#include "DeviceController.h"

void DeviceController::begin()
{	
	Serial.println(115200);
	delay(1000);
	Serial.println("Setting up hardware");
	setupHardware();
	Serial.println("Setting up vars");
	setupVars();
	
	Serial.println("Setting up Media Program");
	Media.SetProgram(&Display.ScreenArray[0], &DeviceVars, 0);

	Serial.println("Setting up Media Program");
	Volume.SetProgram(&Display.ScreenArray[1], &DeviceVars, 1);

	Display.clearScreen();
}

void DeviceController::begin(int SetRotationAll)
{
	begin();
	Display.setRotation(SetRotationAll);
}

bool DeviceController::setupHardware()
{
	int counter = 0;
	Serial.println("initing program");
	initProgram();
	Serial.println("Initializing system volume");
	while (counter < 100) {
		Serial.println("loop");
		Volume.volumePush(0);
		delay(100);
		counter++;
	}
	Volume.setVolume(DeviceVars.defaultVolume);
	//Initialize Display array
	Display.begin();
	//Initialize SD Card Reader
	sdSetup = SDCard.begin();

	return true;
}

bool DeviceController::setupVars()
{
	DeviceVars.time = millis();
	DeviceVars.paused = false;
	return true;
}

void DeviceController::controllerDemo()
{
	Display.setTextScale(2);
	//buttonRead(readKey());
}

char *DeviceController::readKey() {
	DeviceVars.customKey = customKeypad.getKey();
	if (DeviceVars.customKey) {
		if (DeviceVars.customKey == DeviceVars.lastKey) DeviceVars.newKey = false;
		else DeviceVars.newKey = true;

		DeviceVars.lastKey = DeviceVars.customKey;
		return &DeviceVars.customKey;
	}
	return nullptr;
}

void DeviceController::buttonRead(char *input)
{
	if (input) {
		if (*input == '1') {
			Media.playPause();
		}
		if (*input == '2') {
			Volume.volumePush(1);
		}
		if (*input == '3') {
			Volume.volumePush(0);
		}
	}
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