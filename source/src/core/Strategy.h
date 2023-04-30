#pragma once

#include "types/Point2D.h"
#include "core/Movement.h"
#include "types/PolarVec.h"
#include "core/Lidar.h"

#define HEIGHT 2000 // value in mm
#define WIDTH 1500	// value in mm
#define REED_PIN 32
#define INIT_PIN 34
#define TEAM_PIN 35

class Strategy
{
public:
	Movement movement;
	Strategy();
	void setup();
	void makeSelection();
	bool isReady();
	void init();
	void start(bool lidar);
};