#include <core/Movement.h>

Movement::Movement() : M1(PIN_STP_M1, PIN_DIR_M1),
					   M2(PIN_STP_M2, PIN_DIR_M2),
					   M3(PIN_STP_M3, PIN_DIR_M3),
					   target(0, 0, 0)
{
	atTarget = false;
	isTargetSet = false;
	M1_POS = M2_POS = M3_POS = 0;
	reachedTarget[0] = reachedTarget[1] = reachedTarget[2] = false;
}

void Movement::setup()
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
	long pos[] = {M1.getPosition(), M2.getPosition(), M3.getPosition()};

	if (!isTargetSet)
	{
		M1.setTargetRel(steps.M1);
		M2.setTargetRel(steps.M2);
		M3.setTargetRel(steps.M3);
		reachedTarget[0] = reachedTarget[1] = reachedTarget[2] = false;
		isTargetSet = true;
	}

	if (pos[0] >= steps.M1)
	{
		reachedTarget[0] = true;
		M1_POS += pos[0];
		M1.setPosition(0);
	}

	if (pos[1] >= steps.M2)
	{
		reachedTarget[1] = true;
		M2_POS += pos[1];
		M2.setPosition(0);
	}

	if (pos[2] >= steps.M3)
	{
		reachedTarget[2] = true;
		M3_POS += pos[2];
		M3.setPosition(0);
	}

	if (reachedTarget[0] == true && reachedTarget[1] == true && reachedTarget[2] == true)
	{
		controller.stopTimer();
		atTarget = true;
	}

	if (!atTarget)
	{
		int i = 0;
		while (i < 1000000)
		{
			controller.moveAsync(M1, M2, M3);
			i++;
		}
	}
}

bool Movement::hasArrived()
{
	return atTarget;
}

void Movement::setTargetRelative(Steps steps)
{

	atTarget = false;
	isTargetSet = false;
	target = steps;
}

void Movement::setTargetAbsolute(Steps steps)
{
	atTarget = false;
	isTargetSet = false;
	long s1 = steps.M1 - M1_POS;
	long s2 = steps.M2 - M2_POS;
	long s3 = steps.M3 - M3_POS;
	target = Steps(s1, s2, s3);
}

void Movement::run()
{
	doStepAsync(target);
}
