#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <uri/UriBraces.h>
#include <math.h>

// #include "Lidarx.h"
#define LIDAR_MOTOR_PIN 13
#define LIDAR_MOTOR_SPEED 120

struct Point
{
	int x;
	int y;
};
struct Vec2
{
	int angle;	  // in radians
	int distance; // in steps
};
struct Steps
{
	float M1;
	float M2;
	float M3;
};
WebServer server;
Point CurrentPOS;
const char *AP_SSID = "HandyMan";
const char *AP_PWD = "HANDSOME";
const int PIN_Dir_Motor_1 = 33;
const int PIN_Stp_Motor_1 = 25;
const int PIN_Dir_Motor_2 = 26;
const int PIN_Stp_Motor_2 = 27;
const int PIN_Dir_Motor_3 = 12;
const int PIN_Stp_Motor_3 = 14;
const int PIN_Enable = 13;
AccelStepper Motor_1;
AccelStepper Motor_2;
AccelStepper Motor_3;
MultiStepper Motors;
UriBraces FLOW_URI = UriBraces("/flow/{}/{}/{}");
UriBraces STEPS_URI = UriBraces("/steps/{}/{}/{}");
void InitMotors()
{
	Motor_1.setMaxSpeed(500);
	Motor_1.setAcceleration(50);
	Motor_2.setMaxSpeed(500);
	Motor_2.setAcceleration(50);
	Motor_3.setMaxSpeed(500);
	Motor_3.setAcceleration(50);
	Motors.addStepper(Motor_1);
	Motors.addStepper(Motor_2);
	Motors.addStepper(Motor_3);
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
	long motor_1_steps = server.pathArg(0).toFloat();
	long motor_2_steps = server.pathArg(1).toFloat();
	long motor_3_steps = server.pathArg(2).toFloat();
	long steps[3] = {motor_1_steps, motor_2_steps, motor_3_steps};
	Motor_1.setCurrentPosition(0);
	Motor_2.setCurrentPosition(0);
	Motor_3.setCurrentPosition(0);
	Motors.moveTo(steps);
	Motors.runSpeedToPosition();
}
void InitRoutes(void)
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
void init()
{
	AccelStepper Motor_1(1, PIN_Stp_Motor_1, PIN_Dir_Motor_1);
	AccelStepper Motor_2(1, PIN_Stp_Motor_2, PIN_Dir_Motor_2);
	AccelStepper Motor_3(1, PIN_Stp_Motor_3, PIN_Dir_Motor_3);
}
void initMotors(int max_speed, int acceleration)
{
	Motor_1.setMaxSpeed(max_speed);
	Motor_1.setAcceleration(acceleration);
	Motor_2.setMaxSpeed(max_speed);
	Motor_2.setAcceleration(acceleration);
	Motor_3.setMaxSpeed(max_speed);
	Motor_3.setAcceleration(acceleration);
	Motors.addStepper(Motor_1);
	Motors.addStepper(Motor_2);
	Motors.addStepper(Motor_3);
}
void handy_setup(void)
{
	Serial.begin(115200);
	WiFi.mode(WIFI_MODE_AP);
	WiFi.softAP(AP_SSID, AP_PWD, 1, 0, 2);
	InitMotors();
	server.enableCORS();
	InitRoutes();
	server.begin(80);
}
void handy_listen()
{
	server.handleClient();
};

void Movement()
{
	AccelStepper Motor_1(1, PIN_Stp_Motor_1, PIN_Dir_Motor_1);
	AccelStepper Motor_2(1, PIN_Stp_Motor_2, PIN_Dir_Motor_2);
	AccelStepper Motor_3(1, PIN_Stp_Motor_3, PIN_Dir_Motor_3);
}
void begin()
{
	initMotors(3000, 200);
}
void pos_reset()
{
	Motor_1.setCurrentPosition(0);
	Motor_2.setCurrentPosition(0);
	Motor_3.setCurrentPosition(0);
}
void Execute(Steps steps)
{
	long newPOS[3] = {(int)steps.M1,
					  (int)steps.M2,
					  (int)steps.M3};
	pos_reset();
	Motors.moveTo(newPOS);
	while (Motor_1.distanceToGo() != 0 || Motor_2.distanceToGo() != 0 || Motor_3.distanceToGo() != 0)
	{
		Motors.run();
	}
}
void setCurrentPOS(Point point)
{
	CurrentPOS.x = point.x;
	CurrentPOS.y = point.y;
}
Point getCurrentPOS()
{
	return CurrentPOS;
}
float degToRad(float degrees)
{
	return degrees * DEG_TO_RAD;
}
float CmToSteps(float steps)
{
	return (steps * 4000) / 18.8496;
}

Steps StepsFromVec(Vec2 vec)
{
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
	int full_rot = 4000;				// steps to achieve full rotation eq to 360deg
	float rot = angle * full_rot / 360; // rotation in steps per single motor
	Steps steps = {rot, rot, rot};
	return steps;
}

// Handy handy;
// Lidarx lidar;
void setup()
{
	// lidar.begin(LIDAR_MOTOR_PIN, LIDAR_MOTOR_SPEED, Serial2);
	handy_setup();
}
// LiDARPoint point = {3, 4};

void loop()
{
	handy_listen();
	// LiDARPoint point = lidar.Scan();
}