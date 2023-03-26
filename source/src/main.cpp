#include <Arduino.h>
#include <core/Movement.h>
#include <types/PolarVec.h>
// void test(char *msg, int value)
// {
// 	Serial.print(msg);
// 	Serial.print(" : ");
// 	Serial.println(value);
// }

// Movement movement;

// PolarVec vecs[] = {PolarVec(0, 20), PolarVec(120, 20), PolarVec(240, 20)};
// void simple_strat()
// {
// 	test("start", 0);
// 	int i = 0;
// 	for (i; i < 3; i++)
// 	{
// 		test("iteration", i);
// 		test("vecs", vecs[i].ToSteps().Positions()[0]);
// 		test("maxspeed m1", movement.M1.maxSpeed());
// 		test("maxspeed m2", movement.M2.maxSpeed());
// 		test("accel", movement.M1.acceleration());
// 		Serial.println();
// 		movement.Run(vecs[i].ToSteps());
// 	}
// }

void setup()
{
	Serial.begin(115200);
	// movement.Setup();
}

void loop()
{
	// Serial.println("starting");
	// test("start", 0);
	// goPolar(0, 10);
	// simple_strat();
	delay(1000);
}