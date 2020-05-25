#include "DeviceController.h"

DeviceController Controller;

void setup(void) {
    Serial.begin(115200);
    Controller.begin(2);
    Controller.setTextScale(2);
    Controller.controllerDemo();
}

void loop() {
}