#include <core/Movement.h>

Movement::Movement() : M1(PIN_STP_M1, PIN_DIR_M1),
					   M2(PIN_STP_M2, PIN_DIR_M2),
					   M3(PIN_STP_M3, PIN_DIR_M3)
{
	this->atTarget = false;
	M1_POS = 0;
	M2_POS = 0;
	M3_POS = 0;
}

void Movement::Setup()
{
	M1.setMaxSpeed(MAX_SPEED);
	M1.setAcceleration(MAX_ACCEL);
	M2.setMaxSpeed(MAX_SPEED);
	M2.setAcceleration(MAX_ACCEL);
	M3.setMaxSpeed(MAX_SPEED);
	M3.setAcceleration(MAX_ACCEL);
}

void Movement::doStepAsync(Steps steps)
{
	int pos_1 = M1.getPosition();
	int pos_2 = M2.getPosition();
	int pos_3 = M3.getPosition();
	if (pos_1 == 0 && pos_2 == 0 && pos_3 == 0 && this->atTarget == false)
	{
		M1.setTargetRel(steps.M1);
		M2.setTargetRel(steps.M2);
		M3.setTargetRel(steps.M3);
	}
	if (pos_1 > steps.M1 && pos_2 > steps.M2 && pos_3 > steps.M3)
	{
		controller.stopTimer();
		M1_POS += M1.getPosition();
		M2_POS += M2.getPosition();
		M3_POS += M3.getPosition();
		M1.setPosition(0);
		M2.setPosition(0);
		M3.setPosition(0);
		this->atTarget = true;
	}
	controller.moveAsync(M1, M2, M3);
}

void Movement::MoveRelative(Steps steps)
{
	this->doStepAsync(steps);
}

void Movement::MoveAbsolute(Steps steps)
{
	// long *newPOS = steps.Positions();
	// Movement::speedReset();
	// M.moveTo(newPOS);
	// while (M1.distanceToGo() != 0 || M2.distanceToGo() != 0 || M3.distanceToGo() != 0)
	// {
	// 	M.run();
	// }
}

void Movement::Run(Steps steps)
{
	// long *newPOS = steps.Positions();
	// Movement::positionReset();
	// Movement::speedReset();
	// M.moveTo(newPOS);
	// M.runSpeedToPosition();
}
