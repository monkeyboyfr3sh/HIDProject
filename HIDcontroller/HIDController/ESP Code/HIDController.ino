#include "Debug.h"
#include "Display_Settings.h"

Display_Settings Display;

void setup(void) {
    Serial.begin(115200);
    Display.begin();
    Display.setRotationAll(2);
    Display.setTextScaleAll(2);
    Display.clearDisplay();
    Display.countDisplay();
}

void loop() {
}