#include "Display_Settings.h"

Display_Settings Display;

void setup(void) {
    Serial.begin(115200);
    Display.begin();
    for (int i = 1; i <= NUM_DISPLAY; i++)
    {
        Serial.println();
    }
    /*
    tft1.setRotation(2);
    tft2.setRotation(2);
    tft3.setRotation(2);
    */
}

void loop() {
    /*
    tft1.drawIcon(0, 0, &spkOn, 3, WHITE, BLACK, true);
    tft2.drawIcon(0, 0, &spkOn, 3, OLIVE, BLACK, true);
    tft3.drawIcon(0, 0, &spkOn, 3, BLUE, BLACK, true);
    delay(250);
    tft1.drawIcon(0, 0, &spkOff, 3, RED, BLACK, true);
    tft2.drawIcon(0, 0, &spkOff, 3, RED, BLACK, true);
    tft3.drawIcon(0, 0, &spkOff, 3, RED, BLACK, true);
    delay(250);
    */
}