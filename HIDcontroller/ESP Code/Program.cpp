// 
// 
// 

#include "Program.h"
void initProgram()
{
	//Initialize Consumer API
	Consumer.begin();
}


void Program::init()
{
	Serial.println("This class has the wrong type");
}

bool Program::SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr)
{
	ConsoleScreen = screenPtr;
	//Defaults screen array to console screen but checks if already assigned
	for (int i = 0; i < SCREEN_ARRAY_COUNT; i++) {
		if (!ScreenArray[i]) ScreenArray[i] = ConsoleScreen;
	}
	DeviceVariable = variablePtr;
	active = true;
	return true;
}

bool Program::SetScreenArray(SSD_13XX *screenPtr, uint8_t AltSelect)
{
	ScreenArray[AltSelect] = screenPtr;
	return true;
}

bool Program::changeScreen(SSD_13XX *screenPtr)
{
	ConsoleScreen = screenPtr;
	return true;
}

bool Program::close()
{
	ConsoleScreen = nullptr;
	for (int i = 0; i < SCREEN_ARRAY_COUNT; i++) ScreenArray[i] = nullptr;

	active = false;
	return true;
}

//Volume
/*--------------------------------------------------------------------------------------------------------*/
void Volume::init()
{
	Serial.println("This is a volume program");
	
	//Lowers volume until it is certainly a 0. To work, programs must be good to go
	volumePush(0);
	int counter = 0;
	//Puts it on the screen once. Then doesn't update screen till after.
	DeviceVariable->updatescreen = false;
	while (counter < 100) {
		volumePush(0);
		delay(10);
		counter++;
	}
	DeviceVariable->updatescreen = true;
	DeviceVariable->systemVolume = 0;

	setVolume(DeviceVariable->defaultVolume);
	ConsoleScreen->println("System volume setup!");	
}

bool Volume::SetScreenArray(SSD_13XX *screenPtr, int input)
{
	ScreenArray[input] = screenPtr;
	ScreenArray[input]->println("Volume");
	return true;
}

bool Volume::volumePush(bool dir)
{
	//Volume Up
	if (dir) {

		Consumer.write(MEDIA_VOLUME_UP);
		DeviceVariable->systemVolume = DeviceVariable->systemVolume + DeviceVariable->volumeDelta;
		if (DeviceVariable->updatescreen == true) {
			ScreenArray[Volume::instructions(Up)]->clearScreen();
			ScreenArray[Volume::instructions(Up)]->println("System");
			ScreenArray[Volume::instructions(Up)]->println("Volume Up!");
		}
		
		lastKeylocal = 'Up';
	}
	//Volume Down
	else {

		Consumer.write(MEDIA_VOLUME_DOWN);
		DeviceVariable->systemVolume = DeviceVariable->systemVolume - DeviceVariable->volumeDelta;
		if (DeviceVariable->updatescreen == true) {
			ScreenArray[Volume::instructions(Down)]->clearScreen();
			ScreenArray[Volume::instructions(Down)]->println("System");
			ScreenArray[Volume::instructions(Down)]->println("Volume Down!");
		}

		lastKeylocal = 'Down';
	}
}

bool Volume::setVolume(int inputVolume)
{
	bool first = true;
	//Slide Volume Up
	while (DeviceVariable->systemVolume < inputVolume) {
		delay(10);
		volumePush(1);
		//Updates the screen once. Eventually i'd like to make this display a bar
		if (first) {
			first = false;
			DeviceVariable->updatescreen = false;
		}
	}
	//Slide Volume Down
	while (DeviceVariable->systemVolume > inputVolume) {
		delay(10);
		volumePush(0);
		//Updates the screen once. Eventually i'd like to make this display a bar
		if (first) {
			first = false;
			DeviceVariable->updatescreen = false;
		}
	}
	DeviceVariable->updatescreen = true;
}
bool Volume::mute()
{
	Consumer.write(MEDIA_VOLUME_MUTE);
	if (DeviceVariable->mute) {
		DeviceVariable->mute = false;
		if (DeviceVariable->updatescreen == true) {
			ScreenArray[Volume::instructions(Mute)]->clearScreen();
			ScreenArray[Volume::instructions(Mute)]->println("System");
			ScreenArray[Volume::instructions(Mute)]->println("Sound");
		}
	}
	else {
		//Display.drawIcon(pause symbol);
		DeviceVariable->mute = true;
		if (DeviceVariable->updatescreen == true) {
			ScreenArray[Volume::instructions(Mute)]->clearScreen();
			ScreenArray[Volume::instructions(Mute)]->println("System");
			ScreenArray[Volume::instructions(Mute)]->println("Muted");
		}
	}
}

//Media
/*--------------------------------------------------------------------------------------------------------*/
void Media::init()
{
	Serial.println("This is a media program");
}

bool Media::playPause()
{
	Consumer.write(MEDIA_PLAY_PAUSE);
	if (DeviceVariable->paused) {
		//Display.drawIcon(play symbol);
		DeviceVariable->paused = false;
	}
	else {
		//Display.drawIcon(pause symbol);
		DeviceVariable->paused = true;
	}
}