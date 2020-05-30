// DeviceController.h
#include <Keypad.h>
#include "Display_Settings.h"
#include "SD_Reader.h"
#include "HID-Project.h"
#include "Debug.h"

#define DEFAULT_DELAY 500
#define VOLUME_INCREMENT 2
#define DEFAULT_VOLUME 100
#define ROWS 1
#define COLS 3

class DeviceController
{
 protected:
     Display_Settings   Display;
     SD_Reader          SDCard;
     File               *CurrentFile;

     char hexaKeys[ROWS][COLS] = {
        {'1','2','3'},
     };
     byte rowPins[ROWS] = { 8 }; //connect to the row pinouts of the keypad
     byte colPins[COLS] = { 3, 4, 5 }; //connect to the column pinouts of the keypad

     //initialize an instance of class NewKeypad
     Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

     //Vars stuff
     const int defaultDelay = DEFAULT_DELAY;
     const int defaultVolume = DEFAULT_VOLUME;
     const int volumeDelta = VOLUME_INCREMENT;
     int time,systemVolume;
     bool paused,mute;
     char *readKey();
     char customKey, lastKey;
     bool newKey;

     //Internal Controls
     bool setupHardware();
     bool setupVars();
 public:
     bool sdSetup;

    //Starts necessary processes
	void begin();
    //Starts necessary processes and initializes all screen rotation to SetRotationAll
    void begin(int SetRotationAll);
    //Reads button input
    void buttonRead(char *input);
    //Toggles between play and pause
    void playPause();
    //Push volume. 0 = down; 1 = up
    void volumePush(bool dir);
    //Set system volume
    void setVolume(int inputVolume);

    void controllerDemo();
};