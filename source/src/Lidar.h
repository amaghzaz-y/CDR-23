#pragma once
#include <RPLidar.h>
#include <Types.h>
class Lidar
{
public:
	RPLidar lidar;
	void setup();
	PolarVec detect(int angle, int radius, int range_min, int range_max);

private:
	bool InRadius(PolarVec point, int angle, int radius, int max_range);
	void reconnect();
	PolarVec scan();
	bool isPointNull(PolarVec v);
};