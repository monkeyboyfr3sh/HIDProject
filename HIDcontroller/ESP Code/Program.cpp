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
	for (int i = 0; i < SCREEN_ARRAY_COUNT; i++) ScreenArray[i] = screenPtr;
	ProgVariable = variablePtr;
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
	ProgVariable->updatescreen = false;
	while (counter < 100) {
		volumePush(0);
		delay(10);
		counter++;
	}
	ProgVariable->updatescreen = true;
	ProgVariable->systemVolume = 0;

	setVolume(ProgVariable->defaultVolume);
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
		ProgVariable->systemVolume = ProgVariable->systemVolume + ProgVariable->volumeDelta;
		if (ProgVariable->updatescreen == true) {
			ScreenArray[instructions(Up)]->clearScreen();
			ScreenArray[instructions(Up)]->println("System");
			ScreenArray[instructions(Up)]->println("Volume Up!");
		}
	}
	//Volume Down
	else {
		Consumer.write(MEDIA_VOLUME_DOWN);
		ProgVariable->systemVolume = ProgVariable->systemVolume - ProgVariable->volumeDelta;
		if (ProgVariable->updatescreen == true) {
			ScreenArray[instructions(Down)]->clearScreen();
			ScreenArray[instructions(Down)]->println("System");
			ScreenArray[instructions(Down)]->println("Volume Down!");
		}
	}
}

bool Volume::setVolume(int inputVolume)
{
	bool first = true;
	//Slide Volume Up
	while (ProgVariable->systemVolume < inputVolume) {
		delay(10);
		volumePush(1);
		//Updates the screen once. Eventually i'd like to make this display a bar
		if (first) {
			first = false;
			ProgVariable->updatescreen = false;
		}
	}
	//Slide Volume Down
	while (ProgVariable->systemVolume > inputVolume) {
		delay(10);
		volumePush(0);
		//Updates the screen once. Eventually i'd like to make this display a bar
		if (first) {
			first = false;
			ProgVariable->updatescreen = false;
		}
	}
	ProgVariable->updatescreen = true;
}
bool Volume::mute()
{
	Consumer.write(MEDIA_VOLUME_MUTE);
	if (ProgVariable->mute) {
		ProgVariable->mute = false;
		if (ProgVariable->updatescreen == true) {
			ScreenArray[instructions(Mute)]->clearScreen();
			ScreenArray[instructions(Mute)]->println("System");
			ScreenArray[instructions(Mute)]->println("Sound");
		}
	}
	else {
		//Display.drawIcon(pause symbol);
		ProgVariable->mute = true;
		if (ProgVariable->updatescreen == true) {
			ScreenArray[instructions(Mute)]->clearScreen();
			ScreenArray[instructions(Mute)]->println("System");
			ScreenArray[instructions(Mute)]->println("Muted");
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
	if (ProgVariable->paused) {
		//Display.drawIcon(play symbol);
		ProgVariable->paused = false;
	}
	else {
		//Display.drawIcon(pause symbol);
		ProgVariable->paused = true;
	}
}