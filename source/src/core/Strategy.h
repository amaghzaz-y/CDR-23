#include "types/Point2D.h"
#include "core/Movement.h"
#include "types/PolarVec.h"
#include "core/Lidar.h"

#define HEIGHT 2000	 // value in mm
#define WIDTH 1500	 // value in mm
#define OFFSET 100	 // value in mm
#define MAX_TIME 120 // value in seconds

const Point2D HOME_1_POS = Point2D(OFFSET, OFFSET);
const Point2D HOME_2_POS = Point2D(HEIGHT - OFFSET, WIDTH - OFFSET);

class Strategy
{
private:
	Lidar lidar;
	int currentInstruction;
	Point2D currentPoint;
	Point2D *points;
	int arrayLength;
	bool isPulled;
	bool calibrated;
	bool isHome;
	int team;
	int home;
	int chrono;
	Point2D homePOS;
	Movement movement;

public:
	void execute();
	void updatePOS();
	void calibrate();
	void selectTeam(int team);
	void selectHome(int home);
	bool atHome();
	bool isCalibrated();
	void start();
	bool isReady();
	void startTimer();
	void stop();
	void setTable(Point2D *points, int len);
};