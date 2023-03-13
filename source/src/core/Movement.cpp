#include <core/Movement.h>

MultiStepper M;
AccelStepper M1(1, PIN_STP_M1, PIN_DIR_M1);
AccelStepper M2(1, PIN_STP_M2, PIN_DIR_M2);
AccelStepper M3(1, PIN_STP_M3, PIN_DIR_M3);

void Movement::positionReset()
{
	M1.setCurrentPosition(0);
	M1.setCurrentPosition(0);
	M3.setCurrentPosition(0);
}

void Movement::Setup()
{
	M1.setMaxSpeed(MAX_SPEED);
	M1.setAcceleration(MAX_ACCEL);
	M2.setMaxSpeed(MAX_SPEED);
	M2.setAcceleration(MAX_ACCEL);
	M3.setMaxSpeed(MAX_SPEED);
	M3.setAcceleration(MAX_ACCEL);
	M.addStepper(M1);
	M.addStepper(M2);
	M.addStepper(M3);
}

void Movement::MoveRelative(Steps steps)
{
	long *newPOS = steps.Positions();
	Movement::positionReset();
	M.moveTo(newPOS);
	while (M1.distanceToGo() != 0 || M2.distanceToGo() != 0 || M3.distanceToGo() != 0)
	{
		M.run();
	}
}

void Movement::MoveAbsolute(Steps steps)
{
	long *newPOS = steps.Positions();
	M.moveTo(newPOS);
	while (M1.distanceToGo() != 0 || M2.distanceToGo() != 0 || M3.distanceToGo() != 0)
	{
		M.run();
	}
}