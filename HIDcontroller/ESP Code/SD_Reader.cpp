#include "SD_Reader.h"

bool checkCard() {
    SD.exists("/setup.txt");
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
    return checkCard;
}

char *SD_Reader::returnLine(File *readFile)
{
    while(readFile->available()){
        Serial.println(readFile->read());
    }
    return nullptr;
}

void SD_Reader::loadIcons(File *iconsDir) {
    while (true) {
        File entry = iconsDir->openNextFile();
        if (!entry) {
            // no more files
            break;
        }
        char *name = entry.name();
        Serial.print("Char 2,1,0: ");
        Serial.print(name[2]);
        Serial.print(name[1]);
        Serial.println(name[0]);
        //bool dir = entry.isDirectory();
        entry.close();
    }
}
