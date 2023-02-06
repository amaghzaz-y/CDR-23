#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <uri/UriBraces.h>
class Handy
{
public:
	Handy();
	void setup(void);
	void listen();

private:
	WebServer server;
	// Access Point Settings
	const char *AP_SSID = "HandyMan"; // Access point name
	const char *AP_PWD = "HANDSOME";  // Access point Password
	// Steppers Settings & Pins
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
	// Endpoints
	UriBraces FLOW_URI = UriBraces("/flow/{}/{}/{}");
	UriBraces STEPS_URI = UriBraces("/steps/{}/{}/{}");
	void InitMotors();
	void InitRoutes();
	void Flow_Controller();
	void Steps_Controller();
};