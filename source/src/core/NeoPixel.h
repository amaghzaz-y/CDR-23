#pragma once
#include <FastLED.h>

#define LED_PIN 2
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define NUM_LEDS 300

#define BRIGHTNESS 220
#define FRAMES_PER_SECOND 60

class NeoPixel
{
public:
	CRGB leds[NUM_LEDS];
	void setup();
	void changeColor(int color);
};