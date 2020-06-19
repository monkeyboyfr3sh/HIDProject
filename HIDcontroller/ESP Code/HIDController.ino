#include "DeviceController.h"
DeviceController Controller;
void setup() {
    Controller.begin();
}

void loop() {
    Controller.controllerDemo();
}

/*
#include <Keypad.h>

const byte ROWS = 2; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'}
};
byte rowPins[ROWS] = { 8 , 7 }; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 5, 4 }; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
    Serial.begin(9600);
}

void loop() {
    char customKey = customKeypad.getKey();

    if (customKey) {
        Serial.println(customKey);
    }
}
*/