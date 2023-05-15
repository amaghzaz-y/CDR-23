#pragma once

#include <types/Steps.h>
#include <lib/stepper/AccelStepper.h>
#include <types/Point2D.h>
#include <utils/utils.h>
#include "utils/PINS.h"

// #define PIN_DIR_M1 33
// #define PIN_DIR_M2 26
// #define PIN_DIR_M3 12
// #define PIN_STP_M1 25
// #define PIN_STP_M2 27
// #define PIN_STP_M3 14
// #define PIN_ENABLE 13

const int SIDE_A = 360;
const int SIDE_AB = 60;
const int SIDE_B = 120;
const int SIDE_BC = -180;
const int SIDE_C = -120;
const int SIDE_CA = -60;

const double SPEED = 5000.0;
const double ACCEL = 4000.0;

const float INITIAL_X = 231.47; // value in mm
const float INITIAL_Y = 250.73; // mm

const float OFFSET_DISTANCE = 40.0; // mm

class Movement
{
private:
	AccelStepper A1;
	AccelStepper A2;
	AccelStepper A3;
	Point2D currentPoint;
	float currentRotation;
	float targetRotation;
	float angleToDo;
	Point2D absPoint;
	Point2D targetPoint;
	bool calibrated;
	bool isHome;
	bool isDetected;
	int team;
	float currentSideAngle;
	void goToPoint();
	void stop();
	Point2D TEAM_A_HOME;
	Point2D TEAM_B_HOME;
	void run();
	void runSync();
	void moveTo(Steps steps);
	void doRotation();
	void setPoint(Point2D point);
	void setRotation(float angle);
	void goToPointRotate();
	void goToPoinRotateOffset();

public:
	Movement();
	void rotateTo(float angle);
	void setSide(float angle);
	void setup();
	bool HasArrived();
	void FullStop();
	void setTeam(int t);
	bool isCalibrated();
	bool atHome();
	void Calibrate();
	// move to point with translation
	void Execute(Point2D point, bool lidar);
	// move to point with rotation only
	void ExecuteSEMI(Point2D point, bool lidar);
	// move to point with rotation and offset
	void ExecuteSEMIOFFSET(Point2D point, bool lidar);
	void goHome();
	void goHomeSEMI();
	void setCurrentPosition(Point2D point);
	Point2D getCurrentPoint();
};