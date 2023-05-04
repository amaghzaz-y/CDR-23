#pragma once
#include <Arduino.h>
#include "lib/pwnservo/Adafruit_PWMServoDriver.h"

#define SERVOMIN 150  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600  // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 1300	  // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 1900	  // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

const int SERVO_SIDE_A_L = 0;
const int SERVO_SIDE_A_R = 1;
const int SERVO_SIDE_B_L = 2;
const int SERVO_SIDE_B_R = 3;
const int SERVO_SIDE_C_L = 4;
const int SERVO_SIDE_C_R = 5;
const int SIDE_A_ID = 0;
const int SIDE_B_ID = 1;
const int SIDE_C_ID = 2;

class Actuators
{
private:
	Adafruit_PWMServoDriver servoDriver;
	bool side_A_full;
	bool side_B_full;
	bool side_C_full;

public:
	void setup();
	void pickObject(int SIDE);
	void releaseObject(int SIDE);
	bool isObjectPicked(int SIDE);
	void elevateObject(int SIDE);
	void delevateObject(int SIDE);
	void performTEST();
};