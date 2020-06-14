// Program.h
#include <SSD_13XX.h>
#include "HID-Project.h"

#define NUM_PROGRAM 3
#define DEFAULT_DELAY 500
#define VOLUME_INCREMENT 2
#define DEFAULT_VOLUME 100

enum instructions {
    VolumeMute,
    VolumeUp,
    VolumeDown
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

//Currently just activates consumer API
void initProgram();

class Program
{
 protected:
     SSD_13XX           *ProgScreen;
     Variable_Struct    *ProgVariable;
     bool               active;

 public:
     void virtual init();
     virtual bool SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr);
     bool changeScreen(SSD_13XX *screenPtr);
     bool close();
};

class Volume : public Program 
{
protected:
    //Would like to turn into an array at some point but will leave like this for now
    SSD_13XX            *volumeUpScreen;
    SSD_13XX            *volumeDownScreen;
    SSD_13XX            *volumeMuteScreen;
public:
    void init();
    
    //Set inner screen
    bool SetProgram(SSD_13XX *screenPtr, Variable_Struct *variablePtr);
    //Adjust volume up down. 0 = down/1 = up 
    bool volumePush(bool dir);
    //Adjust volume to specific value
    bool setVolume(int inputVolume);
    bool mute();
};

class Media : public Program
{ 
protected:
    //SSD_13XX *nextTrackScreen;
    //SSD_13XX *previousTrackScreen;
public:
    void init();

    //Play Pause system and update program screen
    bool playPause();
};