// DeviceController.h
#include "Display_Settings.h"
#include "HID-Project.h"
#include "Debug.h"

#define DEFAULT_DELAY 500

class DeviceController
{
 protected:
     Display_Settings   Display;
     int defaultDelay = DEFAULT_DELAY;
     int time;
     bool paused;
     
     /*
     Display.clearDisplay();
     Display.countDisplay();

     Display.setImageAll();
     */

 public:
    //Starts necessary processes
	void begin();
    //Starts necessary processes and initializes all screen rotation to SetRotationAll
    void begin(int SetRotationAll);

    void setRotation(int Screen, int Rotation);

    //Sets Text scale for specified screen
    void setTextScale(int ScreenSlect, int Scale);
    //Sets Text scale for all screen
    void setTextScale(int Scale);

    void playPause();
    void playPause(int Delay);

    void controllerDemo();
};