#include "SD_Reader.h"

bool SD_Reader::begin()
{
    int SDMountTry = 0;
    while (!SD.begin(_sdcs))
    {
        if (DEBUG) {
            Serial.print("SD Mount Attempt: ");
            Serial.println(SDMountTry + 1);
        }
        if (SDMountTry > SDMountMax) {
            if (DEBUG) {
                Serial.println("Card Mount Failed");
            }
            return false;
        }
        SDMountTry++;
    }
    
    return true;
}

