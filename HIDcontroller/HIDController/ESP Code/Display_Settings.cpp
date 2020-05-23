#include "Display_Settings.h"

void Display_Settings::begin()
{
	SPI.begin(_sclk, _miso, _mosi, _cs);
	for (int i = 0; i < NUM_DISPLAY; i++) {
		DisplayArray[i].begin();
		if (DEBUG)
		{
			Serial.print("Initializing display ");
			Serial.println(i);
		}
	}
}

void Display_Settings::playIconAll(int outputdelay)
{
	for (int i = 0; i < NUM_DISPLAY; i++) {
		DisplayArray[i].drawIcon(0, 0, &spkOn, 3, WHITE, BLACK, true);
	}
	//I don't like having a simple delay but it will work for now.
	delay(outputdelay);
	for (int i = 0; i < NUM_DISPLAY; i++) {
		DisplayArray[i].drawIcon(0, 0, &spkOff, 3, RED, BLACK, true);
	}
	delay(outputdelay);
}

void Display_Settings::setTextScaleAll(int newscale)
{
	for (int i = 0; i < NUM_DISPLAY; i++) {
		DisplayArray[i].setTextScale(newscale);
	}
}

void Display_Settings::countDisplay()
{
	for (int i = 0; i < NUM_DISPLAY; i++) {
		DisplayArray[i].println("This is display: ");
		DisplayArray[i].println(i);
	}
}

void Display_Settings::clearDisplay()
{
	for (int i = 0; i < NUM_DISPLAY; i++) {
		DisplayArray[i].clearScreen();
	}
}

void Display_Settings::setRotationAll(int DisplayRotation)
{
	for (int i = 0; i < NUM_DISPLAY; i++)
	{
		DisplayArray[i].setRotation(DisplayRotation);
	}
}

void Display_Settings::setRotation(int DisplaySelect, int DisplayRotation)
{
	DisplayArray[DisplaySelect].setRotation(DisplayRotation);
}