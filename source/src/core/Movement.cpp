#include <core/Movement.h>

Movement::Movement() : target(0, 0, 0)
{
	M1_POS = M2_POS = M3_POS = 0;
	A1 = AccelStepper(1, 25, 33);
	A1.setEnablePin(13);
	A2 = AccelStepper(1, 27, 26);
	A2.setEnablePin(13);
	A3 = AccelStepper(1, 14, 12);
	A3.setEnablePin(13);
}

void Movement::setup()
{
	A1.setAcceleration(ACCEL);
	A2.setAcceleration(ACCEL);
	A3.setAcceleration(ACCEL);

	A1.setMaxSpeed(SPEED);
	A2.setMaxSpeed(SPEED);
	A3.setMaxSpeed(SPEED);
}

void Movement::moveTo(Steps steps)
{
	double absStepsX = abs(steps.M1) * CORRECTIF;
	double absStepsY = abs(steps.M2) * CORRECTIF;
	double absStepsZ = abs(steps.M3) * CORRECTIF;

	double maxSteps = max(absStepsX, max(absStepsZ, absStepsY));

	double scalerX = absStepsX / maxSteps;
	double scalerY = absStepsY / maxSteps;
	double scalerZ = absStepsZ / maxSteps;

	double speedX = SPEED * scalerX;
	double speedY = SPEED * scalerY;
	double speedZ = SPEED * scalerZ;

	double accelX = ACCEL * scalerX;
	double accelY = ACCEL * scalerY;
	double accelZ = ACCEL * scalerZ;

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

bool Movement::hasArrived()
{
	if (A1.distanceToGo() == 0 && A2.distanceToGo() == 0 && A3.distanceToGo() == 0)
	{
		return true;
	}
	return false;
}

void Movement::setTargetRelative(Steps steps)
{

	target = steps;
	moveTo(target);
}

void Movement::setTargetAbsolute(Steps steps)
{
	long s1 = steps.M1 - M1_POS;
	long s2 = steps.M2 - M2_POS;
	long s3 = steps.M3 - M3_POS;
	target = Steps(s1, s2, s3);
	M1_POS += s1;
	M2_POS += s2;
	M3_POS += s3;
	moveTo(target);
}

Steps Movement::rotateTo(float angle)
{

	int full_rot = 4000;				// steps to achieve full rotation eq to 360deg
	float rot = angle * full_rot / 360; // rotation in steps per single motor
	Steps steps = {rot, rot, rot};
	return steps;
}

void Movement::run()
{
	A1.run();
	A2.run();
	A3.run();
}
void Movement::runSync()
{
	while (!hasArrived())
	{
		A1.run();
		A2.run();
		A3.run();
	}
}

void Movement::stop()
{
	A1.stop();
	A2.stop();
	A3.stop();
	delay(2500);
}

void Movement::fullStop()
{
	A1.setMaxSpeed(0);
	A2.setMaxSpeed(0);
	A3.setMaxSpeed(0);
	A1.stop();
	A2.stop();
	A3.stop();
}
