#include <core/Lidar.h>

void Lidar::setup()
{
	lidar.begin(Serial2);
	opponentDetected = false;
	currentPosition = Point2D(0, 0);
}

void Lidar::reconnect()
{
	analogWrite(PIN_LIDAR_MOTOR, 0);
	delay(15);
	rplidar_response_device_info_t info;
	if (IS_OK(lidar.getDeviceInfo(info, 100)))
	{
		Serial.println("Lidar Detected...");
		lidar.startScan();
		analogWrite(PIN_LIDAR_MOTOR, LIDAR_MOTOR_SPEED);
		delay(500);
	}
}

bool Lidar::inRadius(Vec2 point)
{
	float max_angle = angle + (radius / 2);
	float min_angle = angle - (radius / 2);
	if ((point.A >= min_angle) && (point.A <= max_angle) && (point.B <= maxRange))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Vec2 Lidar::scan()
{
	Vec2 point = {-1, -1};
	if (IS_OK(lidar.waitPoint()))
	{
		float a = lidar.getCurrentPoint().angle;
		float d = lidar.getCurrentPoint().distance;
		if (lidar.getCurrentPoint().quality < 10)
		{
			return Vec2(-1, -1);
		}
		return Vec2(a, d);
	}
	else
	{
		Lidar::reconnect();
	}
	return Vec2(-1, -1);
}

void Lidar::detect()
{
	Vec2 point = scan();
	if (Lidar::inRadius(point))
	{
		opponentDetected = true;
	}
	else
	{
		opponentDetected = false;
	}
}

bool Lidar::hasDetected()
{
	return opponentDetected;
}

bool Lidar::isPointNull(Vec2 v)
{
	if (v.A != 0 || v.B != 0)
		return false;
	return true;
}

bool Lidar::Task(Point2D currentPosition)
{
	setCurrentPoint(currentPosition);
	detect();
	if (hasDetected())
	{
		// Serial.println("###-DETECTED-###");
	}
	return hasDetected();
}

void Lidar::setAngle(float _angle)
{
	angle = _angle;
}

void Lidar::setRadius(float _radius)
{
	radius = _radius;
}

void Lidar::setMaxRange(float range)
{
	maxRange = range;
}

bool Lidar::inRange(Vec2 point)
{
	Vec2 vec = PolarVec(point.A, point.B).toVec2();
	Point2D npoint = Point2D(vec.A + currentPosition.X, vec.B + currentPosition.Y);
	if (npoint.Y > X_RANGE_MAX && npoint.Y < 0.0)
	{
		return false;
	}
	if (npoint.Y > Y_RANGE_MAX && npoint.Y < 0.0)
	{
		return false;
	}
	return true;
}

void Lidar::setCurrentPoint(Point2D currentPoint)
{
	currentPosition = currentPoint;
}