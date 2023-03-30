#include <core/Movement.h>

Movement::Movement() : target(0, 0, 0)
{
	atTarget = false;
	isTargetSet = false;
	M1_POS = M2_POS = M3_POS = 0;
	reachedTarget[0] = reachedTarget[1] = reachedTarget[2] = false;
}

void Movement::setup()
{
	M1.connectToPins(25, 33);
	M2.connectToPins(27, 26);
	M3.connectToPins(14, 12);

	M1.setSpeedInStepsPerSecond(SPEED);
	M1.setAccelerationInStepsPerSecondPerSecond(ACCEL);
	M1.setDecelerationInStepsPerSecondPerSecond(ACCEL);

	M2.setSpeedInStepsPerSecond(SPEED);
	M2.setAccelerationInStepsPerSecondPerSecond(ACCEL);
	M2.setDecelerationInStepsPerSecondPerSecond(ACCEL);

	M3.setSpeedInStepsPerSecond(SPEED);
	M3.setAccelerationInStepsPerSecondPerSecond(ACCEL);
	M3.setDecelerationInStepsPerSecondPerSecond(ACCEL);

	M1.startAsService(0);
	M2.startAsService(0);
	M3.startAsService(0);
}

void Movement::moveTo(Steps steps)
{
	double absStepsX = abs(steps.M1);
	double absStepsY = abs(steps.M2);
	double absStepsZ = abs(steps.M3);
	double maxSteps = max(absStepsX, max(absStepsZ, absStepsY));

	double scalerX = absStepsX / maxSteps;
	double scalerY = absStepsY / maxSteps;
	double scalerZ = absStepsZ / maxSteps;

	Serial.print("SCALERS : ");
	Serial.print(scalerX);
	Serial.print(" - ");
	Serial.print(scalerY);
	Serial.print(" - ");
	Serial.println(scalerZ);

	double speedX = SPEED * scalerX;
	double speedY = SPEED * scalerY;
	double speedZ = SPEED * scalerZ;

	Serial.print("SPEEDS : ");
	Serial.print(speedX);
	Serial.print(" - ");
	Serial.print(speedY);
	Serial.print(" - ");
	Serial.println(speedZ);

	double accelX = ACCEL * scalerX;
	double accelY = ACCEL * scalerY;
	double accelZ = ACCEL * scalerZ;

	Serial.print("ACCEL : ");
	Serial.print(accelX);
	Serial.print(" - ");
	Serial.print(accelY);
	Serial.print(" - ");
	Serial.println(accelZ);
	Serial.println();
	Serial.println();

	delay(500);

	M1.setSpeedInStepsPerSecond(speedX);
	M2.setSpeedInStepsPerSecond(speedY);
	M3.setSpeedInStepsPerSecond(speedZ);

	M1.setAccelerationInStepsPerSecondPerSecond(accelX);
	M2.setAccelerationInStepsPerSecondPerSecond(accelY);
	M3.setAccelerationInStepsPerSecondPerSecond(accelZ);

	M1.setDecelerationInStepsPerSecondPerSecond(accelX);
	M2.setDecelerationInStepsPerSecondPerSecond(accelY);
	M3.setDecelerationInStepsPerSecondPerSecond(accelZ);

	M1.setTargetPositionRelativeInSteps(steps.M1);
	M2.setTargetPositionRelativeInSteps(steps.M2);
	M3.setTargetPositionRelativeInSteps(steps.M3);
}

// void Movement::doStepAsync(Steps steps)
// {
// 	long pos[] = {M1.getPosition(), M2.getPosition(), M3.getPosition()};

// 	if (!isTargetSet)
// 	{
// 		M1.setTargetRel(steps.M1);
// 		M2.setTargetRel(steps.M2);
// 		M3.setTargetRel(steps.M3);
// 		reachedTarget[0] = reachedTarget[1] = reachedTarget[2] = false;
// 		isTargetSet = true;
// 	}

// 	if (pos[0] >= steps.M1)
// 	{
// 		reachedTarget[0] = true;
// 		M1_POS += pos[0];
// 		M1.setPosition(0);
// 	}

// 	if (pos[1] >= steps.M2)
// 	{
// 		reachedTarget[1] = true;
// 		M2_POS += pos[1];
// 		M2.setPosition(0);
// 	}

// 	if (pos[2] >= steps.M3)
// 	{
// 		reachedTarget[2] = true;
// 		M3_POS += pos[2];
// 		M3.setPosition(0);
// 	}

// 	if (reachedTarget[0] == true && reachedTarget[1] == true && reachedTarget[2] == true)
// 	{
// 		controller.stopTimer();
// 		atTarget = true;
// 	}

// 	if (!atTarget)
// 	{
// 		int i = 0;
// 		while (i < 1000000)
// 		{
// 			controller.moveAsync(M1, M2, M3);
// 			i++;
// 		}
// 	}
// }

bool Movement::hasArrived()
{
	if (M1.motionComplete() && M2.motionComplete() && M3.motionComplete())
	{
		return true;
	}
	return false;
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
	moveTo(target);
}
