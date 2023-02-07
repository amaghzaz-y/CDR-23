#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <uri/UriBraces.h>

class Handy
{
private:
	WebServer server;
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
		server.on("/", [this]
				  { server.send(200,"text/plain","ESP32");
              Serial2.println(server.client().localIP()); });
		server.on("/ping", [this]
				  { server.send(200, "text/plain", "{\"message\":\"pong\"}"); });
		server.on(FLOW_URI, [this]
				  { Flow_Controller; });
		server.on(STEPS_URI, [this]
				  { Steps_Controller; });
		server.onNotFound([this]
						  { server.send(200, "text/plain", "not found"); });
	}

public:
	Handy()
	{
		AccelStepper Motor_1(1, PIN_Stp_Motor_1, PIN_Dir_Motor_1);
		AccelStepper Motor_2(1, PIN_Stp_Motor_2, PIN_Dir_Motor_2);
		AccelStepper Motor_3(1, PIN_Stp_Motor_3, PIN_Dir_Motor_3);
	}

	void setup(void)
	{
		Serial.begin(115200);
		WiFi.mode(WIFI_MODE_AP);
		WiFi.softAP(AP_SSID, AP_PWD, 1, 0, 2);
		InitMotors();
		server.enableCORS();
		InitRoutes();
		server.begin(80);
	}
	void listen()
	{
		server.handleClient();
	}
};
