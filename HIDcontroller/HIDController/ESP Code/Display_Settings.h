// Display_Settings.h
#include <SPI.h>
#include <SSD_13XX.h>
#include "Debug.h"

#include "_fonts/msShell14.c"
#include "_fonts/orbitron14.c"
#include "_fonts/mono_mid.c"

#include "_icons/spkOn.c"
#include "_icons/spkOff.c"

//Number of Displays
#define NUM_DISPLAY 3

//SPI/TFT Pin Definitions
#define _cs     2   //self CS
#define _dc     33  // DC
#define _mosi   13  // MOSI
#define _miso   12  // MISO
#define _sclk   14  // SCK/CLK
#define _rst    9   // TFT RESET

class Display_Settings
{
protected:
    int DisplayCount = NUM_DISPLAY;

    //CS Pin Definitions
    int CSArray[NUM_DISPLAY] =
    {
        /*Display 0 CS*/    23,
        /*Display 1 CS*/    21,
        /*Display 2 CS*/    22
    };

    SSD_13XX DisplayArray[NUM_DISPLAY] =
    {
        SSD_13XX(CSArray[0],_dc,_rst),
        SSD_13XX(CSArray[1],_dc,_rst),
        SSD_13XX(CSArray[2],_dc,_rst)
    };
public:
    void begin();
    void countDisplay();
    void clearDisplay();

    void playIconAll(int outputdelay);

    void setTextScaleAll (int scale);

    void setRotation(int DisplaySelect,int DisplayRotation);
    void setRotationAll(int DisplayRotation);
};