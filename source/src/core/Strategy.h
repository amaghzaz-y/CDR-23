#pragma once

#include "types/Point2D.h"
#include "core/Movement.h"
#include "types/PolarVec.h"
#include "core/Lidar.h"

#define HEIGHT 2000 // value in mm
#define WIDTH 1500	// value in mm
#define OFFSET 100	// value in mm
#define PIN_REED 20
#define HOME_PIN 21
#define TEAM_PIN 22

const Point2D HOME_1_POS = Point2D(OFFSET, OFFSET);
const Point2D HOME_2_POS = Point2D(HEIGHT - OFFSET, WIDTH - OFFSET);

class Strategy
{
private:
	Movement movement;
	Point2D currentPoint;
	Point2D *points;
	PolarVec *vecs;
	Point2D homePOS;
	int currentInstruction;
	float currentRotation;
	int arrayLength;
	bool isPulled;
	bool calibrated;
	bool isHome;
	bool isDetected;
	int team;
	int home;

	void goToPoint();
	void updatePOS(Point2D point);
	void calibrate();
	void selectTeam(int team);
	void selectHome(int home);
	bool atHome();
	void goHome();
	bool isCalibrated();

public:
	Strategy();
	void makeSelection();
	bool isReady();
	void setup();
	void start(bool lidar);
	void executeVecs(bool lidar);
	void stop();
	void setPoints(Point2D *points, int len);
	void setVecs(PolarVec *vecs, int len);
};