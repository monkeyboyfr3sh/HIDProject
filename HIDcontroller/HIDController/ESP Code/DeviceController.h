// DeviceController.h
#include <Keypad.h>
#include "Display_Settings.h"
#include "SD_Reader.h"
#include "HID-Project.h"
#include "Debug.h"

#define DEFAULT_DELAY 500
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
     int defaultDelay = DEFAULT_DELAY;
     int time;
     bool paused;

     char *readKey();
     char customKey, lastKey;
     bool newKey;
     void playPause(char *input);
 public:
     bool sdSetup;

    //Starts necessary processes
	void begin();
    //Starts necessary processes and initializes all screen rotation to SetRotationAll
    void begin(int SetRotationAll);

    void controllerDemo();
};