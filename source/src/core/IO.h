#include <Arduino.h>

#define ID_TIRETTE 0
#define ID_TEAM_BTN 1
#define ID_INIT_BTN 2
#define ID_STRAT_BTN 3
#define PIN_TIRETTE 32
#define PIN_INIT 34
#define PIN_TEAM 35
#define PIN_STRAT 2

class IO
{
private:
	bool tirette;
	bool teamBtn;
	bool initBtn;
	bool stratBtn;

public:
	bool InputState(int input_id);
};