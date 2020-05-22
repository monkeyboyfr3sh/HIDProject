// Display_Settings.h
#include <SPI.h>
#include <SSD_13XX.h>

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
    //CS Pin Definitions
    int CSArray[NUM_DISPLAY] =
    {
        /*Display 1 CS*/    23,
        /*Display 2 CS*/    21,
        /*Display 3 CS*/    22
    };

    int DisplayCount = NUM_DISPLAY;

public:
    void begin();
    void playIconAll();
};