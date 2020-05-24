#include "Debug.h"
#include "Display_Settings.h"

#define LEDPin 2
Display_Settings Display;

void setup(void) {
    Serial.begin(115200);
    Display.begin();
    Display.setRotationAll(2);
    Display.setTextScaleAll(2);
}

void loop() {
    delay(100);
    /*
    Display.clearDisplay();
    Display.countDisplay();
    */
    Display.setImageAll();
}