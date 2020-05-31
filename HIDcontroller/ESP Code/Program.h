// Program.h
#include <SSD_13XX.h>
#include "HID-Project.h"

#define NUM_PROGRAM 3
#define DEFAULT_DELAY 500
#define VOLUME_INCREMENT 2
#define DEFAULT_VOLUME 100
#define ROWS 1
#define COLS 3


enum Programs {
    PROG_MEDIA,
    PROG_MEDIA_VOLUME
};

//Vars stuff
struct Variable_Struct {
    const int defaultDelay = DEFAULT_DELAY;
    const int defaultVolume = DEFAULT_VOLUME;
    const int volumeDelta = VOLUME_INCREMENT;
    char customKey, lastKey;
    bool newKey;

    uint32_t time;
    int systemVolume;
    bool updatescreen;
    bool paused, mute;
};

void initProgram();

class Program
{
 protected:
     SSD_13XX           *ProgScreen;
     Variable_Struct    *ProgVariable;
     uint16_t           ProgramSelect;

 public:
     bool SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr);
     bool changeScreen(SSD_13XX *screenPtr);
     bool close();
};

class Volume : public Program 
{
public:
    void init();
    
    //Adjust volume up down. 0 = down/1 = up 
    bool volumePush(bool dir);
    //Adjust volume to specific value
    bool setVolume(int inputVolume);
    bool mute();
};

class Media : public Program
{ 
public:
    void init();

    //Play Pause system and update program screen
    bool playPause();
};