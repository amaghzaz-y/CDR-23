#include "RPLidar.h"
#include <Arduino.h>

class OpponentDetection
{
private:
	int MotorPin = 26;
	int MotorSpeed = 150;
	RPLidar lidar;
	void LidarReconnect()
	{
		analogWrite(this->MotorPin, 0);
		delay(15);
		rplidar_response_device_info_t info;
		if (IS_OK(lidar.getDeviceInfo(info, 100)))
		{
			Serial.println("Lidar Detected...");
			lidar.startScan();
			analogWrite(this->MotorPin, this->MotorSpeed);
			delay(500);
		}
	}

public:
	void begin(int motor_pin, int motor_speed, HardwareSerial serial)
	{

		this->MotorPin = motor_pin;
		this->MotorSpeed = motor_speed;
		this->lidar.begin(serial);
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
			LidarReconnect();
		}
		return Point;
	}
};
