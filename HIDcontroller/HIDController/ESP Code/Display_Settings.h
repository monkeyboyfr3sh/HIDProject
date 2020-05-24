// Display_Settings.h
#include <SSD_13XX.h>
#include "SD_Reader.h"
#include "Display_Resources.h"
#include "Debug.h"

//Number of Displays
#define NUM_DISPLAY 3

//SPI/TFT Pin Definitions
#define _cs     3   //self CS
#define _dc     7   // DC
#define _rst    6   // TFT RESET

class Display_Settings
{
protected:
    int DisplayCount = NUM_DISPLAY;
    SD_Reader SDCard;
    //CS Pin Definitions
    int CSArray[NUM_DISPLAY] =
    {
        /*Display 0 CS*/    18,
        /*Display 1 CS*/    19,
        /*Display 2 CS*/    20
    };

    SSD_13XX DisplayArray[NUM_DISPLAY] =
    {
        SSD_13XX(CSArray[0],_dc),
        SSD_13XX(CSArray[1],_dc),
        SSD_13XX(CSArray[2],_dc)
    };
public:
    bool sdSetup;
    void begin();
    void countDisplay();
    void clearDisplay();
    void setImageAll();

    void setTextScaleAll(int scale);

    void playIconAll(int outputdelay);
    void setRotation(int DisplaySelect,int DisplayRotation);
    void setRotationAll(int DisplayRotation);
};