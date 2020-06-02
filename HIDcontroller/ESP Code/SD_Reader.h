// SD_Reader.h
#include <SPI.h>
#include <SD.h>
#include "Debug.h"

//CS for SD Card
//#define _sdcs 2
#define _sdcs 21
#define BUFFER_SIZE 45

//Number of attempts for SD Card
#define SDMountMax 10

class SD_Reader
{
 protected:
     char lineBuffer[BUFFER_SIZE];
     char *cFile = ".c";
     char *txtFile = ".txt";
 public:
     //Make sure SPI.begin is set before calling
     bool begin();
     //Returns line of given file or until buffer fills
     char *returnLine(File *readFile);

     void loadIcons(File *iconsDir);
};

