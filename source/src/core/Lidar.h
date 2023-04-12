#pragma once
#include <rplidar/RPLidar.h>
#include <types/PolarVec.h>
#define LIDAR_MOTOR_PIN 15
#define LIDAR_MOTOR_SPEED 120

class Lidar
{
public:
	RPLidar lidar;
	void setup();
	void detect();
	bool hasDetected();
	void setAngle(float _angle);
	void setRadius(float _radius);
	void setMaxRange(float _range);
	void Task();
	void startService();

private:
	float angle;
	float radius;
	float maxRange;
	bool opponentDetected;
	bool inRadius(PolarVec point);
	void reconnect();
	PolarVec scan();
	bool isPointNull(PolarVec v);
	TaskHandle_t xHandle;
};