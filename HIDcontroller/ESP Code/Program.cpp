// 
// 
// 

#include "Program.h"

void initProgram()
{
	//Initialize Consumer API
	Consumer.begin();
}

void Program::SetProgram(SSD_13XX *screenPtr,Variable_Struct *variablePtr,uint16_t ProgramSelectIn)
{
	ProgScreen = screenPtr;
	ProgVariable = variablePtr;
	ProgramSelect = ProgramArray(ProgramSelectIn);
}

bool Program::close()
{
	ProgScreen = nullptr;
	return true;
}

bool Program::playPause()
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

bool Program::volumePush(bool dir)
{
	//Volume Up
	if (dir) {
		Consumer.write(MEDIA_VOLUME_UP);
		//Media Screen up icon
		ProgVariable->systemVolume = ProgVariable->systemVolume + ProgVariable->volumeDelta;
		ProgScreen->clearScreen();
		ProgScreen->println("System");
		ProgScreen->println("Volume Up!");
	}
	//Volume Down
	else {
		Serial.println("Adjusting volume");
		Consumer.write(MEDIA_VOLUME_DOWN);
		//Media Screen down icon
		Serial.println("Adjusting vars");
		ProgVariable->systemVolume = ProgVariable->systemVolume - ProgVariable->volumeDelta;
		Serial.println("Clearing screen");
		//ProgScreen->clearScreen();
		Serial.println("Printing to screen");
		ProgScreen->println("System");
		ProgScreen->println("Volume Down!");
	}
}

bool Program::setVolume(int inputVolume)
{
	//Slide Volume Up
	while (ProgVariable->systemVolume < inputVolume) {
		delay(10);
		volumePush(1);
	}
	//Slide Volume Down
	while (ProgVariable->systemVolume > inputVolume) {
		delay(10);
		volumePush(0);
	}
}
