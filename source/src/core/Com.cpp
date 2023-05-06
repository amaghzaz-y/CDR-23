#include "core/Com.h"

void Com::setup(int card_id)
{
	_serial.begin(9600, SWSERIAL_8N1, RXPIN, TXPIN, false, 500, 200);
}