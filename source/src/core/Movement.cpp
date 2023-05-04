#include <core/Movement.h>

Movement::Movement()
{
	A1 = AccelStepper(1, 25, 33);
	A1.setEnablePin(13);
	A2 = AccelStepper(1, 27, 26);
	A2.setEnablePin(13);
	A3 = AccelStepper(1, 14, 12);
	A3.setEnablePin(13);
	TEAM_A_HOME = Point2D(INITIAL_X, INITIAL_Y);
	TEAM_B_HOME = Point2D(INITIAL_X, INITIAL_Y);
	currentRotation = 0.0;
	targetRotation = 0.0;
	angleToDo = 0.0;
	calibrated = false;
	isHome = false;
	isDetected = false;
	team = 0;
	currentSideAngle = SIDE_A;
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
	// Serial.print("M1 : ");
	// Serial.print(steps.M1);
	// Serial.print(" - M2 : ");
	// Serial.print(steps.M2);
	// Serial.print(" - M3 : ");
	// Serial.println(steps.M3);

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

bool Movement::hasArrived()
{
	if (A1.distanceToGo() == 0 && A2.distanceToGo() == 0 && A3.distanceToGo() == 0)
	{
		return true;
	}
	return false;
}

void Movement::rotateTo(float angle)
{
	double full_rot = 16000.0;			   // steps to achieve full rotation eq to 360deg
	double rot = angle * full_rot / 360.0; // rotation in steps per single motor
	Steps steps = {(long)rot, (long)rot, (long)rot};
	moveTo(steps);
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
		setPoint(TEAM_A_HOME);
		goToPoint();
		isHome = true;
	}
	else if (team == 1)
	{
		setPoint(TEAM_B_HOME);
		goToPoint();
		isHome = true;
	}
}

void Movement::goHomeSEMI()
{
	setSide(SIDE_A);
	if (team == 0)
	{
		setPoint(TEAM_A_HOME);
		goToPointRotate();
		setRotation(SIDE_A);
		runSync();
		isHome = true;
	}
	else if (team == 1)
	{
		setPoint(TEAM_B_HOME);
		goToPointRotate();
		isHome = true;
	}
}

void Movement::setPoint(Point2D point)
{
	targetPoint = point;
	absPoint = Point2D(point.X - currentPoint.X, point.Y - currentPoint.Y);
}

// sets new absolute Rotation // working proprely
void Movement::setRotation(float angle)
{
	targetRotation = angle;
	angleToDo = normalizeAngle(angle - currentRotation);
	Serial.print("Rotating to Angle: ");
	Serial.println(angleToDo);
}

// executes the absolute rotation
void Movement::doRotation()
{
	rotateTo(angleToDo);
	while (!hasArrived())
	{
		if (isDetected)
		{
			stop();
		}
		run();
	}
	currentRotation = targetRotation;
	Serial.print("current rotation : ");
	Serial.println(currentRotation);
}

void Movement::goToPoint()
{
	isHome = false;
	calibrated = false;

	float distance = sqrt(pow(absPoint.X, 2) + pow(absPoint.Y, 2));
	float angle = currentSideAngle - (atan2(absPoint.Y, absPoint.X) * 57.2957795); // in degrees
	angle = normalizeAngle(angle);
	Serial.print("Moving to Angle : ");
	Serial.println(angle);
	PolarVec vec = PolarVec(angle, distance);
	moveTo(vec.ToSteps());

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

void Movement::goToPointRotate()
{
	isHome = false;
	calibrated = false;

	float distance = sqrt(pow(absPoint.X, 2) + pow(absPoint.Y, 2));
	float angle = 360 - currentSideAngle - (atan2(absPoint.Y, absPoint.X) * 57.2957795); // in degrees
	angle = normalizeAngle(angle);

	setRotation(angle);
	doRotation();

	PolarVec vec = PolarVec(currentSideAngle, distance);

	moveTo(vec.ToSteps());

	Serial.print("Moving to Angle : ");
	Serial.println(vec.angle);
	while (!hasArrived())
	{
		if (isDetected)
		{
			stop();
		}
		run();
	}
	currentPoint = targetPoint;
};

void Movement::setSide(float angle)
{
	currentSideAngle = angle;
}

void Movement::calibrate()
{
	if (team == 0)
	{
		moveTo(PolarVec(SIDE_B, 200).ToSteps());
		runSync();
		moveTo(PolarVec(SIDE_CA, 115).ToSteps());
		runSync();
		rotateTo(30.0);
		runSync();
		moveTo(PolarVec(SIDE_BC, 200).ToSteps());
		runSync();
		moveTo(PolarVec(SIDE_A, 50).ToSteps());
		runSync();
		isHome = true;
		calibrated = true;
		currentPoint = TEAM_A_HOME;
		delay(3000);
	}
	else if (team == 1)
	{
		moveTo(PolarVec(SIDE_C, 200).ToSteps());
		runSync();
		moveTo(PolarVec(SIDE_AB, 115).ToSteps());
		runSync();
		rotateTo(SIDE_C);
		runSync();
		moveTo(PolarVec(SIDE_BC, 200).ToSteps());
		runSync();
		isHome = true;
		calibrated = true;
		currentPoint = TEAM_B_HOME;
		delay(3000);
	}
}

bool Movement::isCalibrated()
{
	return calibrated;
}

void Movement::Execute(Point2D point, bool lidar)
{
	isDetected = lidar;
	setPoint(point);
	goToPoint();
}

void Movement::ExecuteSEMI(Point2D point, bool lidar)
{
	isDetected = lidar;
	setPoint(point);
	goToPointRotate();
}

bool Movement::atHome()
{
	return isHome;
}