#include "DeviceController.h"

void DeviceController::begin()
{	
	Serial.begin(115200);
	delay(1000);

	DeviceVars.deviceSetup=setup();

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
	VolumeProg.volumeMuteScreen = &(Display.ScreenArray[0]);
	VolumeProg.volumeUpScreen = &(Display.ScreenArray[1]);
	VolumeProg.volumeDownScreen = &(Display.ScreenArray[1]);
	VolumeProg.init();

	//Initialize SD Card Reader
	sdSetup = SDCard.begin();
	return true;
}

void DeviceController::controllerDemo()
{
	buttonRead();
}

bool DeviceController::readKey() {
	char input = customKeypad.getKey();

	if (input) {
		DeviceVars.lastKey =DeviceVars.customKey;
		DeviceVars.customKey = input;
		if (DeviceVars.customKey == DeviceVars.lastKey) DeviceVars.newKey = false;
		else DeviceVars.newKey = true;
		return true;
	}
	return false;
}

void DeviceController::buttonRead()
{
	if(readKey()){
		if (DeviceVars.customKey == '1') VolumeProg.mute();
		if (DeviceVars.customKey == '2') VolumeProg.volumePush(1);
		if (DeviceVars.customKey == '3') VolumeProg.volumePush(0);
		if (DeviceVars.customKey == '4') VolumeProg.mute();
		if (DeviceVars.customKey == '5') VolumeProg.volumePush(1);
		if (DeviceVars.customKey == '6') VolumeProg.volumePush(0);
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