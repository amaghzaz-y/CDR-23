#pragma once

#include <types/Steps.h>
#include <stepper/AccelStepper.h>
#include <types/Point2D.h>

#define PIN_DIR_M1 33
#define PIN_DIR_M2 26
#define PIN_DIR_M3 12
#define PIN_STP_M1 25
#define PIN_STP_M2 27
#define PIN_STP_M3 14
#define PIN_ENABLE 13
const int SIDE_A = 0;
const int SIDE_AB = 60;
const int SIDE_B = 120;
const int SIDE_BC = 180;
const int SIDE_C = -120;
const int SIDE_CA = -60;
const double SPEED = 4000.0;
const double ACCEL = 2000.0;
const float INITIAL_X = 231.47; // value in mm
const float INITIAL_Y = 250.73; // mm
const Point2D TEAM_A_HOME = Point2D(INITIAL_X, INITIAL_Y);
const Point2D TEAM_B_HOME = Point2D(INITIAL_X, INITIAL_Y);

class Movement
{
private:
	AccelStepper A1;
	AccelStepper A2;
	AccelStepper A3;
	Point2D currentPoint;
	float currentRotation;
	float targetRotation;
	float absRotation;
	Point2D absPoint;
	Point2D targetPoint;
	Point2D *points;
	PolarVec *vecs;
	int currentInstruction;
	int arrayLength;
	bool isPulled;
	bool calibrated;
	bool isHome;
	bool isDetected;
	int team;

public:
	Movement();
	void setup();
	void run();
	void runSync();
	bool hasArrived();
	void moveToRel(Steps steps);
	void moveToAbs(Steps steps);
	void stop();
	void fullStop();
	void setTeam(int t);
	void goHome();
	bool isCalibrated();
	void goToPoint();
	void doRotation();
	void setNextPoint(Point2D point);
	void setNextRotation(float angle);
	void rotateTo(float angle);
	bool atHome();
	void calibrate();
	void setPoints(Point2D *points, int len);
	void start(bool lidar);
};