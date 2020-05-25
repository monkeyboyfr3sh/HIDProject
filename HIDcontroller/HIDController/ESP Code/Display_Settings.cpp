#include "Display_Settings.h"

void Display_Settings::begin()
{
	for (int i = 0; i < screenCount; i++) {
		ScreenArray[i].begin();
		if (DEBUG)
		{
			Serial.print("Initializing Screen ");
			Serial.println(i);
		}
	}
	
	sdSetup = SDCard.begin();
	if (DEBUG) {
		Serial.print("SD Card Status: ");
		Serial.println(sdSetup);
	}
}

void Display_Settings::playIcon(int OutputDelay)
{
	for (int i = 0; i < screenCount; i++) {
		ScreenArray[i].drawIcon(0, 0, &spkOn, 3, WHITE, BLACK, true);
	}
	//I don't like having a simple delay but it will work for now.
	delay(OutputDelay);
	for (int i = 0; i < screenCount; i++) {
		ScreenArray[i].drawIcon(0, 0, &spkOff, 3, RED, BLACK, true);
	}
	delay(OutputDelay);
}

void Display_Settings::setImageAll()
{
	delay(200);
	for (int i = 0; i < screenCount; i++) {
		ScreenArray[i].drawImage(0,0, &wifi2s);
	}
	delay(200);
	for (int i = 0; i < screenCount; i++) {
		ScreenArray[i].drawImage(0, 0, &wifi2sr);
	}
	delay(200);
}

void Display_Settings::setIcon(int ScreenSelect, int IconSelect, int Color1, int Color2)
{
}

void Display_Settings::setIcon(int IconSelect,int Color1, int Color2)
{
	for (int i = 0; i < screenCount; i++) {
		ScreenArray[i].drawIcon(0, 0, &spkOn, 1, Color1, Color2, true);
	}
}//&Resource.iconArray[IconSelect]

void Display_Settings::setTextScale(int ScreenSelect, int Scale)
{
	ScreenArray[ScreenSelect].setTextScale(Scale);
}

void Display_Settings::setTextScale(int Scale)
{
	for (int i = 0; i < screenCount; i++) {
		ScreenArray[i].setTextScale(Scale);
	}
}

void Display_Settings::countScreen()
{
	for (int i = 0; i < screenCount; i++) {
		ScreenArray[i].println("This is screen: ");
		ScreenArray[i].println(i);
	}
}

void Display_Settings::clearScreen(int ScreenSelect)
{
	ScreenArray[ScreenSelect].clearScreen();
}
void Display_Settings::clearScreen()
{
	for (int i = 0; i < screenCount; i++) {
		ScreenArray[i].clearScreen();
	}
}

void Display_Settings::setRotation(int ScreenSelect, int ScreenRotation)
{
	ScreenArray[ScreenSelect].setRotation(ScreenRotation);
}

void Display_Settings::setRotation(int ScreenRotation)
{
	for (int i = 0; i < screenCount; i++)
	{
		ScreenArray[i].setRotation(ScreenRotation);
	}
}
