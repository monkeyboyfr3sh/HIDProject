#include "DeviceController.h"
DeviceController Controller;
void setup() {
    Controller.begin();
}

void loop() {
    Controller.controllerDemo();
}