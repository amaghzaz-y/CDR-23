#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <uri/UriBraces.h>
#include <math.h>
#include <Types.h>
#include <Lidar.h>
#include <Movement.h>

const char *AP_SSID = "HandyMan";
const char *AP_PWD = "HANDSOME";
bool lidarConnected = false;
UriBraces FLOW_URI = UriBraces("/flow/{}/{}/{}");
UriBraces STEPS_URI = UriBraces("/steps/{}/{}/{}");
UriBraces LIDAR_URI = UriBraces("/lidar");
WebServer server;

void test(char *msg, int value)
{
	Serial.print(msg);
	Serial.print(" : ");
	Serial.println(value);
}

// void Flow_Controller()
// {
// 	server.send(200);
// 	int speed = server.pathArg(0).toInt();
// 	int max_speed = server.pathArg(1).toInt();
// 	int accel = server.pathArg(2).toInt();
// 	// set speed
// 	Motor_1.setSpeed(speed);
// 	Motor_2.setSpeed(speed);
// 	Motor_3.setSpeed(speed);
// 	// set max
// 	Motor_1.setMaxSpeed(max_speed);
// 	Motor_2.setMaxSpeed(max_speed);
// 	Motor_3.setMaxSpeed(max_speed);
// 	// set acceleration
// 	Motor_1.setAcceleration(accel);
// 	Motor_2.setAcceleration(accel);
// 	Motor_3.setAcceleration(accel);
// }

// void Steps_Controller()
// {
// 	server.send(200);
// 	float motor_1_steps = server.pathArg(0).toFloat();
// 	float motor_2_steps = server.pathArg(1).toFloat();
// 	float motor_3_steps = server.pathArg(2).toFloat();
// 	// long steps[3] = {motor_1_steps, motor_2_steps, motor_3_steps};
// 	Steps steps = {motor_1_steps, motor_2_steps, motor_3_steps};
// 	Execute_movement(steps);
// 	// Motor_1.setCurrentPosition(0);
// 	// Motor_2.setCurrentPosition(0);
// 	// Motor_3.setCurrentPosition(0);
// 	// Motors.moveTo(steps);
// 	// Motors.runSpeedToPosition();
// }
// void Lidar_Controller()
// {
// 	if (lidarConnected)
// 	{
// 		server.send(200, "text/plain", "ping");
// 	}
// 	else
// 	{
// 		server.send(200, "text/plain", "pong");
// 	}
// }
// void routes(void)
// {
// 	server.on("/", []
// 			  { server.send(200,"text/plain","ESP32");
//               Serial2.println(server.client().localIP()); });
// 	server.on("/ping", []
// 			  { server.send(200, "text/plain", "{\"message\":\"pong\"}"); });
// 	server.on(FLOW_URI, []
// 			  { Flow_Controller; });
// 	server.on(STEPS_URI, []
// 			  { Steps_Controller; });
// 	server.on(LIDAR_URI, [] {

// 	});
// 	server.onNotFound([]
// 					  { server.send(200, "text/plain", "not found"); });
// }

// void handy_setup(void)
// {
// 	Serial.begin(115200);
// 	WiFi.mode(WIFI_MODE_AP);
// 	WiFi.softAP(AP_SSID, AP_PWD, 1, 0, 2);
// 	server.enableCORS();
// 	routes();
// 	server.begin(80);
// }

// void handy_listen()
// {
// 	server.handleClient();
// };

// float degToRad(float degrees)
// {
// 	return degrees * DEG_TO_RAD;
// }

// float cmToSteps(float steps)
// {
// 	return (steps * 4000) / 18.8496;
// }

// Steps StepsFromVec(Vec2 vec)
// {
// 	vec.distance = cmToSteps(vec.distance);
// 	vec.angle = degToRad(vec.angle);
// 	float angle_1 = vec.angle - degToRad(90);
// 	float angle_2 = vec.angle + degToRad(30);
// 	float angle_3 = vec.angle + degToRad(150);
// 	float steps_1 = vec.distance * sin(angle_1);
// 	float steps_2 = vec.distance * sin(angle_2);
// 	float steps_3 = vec.distance * sin(angle_3);
// 	Steps steps = {steps_1, steps_2, steps_3};
// 	return steps;
// }

// Point XYfromVec(Vec2 vec)
// {
// 	float x = float(vec.distance) * cos(vec.angle);
// 	float y = float(vec.distance) * sin(vec.angle);
// 	Point point = {x, y};
// 	return point;
// }

// Vec2 VecFromXY(Point point)
// {
// 	float distance = sqrt(pow(point.x, 2) + pow(point.y, 2));
// 	float angle = atan2(point.y, point.x);
// 	Vec2 vec = {angle, distance};
// 	return vec;
// }

// Steps RotateTo(float angle) // in degrees
// {
// 	int full_rot = 4000;				// steps to achieve full rotation eq to 360deg
// 	float rot = angle * full_rot / 360; // rotation in steps per single motor
// 	Steps steps = {rot, rot, rot};
// 	return steps;
// }

// void Execute_Movement_Lidar(Steps steps, int angle)
// {
// 	long newPOS[3] = {long(steps.M1),
// 					  long(steps.M2),
// 					  long(steps.M3)};
// 	position_reset();
// 	Motors.moveTo(newPOS);
// 	while (Motor_1.distanceToGo() != 0 || Motor_2.distanceToGo() != 0 || Motor_3.distanceToGo() != 0)
// 	{
// 		LiDARPoint point = LIDAR_Detect(angle, 90, 0, 300);
// 		if (LIDAR_isPointNull(point))
// 		{
// 			Motors.run();
// 		}
// 	}
// }
Vec2 vecs[] = {{0, 20}, {120, 20}, {240, 20}};
void simple_strat()
{
	int i = 0;
	for (i; i < 3; i++)
	{
		// test("iteration", i);
		// Vec2 vec = vecs[i];
		// test("angle", vec.angle);
		// test("distance", vec.distance);
		// Serial.println();
		// Steps steps = StepsFromVec(vec);
		// Execute_Movement_Lidar(steps, vec.angle);
		// Serial.println()
		// Execute_movement(steps);
	}
}

void setup()
{
	Serial.begin(115200);
	// handy_setup();
	// LIDAR_Setup();
	// movement_setup();
}

void loop()
{
	// Serial.println("starting");
	// test("start", 0);
	// goPolar(0, 10);
	simple_strat();
	delay(1000);
}