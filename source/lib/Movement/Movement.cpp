#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <math.h>
class Movement
{
public:
	typedef struct Point
	{
		int x;
		int y;
	};
	typedef struct Vec2
	{
		int angle;
		int distance;
	};
	typedef struct Steps
	{
		float M1;
		float M2;
		float M3;
	};
	const int PIN_Dir_Motor_1 = 33;
	const int PIN_Stp_Motor_1 = 25;
	const int PIN_Dir_Motor_2 = 26;
	const int PIN_Stp_Motor_2 = 27;
	const int PIN_Dir_Motor_3 = 12;
	const int PIN_Stp_Motor_3 = 14;
	const int PIN_Enable = 13;
	AccelStepper Motor_1;
	AccelStepper Motor_2;
	AccelStepper Motor_3;
	MultiStepper Motors;
	Movement()
	{
		AccelStepper Motor_1(1, PIN_Stp_Motor_1, PIN_Dir_Motor_1);
		AccelStepper Motor_2(1, PIN_Stp_Motor_2, PIN_Dir_Motor_2);
		AccelStepper Motor_3(1, PIN_Stp_Motor_3, PIN_Dir_Motor_3);
	}
	void begin()
	{
		initMotors(3000, 200);
	}
	void Execute(Steps steps)
	{
		long newPOS[3] = {steps.M1,
						  steps.M2,
						  steps.M3};
		pos_reset();
		Motors.moveTo(newPOS);
		while (Motor_1.distanceToGo() != 0 || Motor_2.distanceToGo() != 0 || Motor_3.distanceToGo() != 0)
		{
			Motors.run();
		}
	}
	void setCurrentPOS(Point point)
	{
		CurrentPOS.x = point.x;
		CurrentPOS.y = point.y;
	}
	Point getCurrentPOS()
	{
		return CurrentPOS;
	}

private:
	Point CurrentPOS;
	void initMotors(int max_speed, int acceleration)
	{
		Motor_1.setMaxSpeed(max_speed);
		Motor_1.setAcceleration(acceleration);
		Motor_2.setMaxSpeed(max_speed);
		Motor_2.setAcceleration(acceleration);
		Motor_3.setMaxSpeed(max_speed);
		Motor_3.setAcceleration(acceleration);
		Motors.addStepper(Motor_1);
		Motors.addStepper(Motor_2);
		Motors.addStepper(Motor_3);
	}

	void pos_reset()
	{
		Motor_1.setCurrentPosition(0);
		Motor_2.setCurrentPosition(0);
		Motor_3.setCurrentPosition(0);
	}
	Steps StepsFromVec(Vec2 vec)
	{
		float angle_1 = vec.angle - degToRad(90);
		float angle_2 = vec.angle + degToRad(30);
		float angle_3 = vec.angle + degToRad(150);
		float steps_1 = vec.distance * sin(angle_1);
		float steps_2 = vec.angle * sin(angle_2);
		float steps_3 = vec.angle * sin(angle_3);
		Steps steps = {steps_1, steps_2, steps_3};
		return steps;
	}

	Point XYfromVec(Vec2 vec)
	{
		float x = vec.distance * cos(vec.angle);
		float y = vec.distance * sin(vec.angle);
		Point point = {x, y};
		return point;
	}
	Vec2 VecFromXY(Point point)
	{
		float distance = sqrt(pow(point.x, 2) + pow(point.y, 2));
		float angle = atan2(point.y, point.x);
		Vec2 vec = {angle, distance};
		return vec;
	}
	float degToRad(float degrees)
	{
		float rad = degrees * DEG_TO_RAD;
		return rad;
	}
};