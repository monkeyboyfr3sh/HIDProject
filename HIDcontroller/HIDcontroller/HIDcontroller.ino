#include <HID.h>
#include <HID-Settings.h>
#include <HID-Project.h>
#include "arduino.h"

#define MAXVOLUME 100
#define MINVOLUME 0
#define VOLUMEINCREMENT 2

#define INPUTDELAY 10
#define BUFFERSIZE 10

#define DEBUG true

int sensorPin = 14;
int sensorValue = 0;

uint8_t defaultVolume;
uint8_t currentVolume;

void setup() {
    Serial.begin(115200);
    
    
    if (DEBUG) {
        Serial.println("System will init in: ");
        
        delay(2000);
        
        for (int i = 0; i < 10; i++) {
            Serial.println(10 - i);
            delay(200);
        }
    }

    initSys(100);
}

void loop() {
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    delay(100);
}

void launch_prog(ConsumerKeycode inputProgram) 
{
    Consumer.write(inputProgram);
}
/*
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
*/

void changeSysVolume(int newVolume)
{
    //Checks if input is valid
    if ((newVolume >= MINVOLUME) && (newVolume <= MAXVOLUME)) {

        while (newVolume > currentVolume) {
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
        delay(INPUTDELAY);
    }

    //Set system to defualt volume
    if (DEBUG) {
        Serial.println("Setting system volume to default.");
    }
    changeSysVolume(defaultVolume);
}

void setDefaultVal(int defaultInput)
{
    defaultVolume = defaultInput;
    if (DEBUG) Serial.println("Changing default value");
}
