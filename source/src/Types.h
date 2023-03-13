#pragma once

class Vec2
{
public:
	int a;
	int b;
	Vec2(int y, int z);
};

class Point2D
{
public:
	int X;
	int Y;
	Point2D(int x, int y);
};

class Steps
{
public:
	Steps(long m1, long m2, long m3);

private:
	long M1;
	long M2;
	long M3;
};

class PolarVec
{
public:
	float angle;
	float distance;
	PolarVec(float angle, float distance);
};