#include <core/Lidar.h>

void Lidar::setup()
{
	lidar.begin(Serial2);
	opponentDetected = false;
}

void Lidar::reconnect()
{
	analogWrite(LIDAR_MOTOR_PIN, 0);
	delay(15);
	rplidar_response_device_info_t info;
	if (IS_OK(lidar.getDeviceInfo(info, 100)))
	{
		Serial.println("Lidar Detected...");
		lidar.startScan();
		analogWrite(LIDAR_MOTOR_PIN, LIDAR_MOTOR_SPEED);
		delay(500);
	}
}

bool Lidar::inRadius(PolarVec point)
{
	float max_angle = angle + (radius / 2);
	float min_angle = angle - (radius / 2);
	if ((point.getAngle() >= min_angle) && (point.getAngle() <= max_angle) && (point.getDistance() <= maxRange) && (point.getDistance() != 0.0f))
	{
		return true;
	}
	else
	{
		return false;
	}
}

PolarVec Lidar::scan()
{
	PolarVec point = {0, 0};
	if (IS_OK(lidar.waitPoint()))
	{
		float a = lidar.getCurrentPoint().angle;
		float d = lidar.getCurrentPoint().distance;
		PolarVec cp = PolarVec(a, d);
	}
	else
	{
		Lidar::reconnect();
	}
	return point;
}

void Lidar::detect()
{
	PolarVec point = scan();
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

bool Lidar::isPointNull(PolarVec v)
{
	if (v.getAngle() != 0 || v.getDistance() != 0)
		return false;
	return true;
}

void Lidar::Task()
{
	detect();
	if (hasDetected())
	{
		Serial.println("###-DETECTED-###");
	}
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