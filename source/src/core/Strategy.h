#include "types/Point2D.h"
#define SQUARE 500

class Strategy
{
	int currentInstruction;
	Point2D currentPoint;
	Point2D *points;
	void Execute();
	void updatePOS();
	void calibrate();
};