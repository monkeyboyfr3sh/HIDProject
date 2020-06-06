#include "SD_Reader.h"
bool SD_Reader::setupFromSD() {
    File setupFile = SD.open("setup.txt", FILE_READ);
    while (setupFile.available()) {
        Serial.write(setupFile.read());
    }


}

bool SD_Reader::begin()
{
    volatile int SDMountTry = 0;
    while (!SD.begin(_sdcs))
    {
        if (DEBUG) {
            Serial.print("SD Mount Attempt: ");
            Serial.println(SDMountTry + 1);
        }
        if (SDMountTry >= SDMountMax-1) {
            if (DEBUG) {
                Serial.println("Card Mount Failed");
            }
            return false;
        }
        SDMountTry++;
    }
    if (DEBUG) {
        Serial.println("SD Card Mounted");
    }
    setupFromSD();
    return true;
}