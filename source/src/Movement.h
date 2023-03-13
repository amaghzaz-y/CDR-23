#pragma once

#include <Types.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

#define PIN_DIR_M1 33
#define PIN_DIR_M2 26
#define PIN_DIR_M3 12
#define PIN_STP_M1 25
#define PIN_STP_M2 27
#define PIN_STP_M3 14
#define PIN_ENABLE 13
#define MAX_SPEED 3000
#define MAX_ACCEL 30

class Movement
{
public:
	void Setup();
	void Execute(Steps steps);

private:
	void positionReset();
};