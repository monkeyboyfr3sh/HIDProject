#include "DeviceController.h"

DeviceController Controller;
void setup(void) {
    Controller.begin(2);
}

void loop() {
    Controller.controllerDemo();
}