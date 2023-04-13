#pragma once

#include <types/Steps.h>
// #include <stepper/ESP_FlexyStepper.h>
#include <stepper/AccelStepper.h>
#define PIN_DIR_M1 33
#define PIN_DIR_M2 26
#define PIN_DIR_M3 12
#define PIN_STP_M1 25
#define PIN_STP_M2 27
#define PIN_STP_M3 14
#define PIN_ENABLE 13
#define CORRECTIF 1.025

const double SPEED = 3000;
const double ACCEL = 1000;
class Movement
{
public:
	Movement();
	AccelStepper A1;
	AccelStepper A2;
	AccelStepper A3;
	void setup();
	// void setTarget(Steps steps);
	void run();
	void runSync();
	bool hasArrived();
	void moveToRel(Steps steps);
	void moveToAbs(Steps steps);
	void stop();
	void fullStop();
	Steps rotateTo(double angle);

private:
	// ESP_FlexyStepper M1;
	// ESP_FlexyStepper M2;
	// ESP_FlexyStepper M3;

	Steps target;
	int M1_POS;
	int M2_POS;
	int M3_POS;
	// void doStepAsync(Steps steps);
};