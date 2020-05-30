#include "DeviceController.h"

void DeviceController::begin()
{
	Consumer.begin();
	Display.begin();
	
	sdSetup = SDCard.begin();
	if (DEBUG) {
		Serial.print("SD Card Status: ");
		Serial.println(sdSetup);
	}
	
	/*
	//Demo of selecting a file and saving
	CurrentFile = &SD.open("setup.txt", FILE_READ);
	SDCard.returnLine(CurrentFile);
	CurrentFile->close();
	CurrentFile = &SD.open("/");
	SDCard.loadIcons(CurrentFile);
	CurrentFile->close();
	*/

	//playPause vars
	time = millis();
	paused = false;

	//Saftey clear screen
	Display.clearScreen();
}

void DeviceController::begin(int SetRotationAll)
{
	begin();
	Display.setRotation(SetRotationAll);
}

void DeviceController::controllerDemo()
{
	Display.setTextScale(2);
	playPause(readKey());
}

char *DeviceController::readKey() {
	customKey = customKeypad.getKey();
	if (customKey) {
		if (customKey == lastKey) newKey = false;
		else newKey = true;

		lastKey = customKey;
		return &customKey;
	}
	return nullptr;
}

void DeviceController::playPause(char *input)
{
	if (input) {
		if (*input == '1') {
			Consumer.write(MEDIA_VOLUME_MUTE);
			if(newKey){
				Display.clearScreen();
				Display.printText(0, "Muting");
				Display.printText(0, "System");
			}
		}
		if (*input == '2') {
			Consumer.write(MEDIA_VOLUME_UP);
			Consumer.write(MEDIA_VOLUME_UP);
			if (newKey) {
				Display.clearScreen();
				Display.printText(1, "System");
				Display.printText(1, "Volume Up");
			}
		}
		if (*input == '3') {
			Consumer.write(MEDIA_VOLUME_DOWN);
			Consumer.write(MEDIA_VOLUME_DOWN);
			if (newKey) {
				Display.clearScreen();
				Display.printText(2, "System");
				Display.printText(2, "Volume Down");
			}
		}
	}
}

