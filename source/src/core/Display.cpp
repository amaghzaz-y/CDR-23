#include <core/Display.h>

Display::Display() : lcd(0x3F, 20, 4)
{
}
void Display::setup()
{
	// (0x3F, 16, 2)

	lcd.init(PIN_SDA, PIN_SCL); // initialize the lcd to use user defined I2C pins
	lcd.backlight();
}

void Display::Show(String row0, String row1, String row2, String row3)
{
}

void Display::Test()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.println("hello MF");
	lcd.display();
}