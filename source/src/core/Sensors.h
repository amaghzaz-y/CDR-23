#include <Arduino.h>
#define SENSOR_A_PIN 1
#define SENSOR_B_PIN 2
#define SENSOR_C_PIN 3

const int SIDE_A_ID = 0;
const int SIDE_B_ID = 1;
const int SIDE_C_ID = 2;
class Sensors
{
private:
	bool sensor_a_state;
	bool sensor_b_state;
	bool sensor_c_state;

public:
	void setup();
	bool getSensor(int side_id);
};