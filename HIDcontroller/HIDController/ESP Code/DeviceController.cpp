#include "DeviceController.h"

void DeviceController::begin()
{
	Consumer.begin();
	Display.begin();
	time = millis();
	paused = false;
}

void DeviceController::begin(int SetRotationAll)
{
	begin();
	Display.setRotation(SetRotationAll);
}

void DeviceController::setRotation(int Screen, int Rotation)
{
	Display.setRotation(Screen, Rotation);
}

void DeviceController::setTextScale(int ScreenSlect, int Scale)
{
	Display.setTextScale(ScreenSlect, Scale);
}

void DeviceController::setTextScale(int Scale)
{
	Display.setTextScale(Scale);
}

void DeviceController::playPause()
{
	if ((millis() - time) > defaultDelay) {
		if (paused) {
			Display.setIcon(0, WHITE, BLACK);
			Consumer.write(MEDIA_PLAY_PAUSE);
			paused = false;
		}
		else {
			Display.setIcon(1, RED, BLACK);
			Consumer.write(MEDIA_PLAY_PAUSE);
			paused = true;
		}
		time = millis();
	}
}
void DeviceController::playPause(int Delay)
{
	if ((millis() - time) > Delay) {
		if (paused) {
			Display.setIcon(0, WHITE, BLACK);
			Consumer.write(MEDIA_PLAY_PAUSE);
			paused = false;
		}
		else {
			Display.setIcon(1, RED, BLACK);
			Consumer.write(MEDIA_PLAY_PAUSE);
			paused = true;
		}
		time = millis();
	}
}

void DeviceController::controllerDemo()
{
	Display.clearScreen();
	
	Display.countScreen();
}

