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
	void LidarReconnect();

public:
	void begin(int motor_pin, int motor_speed, HardwareSerial serial);
	Point GetLidarPoint();
};