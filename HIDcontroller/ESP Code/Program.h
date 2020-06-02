// Program.h
#include <SSD_13XX.h>
#include "HID-Project.h"

#define NUM_PROGRAM 3
#define DEFAULT_DELAY 500
#define VOLUME_INCREMENT 2
#define DEFAULT_VOLUME 100
#define SCREEN_ARRAY_COUNT 3
#define DEFAULT_MSG_COUNT 5

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

//Currently just activates consumer API
void initProgram();

class Program
{
 protected:
     SSD_13XX           *ConsoleScreen;
     SSD_13XX           *ScreenArray[SCREEN_ARRAY_COUNT];
     Variable_Struct    *ProgVariable;
     bool               active;

 public:
     void virtual init();
     virtual bool SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr);
     virtual bool SetScreenArray(SSD_13XX *screenPtr, uint8_t AltSelect);
     bool changeScreen(SSD_13XX *screenPtr);
     bool close();
};

class Volume : public Program 
{
protected:
    char msg1 = 'Test';


public:
    enum instructions {
        Mute = 0,
        Up = 1,
        Down = 2
    };

    void init();
    bool SetScreenArray(SSD_13XX *screenPtr, int input);
    //Adjust volume up down. 0 = down/1 = up, Outputs to AltDisply 0
    bool volumePush(bool dir);
    //Adjust volume to specific value
    bool setVolume(int inputVolume);
    bool mute();
};

class Media : public Program
{ 
public:
    void init();
    bool SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr);
    //Play Pause system and update program screen
    bool playPause();
};