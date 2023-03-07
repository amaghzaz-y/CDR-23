#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <uri/UriBraces.h>
#include <math.h>
#include <RPLidar.h>

const int LIDAR_MOTOR_PIN = 13;
const int LIDAR_MOTOR_SPEED = 120;
const char *AP_SSID = "HandyMan";
const char *AP_PWD = "HANDSOME";
const int PIN_Dir_Motor_1 = 33;
const int PIN_Stp_Motor_1 = 25;
const int PIN_Dir_Motor_2 = 26;
const int PIN_Stp_Motor_2 = 27;
const int PIN_Dir_Motor_3 = 12;
const int PIN_Stp_Motor_3 = 14;
const int PIN_Enable = 13;
int MAX_SPEED = 3000;
int MAX_ACCEL = 100;
RPLidar lidar;
UriBraces FLOW_URI = UriBraces("/flow/{}/{}/{}");
UriBraces STEPS_URI = UriBraces("/steps/{}/{}/{}");
WebServer server;
MultiStepper Motors;
AccelStepper Motor_1(1, PIN_Stp_Motor_1, PIN_Dir_Motor_1);
AccelStepper Motor_2(1, PIN_Stp_Motor_2, PIN_Dir_Motor_2);
AccelStepper Motor_3(1, PIN_Stp_Motor_3, PIN_Dir_Motor_3);
struct Point
{
	int x;
	int y;
};
Point CurrentPOS;
struct Vec2
{
	int angle;	  // in radians
	int distance; // in cm
};

struct Steps
{
	int M1;
	int M2;
	int M3;
};
void setCurrentPOS(Point point)
{
	CurrentPOS.x = point.x;
	CurrentPOS.y = point.y;
}
void position_reset()
{
	Motor_1.setCurrentPosition(0);
	Motor_2.setCurrentPosition(0);
	Motor_3.setCurrentPosition(0);
}
void Execute_movement(Steps steps)
{
	long newPOS[3] = {(int)steps.M1,
					  (int)steps.M2,
					  (int)steps.M3};
	position_reset();
	Motors.moveTo(newPOS);
	while (Motor_1.distanceToGo() != 0 || Motor_2.distanceToGo() != 0 || Motor_3.distanceToGo() != 0)
	{
		Motors.run();
	}
}
void Flow_Controller()
{
	server.send(200);
	int speed = server.pathArg(0).toInt();
	int max_speed = server.pathArg(1).toInt();
	int accel = server.pathArg(2).toInt();
	// set speed
	Motor_1.setSpeed(speed);
	Motor_2.setSpeed(speed);
	Motor_3.setSpeed(speed);
	// set max
	Motor_1.setMaxSpeed(max_speed);
	Motor_2.setMaxSpeed(max_speed);
	Motor_3.setMaxSpeed(max_speed);
	// set acceleration
	Motor_1.setAcceleration(accel);
	Motor_2.setAcceleration(accel);
	Motor_3.setAcceleration(accel);
}

void Steps_Controller()
{
	server.send(200);
	int motor_1_steps = server.pathArg(0).toFloat();
	int motor_2_steps = server.pathArg(1).toFloat();
	int motor_3_steps = server.pathArg(2).toFloat();
	// long steps[3] = {motor_1_steps, motor_2_steps, motor_3_steps};
	Steps steps = {motor_1_steps, motor_2_steps, motor_3_steps};
	Execute_movement(steps);
	// Motor_1.setCurrentPosition(0);
	// Motor_2.setCurrentPosition(0);
	// Motor_3.setCurrentPosition(0);
	// Motors.moveTo(steps);
	// Motors.runSpeedToPosition();
}

void routes(void)
{
	server.on("/", []
			  { server.send(200,"text/plain","ESP32");
              Serial2.println(server.client().localIP()); });
	server.on("/ping", []
			  { server.send(200, "text/plain", "{\"message\":\"pong\"}"); });
	server.on(FLOW_URI, []
			  { Flow_Controller; });
	server.on(STEPS_URI, []
			  { Steps_Controller; });
	server.onNotFound([]
					  { server.send(200, "text/plain", "not found"); });
}

void movement_setup()
{
	Motor_1.setMaxSpeed(MAX_SPEED);
	Motor_1.setAcceleration(MAX_ACCEL);
	Motor_2.setMaxSpeed(MAX_SPEED);
	Motor_2.setAcceleration(MAX_ACCEL);
	Motor_3.setMaxSpeed(MAX_SPEED);
	Motor_3.setAcceleration(MAX_ACCEL);
	Motors.addStepper(Motor_1);
	Motors.addStepper(Motor_2);
	Motors.addStepper(Motor_3);
}

