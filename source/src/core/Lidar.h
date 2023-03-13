#pragma once
#include <rplidar/RPLidar.h>
#include <types/PolarVec.h>
#define LIDAR_MOTOR_PIN 15
#define LIDAR_MOTOR_SPEED 120

class Lidar
{
public:
	void setup();
	PolarVec Detect(int angle, int radius, int range_max);

private:
	bool inRadius(PolarVec point, int angle, int radius, int max_range);
	void reconnect();
	PolarVec scan();
	bool isPointNull(PolarVec v);
};