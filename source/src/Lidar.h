#pragma once
#include <RPLidar.h>
#include <Types.h>

#define LIDAR_MOTOR_PIN 15
#define LIDAR_MOTOR_SPEED 120


class Lidar
{
public:
	void setup();
	PolarVec detect(int angle, int radius, int range_min, int range_max);

private:
	bool InRadius(PolarVec point, int angle, int radius, int max_range);
	void reconnect();
	PolarVec scan();
	bool isPointNull(PolarVec v);
};