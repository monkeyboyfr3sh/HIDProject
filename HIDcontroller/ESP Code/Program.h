// Program.h
#include <SSD_13XX.h>
#include "HID-Project.h"

#define NUM_PROGRAM 3
#define DEFAULT_DELAY 500
#define VOLUME_INCREMENT 2
#define DEFAULT_VOLUME 100
#define ROWS 1
#define COLS 3


enum ProgramArray {
    PROG_MEDIA_MUTE,
    PROG_MEDIA_VOLUME
};

//Vars stuff
struct Variable_Struct {
    const int defaultDelay = DEFAULT_DELAY;
    const int defaultVolume = DEFAULT_VOLUME;
    const int volumeDelta = VOLUME_INCREMENT;
    char customKey, lastKey;
    int time, systemVolume;
    bool paused, mute;
    bool newKey;
};

void initProgram();

class Program
{
 protected:
     SSD_13XX           *ProgScreen;
     Variable_Struct    *ProgVariable;
     uint16_t           ProgramSelect;



 public:
	void SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr, uint16_t ProgramSelectIn);
    bool close();
    //Play Pause system and update program screen
    bool playPause();
    //Adjust volume up down. 0 = down/1 = up 
    bool volumePush(bool dir);
    //Adjust volume to specific value
    bool setVolume(int inputVolume);
    //changeScreen(SSD_13XX *screenPtr, uint16_t ProgramSelect);
};