#pragma once

#include <types/Steps.h>
#include <stepper/ESP_FlexyStepper.h>

#define PIN_DIR_M1 33
#define PIN_DIR_M2 26
#define PIN_DIR_M3 12
#define PIN_STP_M1 25
#define PIN_STP_M2 27
#define PIN_STP_M3 14
#define PIN_ENABLE 13
#define MAX_SPEED 1000000
#define MAX_ACCEL 100000
const double SPEED = 14000;
const double ACCEL = 25000;
class Movement
{
public:
	Movement();
	ESP_FlexyStepper M1;
	ESP_FlexyStepper M2;
	ESP_FlexyStepper M3;
	void setup();
	void setTargetRelative(Steps steps);
	void setTargetAbsolute(Steps steps);
	void run();
	bool hasArrived();
	void moveTo(Steps steps);

private:
	Steps target;
	int M1_POS;
	int M2_POS;
	int M3_POS;
	bool atTarget;
	bool isTargetSet;
	bool reachedTarget[3];
	// void doStepAsync(Steps steps);
};