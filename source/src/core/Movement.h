#pragma once

#include <stepper/TeensyStep.h>
#include <types/Steps.h>

#define PIN_DIR_M1 33
#define PIN_DIR_M2 26
#define PIN_DIR_M3 12
#define PIN_STP_M1 25
#define PIN_STP_M2 27
#define PIN_STP_M3 14
#define PIN_ENABLE 13
#define MAX_SPEED 10000
#define MAX_ACCEL 1000

class Movement
{
public:
	Movement();
	void setup();
	void setTargetRelative(Steps steps);
	void setTargetAbsolute(Steps steps);
	void run();
	bool hasArrived();

private:
	Stepper M1;
	Stepper M2;
	Stepper M3;
	StepControl controller;
	Steps target;
	int M1_POS;
	int M2_POS;
	int M3_POS;
	bool atTarget;
	bool isTargetSet;
	bool reachedTarget[3];
	void doStepAsync(Steps steps);
};