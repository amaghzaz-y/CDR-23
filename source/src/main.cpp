#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <uri/UriBraces.h>
#include <math.h>
#include <RPLidar.h>

const int LIDAR_MOTOR_PIN = 15;
const int LIDAR_MOTOR_SPEED = 120;
const char *AP_SSID = "HandyMan";
const char *AP_PWD = "HANDSOME";
bool lidarConnected = false;
const int PIN_Dir_Motor_1 = 33;
const int PIN_Stp_Motor_1 = 25;
const int PIN_Dir_Motor_2 = 26;
const int PIN_Stp_Motor_2 = 27;
const int PIN_Dir_Motor_3 = 12;
const int PIN_Stp_Motor_3 = 14;
const int PIN_Enable = 13;
int MAX_SPEED = 3000;
int MAX_ACCEL = 30;
RPLidar lidar;
UriBraces FLOW_URI = UriBraces("/flow/{}/{}/{}");
UriBraces STEPS_URI = UriBraces("/steps/{}/{}/{}");
UriBraces LIDAR_URI = UriBraces("/lidar");
WebServer server;
MultiStepper Motors;
AccelStepper Motor_1(1, PIN_Stp_Motor_1, PIN_Dir_Motor_1);
AccelStepper Motor_2(1, PIN_Stp_Motor_2, PIN_Dir_Motor_2);
AccelStepper Motor_3(1, PIN_Stp_Motor_3, PIN_Dir_Motor_3);
void test(char *msg, int value)
{
	Serial.print(msg);
	Serial.print(" : ");
	Serial.println(value);
}
struct Point
{
	float x;
	float y;
};
Point CurrentPOS;
struct Vec2
{
	float angle;	// in radians
	float distance; // in cm
};

struct Steps
{
	float M1;
	float M2;
	float M3;
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
	long newPOS[3] = {long(steps.M1),
					  long(steps.M2),
					  long(steps.M3)};
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
	float motor_1_steps = server.pathArg(0).toFloat();
	float motor_2_steps = server.pathArg(1).toFloat();
	float motor_3_steps = server.pathArg(2).toFloat();
	// long steps[3] = {motor_1_steps, motor_2_steps, motor_3_steps};
	Steps steps = {motor_1_steps, motor_2_steps, motor_3_steps};
	Execute_movement(steps);
	// Motor_1.setCurrentPosition(0);
	// Motor_2.setCurrentPosition(0);
	// Motor_3.setCurrentPosition(0);
	// Motors.moveTo(steps);
	// Motors.runSpeedToPosition();
}
void Lidar_Controller()
{
	if (lidarConnected)
	{
		server.send(200, "text/plain", "ping");
	}
	else
	{
		server.send(200, "text/plain", "pong");
	}
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
	server.on(LIDAR_URI, [] {

	});
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
	vec.angle = degToRad(vec.angle);
	float angle_1 = vec.angle - degToRad(90);
	float angle_2 = vec.angle + degToRad(30);
	float angle_3 = vec.angle + degToRad(150);
	float steps_1 = vec.distance * sin(angle_1);
	float steps_2 = vec.distance * sin(angle_2);
	float steps_3 = vec.distance * sin(angle_3);
	Steps steps = {steps_1, steps_2, steps_3};
	return steps;
}

Point XYfromVec(Vec2 vec)
{
	float x = float(vec.distance) * cos(vec.angle);
	float y = float(vec.distance) * sin(vec.angle);
	Point point = {x, y};
	return point;
}

Vec2 VecFromXY(Point point)
{
	float distance = sqrt(pow(point.x, 2) + pow(point.y, 2));
	float angle = atan2(point.y, point.x);
	Vec2 vec = {angle, distance};
	return vec;
}

Steps RotateTo(float angle) // in degrees
{
	int full_rot = 4000;				// steps to achieve full rotation eq to 360deg
	float rot = angle * full_rot / 360; // rotation in steps per single motor
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

bool LIDAR_InRadius(LiDARPoint point, int angle, int radius, int max_range)
{
	int max_angle = angle + (radius / 2);
	int min_angle = angle - (radius / 2);
	if ((point.angle > min_angle) && (point.angle < max_angle) && (point.distance < max_range))
		return true;
	return false;
}

void LIDAR_Setup()
{
	lidar.begin(Serial2);
}

LiDARPoint LIDAR_Scan()
{
	LiDARPoint point = {0, 0};
	if (IS_OK(lidar.waitPoint()))
	{
		point.angle = lidar.getCurrentPoint().angle;
		point.distance = lidar.getCurrentPoint().distance;
		lidarConnected = true;
	}
	else
	{
		lidarConnected = false;
		LidarReconnect();
	}
	return point;
}

LiDARPoint LIDAR_Detect(int angle, int radius, int range_min, int range_max)
{
	LiDARPoint point = LIDAR_Scan();
	if (LIDAR_InRadius(point, angle, radius, range_max))
		return point;
	else
		return LiDARPoint{0, 0};
}
bool LIDAR_isPointNull(LiDARPoint v)
{
	if (v.angle != 0 || v.distance != 0)
		return false;
	return true;
}
void Execute_Movement_Lidar(Steps steps, int angle)
{
	long newPOS[3] = {long(steps.M1),
					  long(steps.M2),
					  long(steps.M3)};
	position_reset();
	Motors.moveTo(newPOS);
	while (Motor_1.distanceToGo() != 0 || Motor_2.distanceToGo() != 0 || Motor_3.distanceToGo() != 0)
	{
		LiDARPoint point = LIDAR_Detect(angle, 90, 0, 300);
		if (LIDAR_isPointNull(point))
		{
			Motors.run();
		}
	}
}
Vec2 vecs[] = {{0, 20}, {120, 20}, {240, 20}};
void simple_strat()
{
	int i = 0;
	for (i; i < 3; i++)
	{
		test("iteration", i);
		Vec2 vec = vecs[i];
		test("angle", vec.angle);
		test("distance", vec.distance);
		// Serial.println();
		Steps steps = StepsFromVec(vec);
		// Execute_Movement_Lidar(steps, vec.angle);
		// Serial.println()
		Execute_movement(steps);
	}
}

void setup()
{
	Serial.begin(115200);
	// handy_setup();
	// LIDAR_Setup();
	movement_setup();
}

void loop()
{
	// Serial.println("starting");
	// test("start", 0);
	// goPolar(0, 10);
	simple_strat();
	delay(1000);
}