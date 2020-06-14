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
	Serial.println("base SetProgram");
	ProgScreen = screenPtr;
	ProgVariable = variablePtr;
	active = true;
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
	ProgScreen->println("System volume setup!");	
}

bool Volume::SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr)
{
	SetProgram(screenPtr,variablePtr);
	volumeUpScreen = screenPtr;
	volumeDownScreen = screenPtr;
	volumeMuteScreen = screenPtr;
	return true;
}

bool Volume::volumePush(bool dir)
{
	//Volume Up
	if (dir) {
		Consumer.write(MEDIA_VOLUME_UP);
		ProgVariable->systemVolume = ProgVariable->systemVolume + ProgVariable->volumeDelta;
		if (ProgVariable->updatescreen == true) {
			volumeUpScreen->clearScreen();
			volumeUpScreen->println("System");
			volumeUpScreen->println("Volume Up!");
		}
	}
	//Volume Down
	else {
		Consumer.write(MEDIA_VOLUME_DOWN);
		ProgVariable->systemVolume = ProgVariable->systemVolume - ProgVariable->volumeDelta;
		if (ProgVariable->updatescreen == true) {
			volumeDownScreen->clearScreen();
			volumeDownScreen->println("System");
			volumeDownScreen->println("Volume Down!");
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