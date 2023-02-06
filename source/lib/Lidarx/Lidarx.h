#pragma once
#include "RPLidar.h"
#include <Arduino.h>
class Lidarx
{
	typedef struct Point;

private:
	const int MotorPin = 26;
	const int MotorSpeed = 150;
	RPLidar lidar;
	bool isDetected(Point point, int angle, int radius, int range_min, int range_max);
	void LidarReconnect();

public:
	void begin(int motor_pin, int motor_speed, HardwareSerial serial);
	Point Scan();
	// return Point(0,0) if no object has been detected
	Point Detect(int angle, int radius, int range_min, int range_max);
};