#include "DeviceController.h"
DeviceController Controller;
void setup() {
    Controller.begin(2);
}

void loop() {
    Controller.controllerDemo();
}