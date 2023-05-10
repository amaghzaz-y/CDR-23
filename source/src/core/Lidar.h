#pragma once
#include <lib/rplidar/RPLidar.h>
#include <types/PolarVec.h>
#include <types/Point2D.h>

#define LIDAR_MOTOR_PIN 15
#define LIDAR_MOTOR_SPEED 120
#define X_RANGE_MAX 1500
#define Y_RANGE_MAX 2000

class Lidar
{
public:
	void setup();
	void detect();
	bool hasDetected();
	void setAngle(float _angle);
	void setRadius(float _radius);
	void setMaxRange(float _range);
	void setCurrentPoint(Point2D _point);
	void Task();
	void startService();

private:
	RPLidar lidar;
	float angle;
	float radius;
	float maxRange;
	bool opponentDetected;
	Point2D currentPosition;
	bool inRadius(PolarVec point);
	bool inRange(PolarVec point);
	void reconnect();
	PolarVec scan();
	bool isPointNull(PolarVec v);
	TaskHandle_t xHandle;
};