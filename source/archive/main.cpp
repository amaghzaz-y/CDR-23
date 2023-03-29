#include <Arduino.h>
#include <ESP_FlexyStepper.h>

// Speed settings
const double SPEED = 14000;
const double ACCEL = 25000;

// create the stepper motor object
ESP_FlexyStepper M1;
ESP_FlexyStepper M2;
ESP_FlexyStepper M3;

void setup()
{
	Serial.begin(9600);
	// connect and configure the stepper motor to its IO pins
	M1.connectToPins(25, 33);
	M2.connectToPins(27, 26);
	M3.connectToPins(14, 12);
	// set the spee and acceleration rates for the stepper motor
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

void moveWithCoordination(long stepsX, long stepsY, long stepsZ)
{
	double absStepsX = abs(stepsX);
	double absStepsY = abs(stepsY);
	double absStepsZ = abs(stepsZ);
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

	M1.setTargetPositionRelativeInSteps(stepsX);
	M2.setTargetPositionRelativeInSteps(stepsY);
	M3.setTargetPositionRelativeInSteps(stepsZ);
}
void loop()
{
	M1.setCurrentPositionInSteps(0);
	M2.setCurrentPositionInSteps(0);
	M3.setCurrentPositionInSteps(0);
	delay(1000);
	moveWithCoordination(9000, 5500, 2000);
	while (M1.getDistanceToTargetSigned() != 0 || M2.getDistanceToTargetSigned() != 0 || M3.getDistanceToTargetSigned() != 0)
	{
		Serial.print(M1.getCurrentPositionInSteps());
		Serial.print(" - ");
		Serial.print(M2.getCurrentPositionInSteps());
		Serial.print(" - ");
		Serial.print(M3.getCurrentPositionInSteps());
		Serial.print("       ||  ");
		Serial.print(M1.motionComplete());
		Serial.print(" - ");
		Serial.print(M2.motionComplete());
		Serial.print(" - ");
		Serial.println(M3.motionComplete());
		delay(1000);
	}
}