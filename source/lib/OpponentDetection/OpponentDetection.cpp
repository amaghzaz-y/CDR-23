#include "RPLidar.h"
#include <Arduino.h>

class OpponentDetection
{
private:
	int MotorPin = 26;
	int MotorSpeed = 150;
	RPLidar lidar;

public:
	void begin(int motor_pin, int motor_speed, HardwareSerial serial)
	{
		
		this->MotorPin = motor_pin;
		this->MotorSpeed = motor_speed;
		this->lidar.begin(serial);
	}
};

void setLidarSpeed(int NewSpeed)
{
	LIDAR_SPEED = NewSpeed;
}

RPLidarMeasurement GetLidarPoint()
{
	RPLidarMeasurement Point;
	if (IS_OK(lidar.waitPoint()))
	{
		Point = lidar.getCurrentPoint();
	}
	else
	{
		analogWrite(LIDAR_MOTOR, 0);
		delay(15);
		rplidar_response_device_info_t info;
		if (IS_OK(lidar.getDeviceInfo(info, 100)))
		{
			Serial.println("Lidar Detected...");
			lidar.startScan();
			analogWrite(LIDAR_MOTOR, LIDAR_SPEED);
			delay(1000);
		}
	}
	return Point;
}