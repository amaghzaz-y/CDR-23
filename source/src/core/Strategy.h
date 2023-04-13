#pragma once

#include "types/Point2D.h"
#include "core/Movement.h"
#include "types/PolarVec.h"
#include "core/Lidar.h"

#define HEIGHT 2000		 // value in mm
#define WIDTH 1500		 // value in mm
#define INITIAL_X 171.47 // value in mm
#define INITIAL_Y 250.73
#define REED_PIN 32
#define INIT_PIN 34
#define TEAM_PIN 35

const Point2D HOME_1_POS = Point2D(INITIAL_X, INITIAL_Y);
const Point2D HOME_2_POS = Point2D(HEIGHT - INITIAL_X, WIDTH - INITIAL_Y);

const int SIDE_A = 0;
const int SIDE_AB = 60;
const int SIDE_B = 120;
const int SIDE_BC = 180;
const int SIDE_C = -120;
const int SIDE_CA = -60;

class Strategy
{
private:
	Movement movement;
	Point2D currentPoint;
	Point2D nextPoint;
	Point2D *points;
	PolarVec *vecs;
	Point2D homePOS;
	int currentInstruction;
	int arrayLength;
	float rotation;
	bool isPulled;
	bool calibrated;
	bool isHome;
	bool isDetected;
	int team;
	int home;

public:
	Strategy();
	void goHome();
	bool isCalibrated();
	void goToPoint();
	bool atHome();
	void makeSelection();
	bool isReady();
	void init();
	void calibrate();
	void selectTeam(int team);
	void setNextPoint(Point2D point);
	void setup();
	void start(bool lidar);
	void executeVecs(bool lidar);
	void stop();
	void setPoints(Point2D *points, int len);
	void setVecs(PolarVec *vecs, int len);
};