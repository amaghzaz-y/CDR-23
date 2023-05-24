#include "NeoPixel.h"

void NeoPixel::setup()
{
	delay(500);
	FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(BRIGHTNESS);
	FastLED.clear(true);
	for (int i = 0; i < NUM_LEDS; i++)
	{
		// For each pixel...
		leds[i] = CRGB::Red;
		FastLED.show();
		delay(1);
	}
}

// 0 for red, 1 for green, 2 for blue, 3 for while
void NeoPixel::changeColor(int color)
{
	if (color == 0)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::Red;
		}
		FastLED.show();
	}
	if (color == 1)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::Green;
			FastLED.show();
		}
	}
	if (color == 2)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::Blue;
			FastLED.show();
		}
	}
	if (color == 3)
	{
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i] = CRGB::White;
			FastLED.show();
		}
	}
}