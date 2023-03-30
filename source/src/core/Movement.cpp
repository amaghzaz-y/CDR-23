#include <core/Movement.h>

Movement::Movement() : target(0, 0, 0)
{
	atTarget = false;
	isTargetSet = false;
	M1_POS = M2_POS = M3_POS = 0;
	reachedTarget[0] = reachedTarget[1] = reachedTarget[2] = false;
	A1 = AccelStepper(1, 25, 33);
	A1.setEnablePin(13);
	A2 = AccelStepper(1, 27, 26);
	A2.setEnablePin(13);
	A3 = AccelStepper(1, 14, 12);
	A3.setEnablePin(13);
}

void Movement::setup()
{
	// M1.connectToPins(25, 33);
	// M2.connectToPins(27, 26);
	// M3.connectToPins(14, 12);

	// M1.setSpeedInStepsPerSecond(SPEED);
	// M1.setAccelerationInStepsPerSecondPerSecond(ACCEL);
	// M1.setDecelerationInStepsPerSecondPerSecond(ACCEL);

	// M2.setSpeedInStepsPerSecond(SPEED);
	// M2.setAccelerationInStepsPerSecondPerSecond(ACCEL);
	// M2.setDecelerationInStepsPerSecondPerSecond(ACCEL);

	// M3.setSpeedInStepsPerSecond(SPEED);
	// M3.setAccelerationInStepsPerSecondPerSecond(ACCEL);
	// M3.setDecelerationInStepsPerSecondPerSecond(ACCEL);

	// M1.startAsService(1);
	// M2.startAsService(1);
	// M3.startAsService(1);

	A1.setAcceleration(ACCEL);
	A2.setAcceleration(ACCEL);
	A3.setAcceleration(ACCEL);

	A1.setMaxSpeed(SPEED);
	A2.setMaxSpeed(SPEED);
	A3.setMaxSpeed(SPEED);
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

	// M1.setSpeedInStepsPerSecond(speedX);
	// M2.setSpeedInStepsPerSecond(speedY);
	// M3.setSpeedInStepsPerSecond(speedZ);

	// M1.setAccelerationInStepsPerSecondPerSecond(accelX);
	// M2.setAccelerationInStepsPerSecondPerSecond(accelY);
	// M3.setAccelerationInStepsPerSecondPerSecond(accelZ);

	// M1.setDecelerationInStepsPerSecondPerSecond(accelX);
	// M2.setDecelerationInStepsPerSecondPerSecond(accelY);
	// M3.setDecelerationInStepsPerSecondPerSecond(accelZ);

	// M1.setCurrentPositionInSteps(0);
	// M2.setCurrentPositionInSteps(0);
	// M3.setCurrentPositionInSteps(0);

	// M1.setTargetPositionRelativeInSteps(steps.M1);
	// M2.setTargetPositionRelativeInSteps(steps.M2);
	// M3.setTargetPositionRelativeInSteps(steps.M3);

	A1.setAcceleration(accelX);
	A2.setAcceleration(accelY);
	A3.setAcceleration(accelZ);

	A1.setMaxSpeed(speedX);
	A2.setMaxSpeed(speedY);
	A3.setMaxSpeed(speedZ);

	A1.setCurrentPosition(0);
	A2.setCurrentPosition(0);
	A3.setCurrentPosition(0);

	A1.move(steps.M1);
	A2.move(steps.M2);
	A3.move(steps.M3);
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
	// if (M1.motionComplete() && M2.motionComplete() && M3.motionComplete())
	// {
	// 	return true;
	// }
	if (A1.distanceToGo() == 0 && A2.distanceToGo() == 0 && A3.distanceToGo() == 0)
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
	moveTo(target);
}

void Movement::setTargetAbsolute(Steps steps)
{
	atTarget = false;
	isTargetSet = false;
	long s1 = steps.M1 - M1_POS;
	long s2 = steps.M2 - M2_POS;
	long s3 = steps.M3 - M3_POS;
	target = Steps(s1, s2, s3);
	moveTo(target);
}

void Movement::run()
{
	// M1.processMovement();
	// M2.processMovement();
	// M3.processMovement();
	A1.run();
	A2.run();
	A3.run();
}
