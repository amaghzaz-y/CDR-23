#include <lib/SoftwareSerial/SoftwareSerial.h>
#define RXPIN 12
#define TXPIN 13

class Com
{
	EspSoftwareSerial::UART _serial;
	void setup(int CARD);
};