#include <types/Point2D.h>
Point2D::Point2D(int x, int y)
{
	X = x;
	Y = y;
}

Vec2 Point2D::ToPolarVec()
{
	float distance = sqrt(pow(X, 2) + pow(Y, 2));
	float angle = atan2(Y, X);
	Vec2 vec(angle, distance);
	return vec;
}