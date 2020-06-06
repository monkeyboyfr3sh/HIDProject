//Want to flesh out SD reader class more with a setup function that can initialize
//a device controller

// SD_Reader.h
#include <SPI.h>
#include <SD.h>
#include "Debug.h"
//CS for SD Card
//#define _sdcs 2
#define _sdcs 21

//Number of attempts for SD Card
#define SDMountMax 10

class SD_Reader
{
 protected:
     char *cFile = ".c";
     char *txtFile = ".txt";
     bool sdSetup;
 public:
     bool setupFromSD();
     //Make sure SPI.begin is set before calling
     bool begin();
};

