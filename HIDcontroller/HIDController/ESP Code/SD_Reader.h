// SD_Reader.h
#include <SPI.h>
#include <SD.h>
#include <time.h>
#include "Debug.h"

//CS for SD Card
#define _sdcs 2

//Number of attempts for SD Card
#define SDMountMax 10

class SD_Reader
{
 protected:
     uint8_t cardType;
     uint64_t cardSize;

 public:
     //Make sure SPI.begin is set before calling
     bool begin();
};