void handy_setup(void)
{
	Serial.begin(115200);
	WiFi.mode(WIFI_MODE_AP);
	WiFi.softAP(AP_SSID, AP_PWD, 1, 0, 2);
	server.enableCORS();
	routes();
	server.begin(80);
}

void handy_listen()
{
	server.handleClient();
};

float degToRad(float degrees)
{
	return degrees * DEG_TO_RAD;
}

float cmToSteps(float steps)
{
	return (steps * 4000) / 18.8496;
}

Steps StepsFromVec(Vec2 vec)
{
	vec.distance = cmToSteps(vec.distance);
	float angle_1 = vec.angle - degToRad(90);
	float angle_2 = vec.angle + degToRad(30);
	float angle_3 = vec.angle + degToRad(150);
	int steps_1 = vec.distance * sin(angle_1);
	int steps_2 = vec.distance * sin(angle_2);
	int steps_3 = vec.distance * sin(angle_3);
	Steps steps = {steps_1, steps_2, steps_3};
	return steps;
}

Point XYfromVec(Vec2 vec)
{
	float x = vec.distance * cos(vec.angle);
	float y = vec.distance * sin(vec.angle);
	Point point = {(int)x, (int)y};
	return point;
}

Vec2 VecFromXY(Point point)
{
	float distance = sqrt(pow(point.x, 2) + pow(point.y, 2));
	float angle = atan2(point.y, point.x);
	Vec2 vec = {(int)angle, (int)distance};
	return vec;
}

Steps RotateTo(float angle) // in degrees
{
	int full_rot = 4000;			  // steps to achieve full rotation eq to 360deg
	int rot = angle * full_rot / 360; // rotation in steps per single motor
	Steps steps = {rot, rot, rot};
	return steps;
}

struct LiDARPoint
{
	int angle;
	int distance;
};

void LidarReconnect()
{
	analogWrite(LIDAR_MOTOR_PIN, 0);
	delay(15);
	rplidar_response_device_info_t info;
	if (IS_OK(lidar.getDeviceInfo(info, 100)))
	{
		Serial.println("Lidar Detected...");
		lidar.startScan();
		analogWrite(LIDAR_MOTOR_PIN, LIDAR_MOTOR_SPEED);
		delay(500);
	}
}

bool isDetected(LiDARPoint point, int angle, int radius, int range_min, int range_max)
{
	int max_angle = angle + (radius / 2);
	int min_angle = angle + (radius / 2);
	if (point.angle > min_angle && point.angle < max_angle && point.distance > range_min && point.distance < range_max)
		return true;
	return false;
}

void lidar_setup()
{
	lidar.begin(Serial2);
}

LiDARPoint Scan()
{
	LiDARPoint point;
	if (IS_OK(lidar.waitPoint()))
	{
		point.angle = lidar.getCurrentPoint().angle;
		point.distance = lidar.getCurrentPoint().distance;
	}
	else
	{
		LidarReconnect();
	}
	return point;
}

LiDARPoint Detect(int angle, int radius, int range_min, int range_max)
{
	LiDARPoint point = Scan();
	if (isDetected(point, angle, radius, range_min, range_max))
		return point;
	else
		return LiDARPoint{0, 0};
}
bool isLiDARPointNull(LiDARPoint v)
{
	if (v.angle != 0 || v.distance != 0)
		return false;
	return true;
}
void Execute_Movement_Lidar(Steps steps)
{
	long newPOS[3] = {(int)steps.M1,
					  (int)steps.M2,
					  (int)steps.M3};
	position_reset();
	Motors.moveTo(newPOS);
	while (Motor_1.distanceToGo() != 0 || Motor_2.distanceToGo() != 0 || Motor_3.distanceToGo() != 0)
	{
		LiDARPoint point = Detect(360, 0, 0, 500);
		if (!isLiDARPointNull(point))
		{
			Motors.run();
		}
	}
}
Vec2 vecs[] = {(30, 25), (180, 25), (270, 25)};
void simple_strat()
{
	for (int i = 0; i < 2; i++)
	{
		Vec2 vec = vecs[i];
		Steps steps = StepsFromVec(vec);
		Execute_Movement_Lidar(steps);
	}
}
void setup()
{
	// handy_setup();
	lidar_setup();
	movement_setup();
}

void loop()
{
	simple_strat();
	// handy_listen();
}