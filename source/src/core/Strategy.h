#pragma once

#include "types/Point2D.h"
#include "core/Movement.h"
#include "types/PolarVec.h"
#include "core/Lidar.h"

#define HEIGHT 2000 // value in mm
#define WIDTH 1500	// value in mm
#define OFFSET 100	// value in mm
#define PIN_REED 32
#define INIT_PIN 34
#define TEAM_PIN 35

const Point2D HOME_1_POS = Point2D(OFFSET, OFFSET);
const Point2D HOME_2_POS = Point2D(HEIGHT - OFFSET, WIDTH - OFFSET);

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

	void goToPoint();
	void updatePOS(Point2D point);
	bool atHome();
	void goHome();
	bool isCalibrated();

public:
	Strategy();
	void makeSelection();
	bool isReady();
	void init();
	void calibrate();
	void selectTeam(int team);

	void setup();
	void start(bool lidar);
	void executeVecs(bool lidar);
	void stop();
	void setPoints(Point2D *points, int len);
	void setVecs(PolarVec *vecs, int len);
};