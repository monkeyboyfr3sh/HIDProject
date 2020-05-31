// 
// 
// 

#include "Program.h"
void initProgram()
{
	//Initialize Consumer API
	Consumer.begin();
}

bool Program::SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr)
{
	ProgScreen = screenPtr;
	ProgVariable = variablePtr;
	return true;
}

bool Program::changeScreen(SSD_13XX *screenPtr)
{
	ProgScreen = screenPtr;
	return true;
}

bool Program::close()
{
	ProgScreen = nullptr;
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
	ProgScreen->println("System volume setup!");	
}

bool Volume::volumePush(bool dir)
{
	//Volume Up
	if (dir) {
		Consumer.write(MEDIA_VOLUME_UP);
		ProgVariable->systemVolume = ProgVariable->systemVolume + ProgVariable->volumeDelta;
		if (ProgVariable->updatescreen == true) {
			ProgScreen->clearScreen();
			ProgScreen->println("System");
			ProgScreen->println("Volume Up!");
		}
	}
	//Volume Down
	else {
		Consumer.write(MEDIA_VOLUME_DOWN);
		ProgVariable->systemVolume = ProgVariable->systemVolume - ProgVariable->volumeDelta;
		if (ProgVariable->updatescreen == true) {
			ProgScreen->clearScreen();
			ProgScreen->println("System");
			ProgScreen->println("Volume Down!");
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
			ProgScreen->clearScreen();
			ProgScreen->println("System");
			ProgScreen->println("Sound");
		}
	}
	else {
		//Display.drawIcon(pause symbol);
		ProgVariable->mute = true;
		if (ProgVariable->updatescreen == true) {
			ProgScreen->clearScreen();
			ProgScreen->println("System");
			ProgScreen->println("Muted");
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