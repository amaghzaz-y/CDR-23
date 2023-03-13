#include <Lidar.h>

RPLidar lidar;

void Lidar::setup()
{
	lidar.begin(Serial2);
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

bool Lidar::InRadius(PolarVec point, int angle, int radius, int max_range)
{
	int max_angle = angle + (radius / 2);
	int min_angle = angle - (radius / 2);
	if ((point.angle > min_angle) && (point.angle < max_angle) && (point.distance < max_range))
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

PolarVec Lidar::detect(int angle, int radius, int range_min, int range_max)
{
	PolarVec point = scan();
	if (Lidar::InRadius(point, angle, radius, range_max))
		return point;
	PolarVec emptyVec(0, 0);
	return emptyVec;
}

bool isPointNull(PolarVec v)
{
	if (v.angle != 0 || v.distance != 0)
		return false;
	return true;
}