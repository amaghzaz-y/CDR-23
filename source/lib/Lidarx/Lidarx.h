#pragma once
#include "RPLidar.h"
#include <Arduino.h>
typedef struct LiDARPoint
{
	int angle;
	int distance;
};
class Lidarx
{
public:
	void begin(int motor_pin, int motor_speed, HardwareSerial serial);
	LiDARPoint Scan();
	// return Point(0,0) if no object has been detected
	LiDARPoint Detect(int angle, int radius, int range_min, int range_max);

private:
	const int MotorPin = 26;
	const int MotorSpeed = 150;
	RPLidar lidar;
	bool isDetected(LiDARPoint point, int angle, int radius, int range_min, int range_max);
	void LidarReconnect();
};