// DeviceController.h
#include <Keypad.h>
#include "Program.h"
#include "Display_Settings.h"
#include "SD_Reader.h"

#define ROWS 2
#define COLS 3

class DeviceController
{
protected:
     Display_Settings   Display;
     SD_Reader          SDCard;
     File               *CurrentFile;
     Variable_Struct    DeviceVars;
     //Media              MediaProg;
     Volume             VolumeProg;

     char hexaKeys[ROWS][COLS] = {
        {'1','2','3'},
        {'4','5','6'}
     };

     byte rowPins[ROWS] = { 8, 7 }; //connect to the row pinouts of the keypad
     byte colPins[COLS] = { 6, 5, 4 }; //connect to the column pinouts of the keypad

     //initialize an instance of class NewKeypad
     Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
     //Reads button input
     bool readKey();
     //Sets up internal controls and variables. Careful with order
     bool setup();
 
public:
     bool sdSetup;

    //Starts necessary processes
	void begin();
    //Starts necessary processes and initializes all screen rotation to SetRotationAll
    void begin(int SetRotationAll);
    //Reads button input
    void buttonRead();

    void controllerDemo();
};