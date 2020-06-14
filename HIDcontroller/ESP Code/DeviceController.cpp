#include "DeviceController.h"

void DeviceController::begin()
{	
	Serial.begin(115200);
	delay(1000);

	setup();

	Display.clearScreen();
}

void DeviceController::begin(int SetRotationAll)
{
	begin();
	Display.setRotation(SetRotationAll);
}

bool DeviceController::setup()
{
	//Initialize Display array, this is needed for programs. This is why this is done here.
	Display.begin();
	Display.setTextScale(2);

	//Currently just starts the consumer API
	initProgram();

	//Setting up struct variables as needed
	DeviceVars.time = millis();
	DeviceVars.updatescreen = true;
	DeviceVars.paused = false;
	DeviceVars.mute = false;

	//Setting the programs. This gives needed pointers to the program class.
	//At this point screens should be initialized and ready to use.
	//MediaProg.SetProgram(&(Display.ScreenArray[0]), &DeviceVars);
	//MediaProg.init();

	VolumeProg.SetProgram(&(Display.ScreenArray[0]), &DeviceVars);
	//VolumeProg.init();

	//Initialize SD Card Reader
	sdSetup = SDCard.begin();
	Serial.println("Finished setup");
	return true;
}

void DeviceController::controllerDemo()
{
	//Serial.println("loop");
	buttonRead(readKey());
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
			//VolumeProg.mute();
			Serial.println("1");
		}
		if (*input == '2') {
			//VolumeProg.volumePush(1);
			Serial.println("2");
		}
		if (*input == '3') {
			//VolumeProg.volumePush(0);
			Serial.println("3");
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