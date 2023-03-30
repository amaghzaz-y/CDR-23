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
	int max_angle = angle + (radius / 2);
	int min_angle = angle - (radius / 2);
	if ((point.angle > min_angle) && (point.angle < max_angle) && (point.distance < maxRange) && (point.distance != 0.0f))
		return true;
	return false;
}

PolarVec Lidar::scan()
{
	PolarVec point = {0, 0};
	if (IS_OK(lidar.waitPoint()))
	{
		point.angle = lidar.getCurrentPoint().angle;
		point.distance = lidar.getCurrentPoint().distance;
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
		opponentDetected = true;
	opponentDetected = false;
}

bool Lidar::hasDetected()
{
	return opponentDetected;
}

bool Lidar::isPointNull(PolarVec v)
{
	if (v.angle != 0 || v.distance != 0)
		return false;
	return true;
}

void Lidar::Task(void *params)
{
	for (;;)
	{
		// detect();
		// Serial.println(opponentDetected);
		PolarVec vec = scan();
		Serial.print("Distance : ");
		Serial.print(vec.distance);
		Serial.print("  -  angle : ");
		Serial.println(vec.angle);
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