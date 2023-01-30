#include <Arduino.h>
#include <RPLidar.h>
#define RPLIDAR_MOTOR 26
#define LED_BLUE 27
#define TABLE_HEIGHT 10000 // in mm
#define TABLE_WIDTH 10000  // in mm
RPLidar lidar;
void setup()
{
  Serial.begin(115200);
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  lidar.begin(Serial2);
}

void loop()
{
  int target_radius = 30;
  int target_angle = 210;
  int min_angle = target_angle - (target_radius / 2);
  int max_angle = target_angle + (target_radius / 2);

  if (IS_OK(lidar.waitPoint()))
  {
    float distance = lidar.getCurrentPoint().distance; // distance value in mm unit
    float angle = lidar.getCurrentPoint().angle;       // anglue value in degree
    bool startBit = lidar.getCurrentPoint().startBit;  // whether this point is belong to a new scan
    byte quality = lidar.getCurrentPoint().quality;    // quality of the current measurement
    if ((angle >= min_angle) && (angle <= max_angle) && (distance > 0))
    {
      if (distance < 1000)
      {
        digitalWrite(LED_BLUE, HIGH);
      }
      else
      {
        digitalWrite(LED_BLUE, LOW);
      }
    }
  }
  else
  {
    analogWrite(RPLIDAR_MOTOR, 0);
    delay(15);
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100)))
    {
      Serial.println("Lidar Detected...");
      lidar.startScan();
      analogWrite(RPLIDAR_MOTOR, 150);
      delay(1000);
    }
  }
}