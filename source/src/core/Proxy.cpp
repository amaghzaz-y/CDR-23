#include "core/Proxy.h"

void Proxy::setup(int card_id)
{
	if (card_id == 0)
	{
		_serial.begin(9600, SWSERIAL_8N1, RXPIN, TXPIN, false, 500, 200);
	}
	else if (card_id == 1)
	{
		_serial.begin(9600, SWSERIAL_8N1, RXPIN, TXPIN, false, 500, 200);
	}
	else
	{
		Serial.println("error card_id");
		while (1)
			;
	}
}

void Proxy::start(int card_id)
{
	if (card_id == 0)
	{
		String ds = _serial.readStringUntil('\n');
		_serial.flush();
		if (_serial.availableForWrite())
		{
				}
	}
};
