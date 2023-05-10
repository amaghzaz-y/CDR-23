#include "IO.h"

bool IO::InputState(int id)
{
	if (id == ID_TIRETTE)
	{
		return digitalRead(PIN_TIRETTE);
	}
	else if (id == ID_STRAT_BTN)
	{
		return digitalRead(PIN_STRAT);
	}
	else if (id == ID_TEAM_BTN)
	{
		return digitalRead(PIN_TEAM);
	}
}