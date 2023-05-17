#pragma once

#include "types/Point2D.h"
#include "core/Movement.h"
#include "types/PolarVec.h"
#include "core/Lidar.h"
#include "core/Actuators.h"
#include "utils/PINS.h"
#define HEIGHT 2000 // value in mm
#define WIDTH 1500	// value in mm
// const int PIN_IFM3 = 34;
// const int PIN_IFM2 = 36;
// const int PIN_IFM2 = 39;
const int PIN_RST_OLED = 19;
const int PIN_L1 = 15;
const int PIN_L2 = 18;
const int PIN_L3 = 35;
const int REED_PIN = PIN_L1;
const int INIT_PIN = PIN_L2;
const int TEAM_PIN = PIN_L3;

class Strategy
{
private:
	Point2D *points;
	int currentInstruction;
	int arrayLength;
	void teamSelection();
	void init();

public:
	Movement movement;
	Actuators actuators;
	void Initiation();
	void Ready();
	void setup();
	void start(bool lidar);
	void startDebug(bool lidar);
	void startSEMI(bool lidar);
	void startSEMIOFFSET(bool lidar);
	void stop();
	void setPoints(Point2D *points, int len);
	void startStratA(bool lidar);
	void cookMeth(bool lidar);
	void Homologuation(bool lidar);
	Point2D getCurrentPoint();
	void testINPUT();
};