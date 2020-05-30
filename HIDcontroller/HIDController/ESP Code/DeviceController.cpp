#include "DeviceController.h"

void DeviceController::begin()
{	
	Serial.println(115200);
	setupHardware();
	setupVars();

	//Saftey clear screen
	Display.clearScreen();
}

void DeviceController::begin(int SetRotationAll)
{
	begin();
	Display.setRotation(SetRotationAll);
}

bool DeviceController::setupHardware()
{
	//Initialize Consumer API
	Consumer.begin();
	int counter = 0;
	while (counter < 100) {
		volumePush(0);
		counter++;
	}
	setVolume(defaultVolume);
	//Initialize Display array
	Display.begin();
	//Initialize SD Card Reader
	sdSetup = SDCard.begin();

	/*
	//Demo of selecting a file and saving
	CurrentFile = &SD.open("setup.txt", FILE_READ);
	SDCard.returnLine(CurrentFile);
	CurrentFile->close();
	CurrentFile = &SD.open("/");
	SDCard.loadIcons(CurrentFile);
	CurrentFile->close();
	*/
	return true;
}

bool DeviceController::setupVars()
{
	time = millis();
	paused = false;
	return true;
}

void DeviceController::controllerDemo()
{
	Display.setTextScale(2);
	buttonRead(readKey());
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

void DeviceController::playPause()
{
	Consumer.write(MEDIA_PLAY_PAUSE);
	if (paused) {
		//Display.drawIcon(play symbol);
		paused = false;
	}
	else {
		//Display.drawIcon(pause symbol);
		paused = true;
	}
}
void DeviceController::volumePush(bool dir)
{
	//Volume Up
	if (dir) {
		Consumer.write(MEDIA_VOLUME_UP);
		//Media Screen up icon
		systemVolume = systemVolume + volumeDelta;
	}
	//Volume Down
	else {
		Consumer.write(MEDIA_VOLUME_DOWN);
		//Media Screen down icon
		systemVolume = systemVolume - volumeDelta;
	}
}

void DeviceController::setVolume(int inputVolume)
{
	//Slide Volume Up
	while (systemVolume < inputVolume) {
		delay(10);
		volumePush(1);
	}
	//Slide Volume Down
	while (systemVolume > inputVolume) {
		delay(10);
		volumePush(0);
	}
}

void DeviceController::buttonRead(char *input)
{
	if (input) {
		if (*input == '1') {
			playPause();
			if (newKey) {
				Display.clearScreen();
				Display.printText(0, "Muting");
				Display.printText(0, "System");
			}
		}
		if (*input == '2') {
			volumePush(1);
			if (newKey) {
				Display.clearScreen();
				Display.printText(1, "System");
				Display.printText(1, "Volume Up");
			}
		}
		if (*input == '3') {
			volumePush(0);
			if (newKey) {
				Display.clearScreen();
				Display.printText(2, "System");
				Display.printText(2, "Volume Down");
			}
		}
	}
}

