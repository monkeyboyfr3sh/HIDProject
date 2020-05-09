#include <HID-Settings.h>
#include <HID-Project.h>
#include "arduino.h"
#include "consumerDefinitions.h"

#define MAXVOLUME 100
#define MINVOLUME 0
#define VOLUMEINCREMENT 2

#define INPUTDELAY 50
#define BUFFERSIZE 10

//define true if want to interact with base windows enviroment.
//define false if using with AutoHotKey, Voicemeeter, etc...
#define WINDOWSMODE false
#define DEBUG true

uint8_t defaultVolume;
uint8_t currentVolume;

void setup() {
    Serial.begin(115200);
    
    for (int i = 0; i < 100; i++) {
        Serial.println(".");
        delay(100);
    }
    
    
    if (DEBUG) {
        Serial.println("System will init in: ");
        
        delay(2000);
        
        for (int i = 0; i < 10; i++) {
            Serial.println(10 - i);
            delay(1000);
        }

        Serial.println("System init beginning");
    }

    initSys(90);
}
bool set = false;

void loop() {
    //listenToSerial();
    //launch_calc();
    while (!set) {
        Serial.println("Launching Calculator");
        delay(100);
        Consumer.write(HID_CONSUMER_AL_CALCULATOR);
        delay(1000);
        Keyboard.write('8');
        delay(300);
        Keyboard.write('0');
        delay(500);
        Keyboard.write('0');
        delay(200);
        Keyboard.write('8');
        delay(200);
        Keyboard.write('1');
        delay(500);
        Keyboard.write('3');
        delay(800);
        Keyboard.write('5');

        set = true;
    }
    Serial.println("done!");
    delay(20);
}

void launch_prog() {
    /*Need to work on input logic but maybe that should be in another part of the code.
    int input;

    Serial.println("Launch Calculator? [NO = 0 /YES = 1]");
    
    while (!Serial.available()) {
        input = listenToSerial();
        delay(10);
    }
    if (DEBUG) {
        Serial.print("Your input is: ");
        Serial.println(input);
    }
    if (input == 1) {
        Consumer.write(HID_CONSUMER_AL_CALCULATOR);
        
        if (DEBUG) {
            Serial.print("Calculator launched.");
            Serial.println(input);
        }
    }
    */
}

int listenToSerial()
{
    if (Serial.available()) {
        int value = 0;
        int serialCounter = 0;
        int input[BUFFERSIZE];

        while (Serial.available()) {
            char inputChar = Serial.read();
            input[serialCounter] = (int)inputChar - 48;

            //Removes nl/cr from serial message and corrects buffer pointer
            if ((input[serialCounter] == -35) || (input[serialCounter] == -38)) {
                input[serialCounter] = 0;
                serialCounter--;
            }
            serialCounter++;
        }

        //Bits will be stored in reverse order and need to have magnitude adjusted
        for (int i = 0; i < serialCounter; i++) {
            int addValue = (input[i] * pow(10, (serialCounter - 1 - i)));
            value = value + addValue;
        }
        delay(INPUTDELAY);

        return value;
        changeSysVolume(value);
    }
}

void changeSysVolume(int newVolume) {
    //Checks if input is valid
    if ((newVolume >= MINVOLUME) && (newVolume <= MAXVOLUME)) {

        while (newVolume > currentVolume) {
            //if (WINDOWSMODE) Consumer.write(MEDIA_VOLUME_UP);
            //Might want to shift to keyboard strikes later on
            Consumer.write(MEDIA_VOLUME_UP);
            currentVolume = currentVolume + VOLUMEINCREMENT;
            
            delay(INPUTDELAY);
        }
        while (newVolume < currentVolume) {
            Consumer.write(MEDIA_VOLUME_DOWN);
            currentVolume = currentVolume - VOLUMEINCREMENT;
            
            delay(INPUTDELAY);
        }
    }
    Keyboard.releaseAll();
}

int getDefaultVal()
{
    return defaultVolume;
}

int getCurrentVal()
{
    return currentVolume;
}

void initSys(int defaultVolume)
{
    Consumer.begin();
    Keyboard.begin();
    
    setDefaultVal(defaultVolume);
    currentVolume = 0;

    //Zero the volume for system to know location
    if (DEBUG) {
        Serial.println("Zeroing system volume.");
    }
    for (int i = 0; i <= MAXVOLUME; i++) {
        Consumer.write(MEDIA_VOLUME_DOWN);
        /*
        if (WINDOWSMODE) Consumer.write(MEDIA_VOLUME_DOWN);
        else {
            Keyboard.press(KEY_LEFT_CTRL);
            Keyboard.press('\350');
        }
        */
        delay(INPUTDELAY);
    }

    //Set system to defualt volume
    if (DEBUG) {
        Serial.println("Setting system volume to default.");
    }
    changeSysVolume(defaultVolume);
}

void setDefaultVal(int newDefault)
{
    defaultVolume = newDefault;
}
