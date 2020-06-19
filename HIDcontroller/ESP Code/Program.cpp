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
	ProgScreen = screenPtr;
	ProgVariable = variablePtr;
	currentTextScale = DEFAULT_TEXT_SCALE;
	ProgScreen->setTextScale(currentTextScale);
	active = true;
	ProgVariable->centerCursor = false;
	return true;
}

bool Program::idle()
{
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
	//Lowers volume until it is certainly a 0. To work, programs must be good to go
	int counter = 0;
	ProgScreen->clearScreen();
	ProgScreen->println("Calibrating");
	ProgScreen->println("System");
	ProgScreen->println("Audio");
	//Disable screen update for calibrate
	ProgVariable->updatescreen = false;
	while (counter < 80) {
		
		volumePush(0);
		
		delay(10);
		counter++;
	}
	ProgVariable->systemVolume = 0;
	setVolume(ProgVariable->defaultVolume);
	ProgVariable->updatescreen = true;

	ProgScreen->clearScreen();
	ProgScreen->println("System");
	ProgScreen->println("volume set to");
	
	ProgScreen->setTextScale(4);
	ProgScreen->println(ProgVariable->systemVolume);
	ProgScreen->setTextScale(currentTextScale);

	initTime = millis();
	while (millis() - initTime < setupDelay) {
		if (ProgVariable->newKey) break;
	}
	ProgScreen->clearScreen();
	ProgScreen->println("System");
	ProgScreen->println("volume setup!");
	delay(2000);
}

bool Volume::SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr)
{
	Program::SetProgram(screenPtr,variablePtr);
	volumeUpScreen = screenPtr;
	volumeDownScreen = screenPtr;
	volumeMuteScreen = screenPtr;
	return true;
}

bool Volume::idle()
{
	if (idleScreen == false) {
		ProgScreen->clearScreen();
		ProgScreen->setTextColor(WHITE);
		ProgScreen->println("Volume");
		idleScreen = true;
	}

	return true;
}

bool Volume::volumePush(bool dir)
{
	//Volume Up
	if (dir) {
		for(int i = 0;i<ProgVariable->volumeDetlaScale;i++) Consumer.write(MEDIA_VOLUME_UP);
		ProgVariable->systemVolume += ProgVariable->volumeDetlaScale*ProgVariable->volumeDelta;
		if (ProgVariable->systemVolume > 100) ProgVariable->systemVolume = 100;
		if (ProgVariable->mute) ProgVariable->mute = false;
		if (ProgVariable->updatescreen == true) {
			volumeUpScreen->clearScreen();
			volumeUpScreen->println("System");
			volumeUpScreen->println("Volume Up!");

			volumeUpScreen->setTextScale(4);
			volumeUpScreen->println(ProgVariable->systemVolume);
			volumeUpScreen->setTextScale(currentTextScale);
		}
	}
	//Volume Down
	else {
		for (int i = 0; i < ProgVariable->volumeDetlaScale; i++) Consumer.write(MEDIA_VOLUME_DOWN);
		ProgVariable->systemVolume -= ProgVariable->volumeDetlaScale*ProgVariable->volumeDelta;
		if (ProgVariable->systemVolume <= 0) {
			ProgVariable->systemVolume = 0;
			ProgVariable->mute = true;
		}
		if (ProgVariable->updatescreen == true) {
			volumeDownScreen->clearScreen();
			volumeDownScreen->println("System");
			volumeDownScreen->println("Volume Down!");

			volumeDownScreen->setTextScale(4);
			volumeDownScreen->println(ProgVariable->systemVolume);
			volumeDownScreen->setTextScale(currentTextScale);
		}
	}
	return true;
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
	
}

bool Media::SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr)
{
	return false;
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