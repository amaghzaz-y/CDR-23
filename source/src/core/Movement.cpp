#include <core/Movement.h>

Movement::Movement()
{
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

void Movement::moveToRel(Steps steps)
{
	double absStepsX = abs(steps.M1);
	double absStepsY = abs(steps.M2);
	double absStepsZ = abs(steps.M3);

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

void Movement::moveToAbs(Steps steps)
{
	double absStepsX = abs(steps.M1);
	double absStepsY = abs(steps.M2);
	double absStepsZ = abs(steps.M3);

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

	A1.moveTo(steps.M1);
	A2.moveTo(steps.M2);
	A3.moveTo(steps.M3);
}

bool Movement::hasArrived()
{
	if (A1.distanceToGo() == 0 && A2.distanceToGo() == 0 && A3.distanceToGo() == 0)
	{
		return true;
	}
	return false;
}

void Movement::rotateTo(Point2D point)
{
	float angle = point.getAngle();
	double full_rot = 4000.0;			   // steps to achieve full rotation eq to 360deg
	double rot = angle * full_rot / 360.0; // rotation in steps per single motor
	Steps steps = {(long)rot, (long)rot, (long)rot};
	moveToRel(steps);
	runSync();
}

void Movement::rotateToSide(float angle)
{
	double full_rot = 4000.0;			   // steps to achieve full rotation eq to 360deg
	double rot = angle * full_rot / 360.0; // rotation in steps per single motor
	Steps steps = {(long)rot, (long)rot, (long)rot};
	moveToRel(steps);
	runSync();
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

void Movement::setTeam(int i)
{
	team = i;
}

void Movement::goHome()
{
	if (team == 0)
	{
		setNextPoint(TEAM_A_HOME);
		goToPoint();
		isHome = true;
	}
	else if (team == 1)
	{
		setNextPoint(TEAM_B_HOME);
		goToPoint();
		isHome = true;
	}
}

void Movement::setNextPoint(Point2D point)
{
	targetPoint = point;
	absPoint = Point2D(point.X - currentPoint.X, point.Y - currentPoint.Y);
}

void Movement::goToPoint()
{
	isHome = false;
	calibrated = false;
	moveToRel(absPoint.toSteps());
	while (!hasArrived())
	{
		if (isDetected)
		{
			stop();
		}
		run();
	}
	currentPoint = targetPoint;
}

void Movement::setPoints(Point2D *p, int len)
{
	points = p;
	arrayLength = len;
}

void Movement::calibrate()
{
	if (team == 0)
	{
		moveToRel(PolarVec(SIDE_B, 200).ToStepsCosSin());
		runSync();
		moveToRel(PolarVec(SIDE_CA, 115).ToStepsCosSin());
		runSync();
		rotateToSide(SIDE_B);
		moveToRel(PolarVec(SIDE_BC, 200).ToStepsCosSin());
		runSync();
		moveToRel(PolarVec(SIDE_A, 50).ToStepsCosSin());
		runSync();
		isHome = true;
		calibrated = true;
		currentPoint = Point2D(INITIAL_X, INITIAL_Y);
		delay(3000);
	}
	else if (team == 1)
	{
		moveToRel(PolarVec(SIDE_C, 200).ToStepsCosSin());
		runSync();
		moveToRel(PolarVec(SIDE_AB, 115).ToStepsCosSin());
		runSync();
		rotateToSide(SIDE_C);
		moveToRel(PolarVec(SIDE_BC, 200).ToStepsCosSin());
		runSync();
		isHome = true;
		calibrated = true;
		currentPoint = Point2D(INITIAL_X, INITIAL_Y);
		delay(3000);
	}
}

bool Movement::isCalibrated()
{
	return calibrated;
}

void Movement::start(bool lidar)
{
	isDetected = lidar;
	while (currentInstruction < arrayLength)
	{
		setNextPoint(points[currentInstruction]);
		goToPoint();
		currentInstruction++;
	}
	goHome();
}

bool Movement::atHome()
{
	return isHome;
}