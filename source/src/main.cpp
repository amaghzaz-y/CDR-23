#include <Arduino.h>
#include <core/Movement.h>
#include <types/PolarVec.h>

void log(char *msg, int value)
{
	Serial.print(msg);
	Serial.print(" : ");
	Serial.println(value);
}

Movement movement;

PolarVec vecs[] = {PolarVec(0, 20), PolarVec(120, 20), PolarVec(240, 20)};
void simple_strat()
{
	log("start", 0);
	int i = 0;
	for (i; i < 3; i++)
	{
		log("iteration", i);
		log("vecs", vecs[i].ToSteps().Positions()[0]);
		Serial.println();
		movement.Run(vecs[i].ToSteps());
	}
}

void setup()
{
	Serial.begin(115200);
	movement.Setup();
}

void loop()
{
	Serial.println("starting");
	log("start", 0);
	simple_strat();
	delay(1000);
}