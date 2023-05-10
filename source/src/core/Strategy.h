#pragma once

#include "types/Point2D.h"
#include "core/Movement.h"
#include "types/PolarVec.h"
#include "core/Lidar.h"
#include "core/Actuators.h"
#define HEIGHT 2000 // value in mm
#define WIDTH 1500	// value in mm
#define REED_PIN 32
#define INIT_PIN 34
#define TEAM_PIN 35

class Strategy
{
private:
	Point2D *points;
	int currentInstruction;
	int arrayLength;
	void makeSelection();
	void init();
	bool isReady();

public:
	Movement movement;
	Actuators actuators;

	void setup();
	void start(bool lidar);
	void startDebug(bool lidar);
	void ready();
	void startSEMI(bool lidar);
	void startSEMIOFFSET(bool lidar);
	void stop();
	void setPoints(Point2D *points, int len);
};