#include <SPI.h>
#include <SSD_13XX.h>

#include "_fonts/msShell14.c"
#include "_fonts/orbitron14.c"
#include "_fonts/mono_mid.c"

#include "_icons/spkOn.c"
#include "_icons/spkOff.c"

// For the ESP32
#define _cs1   23  // goes to TFT CS
#define _cs2   21  // goes to TFT CS
#define _cs3   22  // goes to TFT CS

#define _dc   33  // goes to TFT DC
#define _mosi 13  // goes to TFT MOSI
#define _sclk 14  // goes to TFT SCK/CLK
#define _rst  9   // ESP RST to TFT RESET
#define _miso 12   // Not connected

SSD_13XX tft1 = SSD_13XX(_cs1, _dc,_rst);
SSD_13XX tft2 = SSD_13XX(_cs2, _dc,_rst);
SSD_13XX tft3 = SSD_13XX(_cs3, _dc,_rst);

void setup(void) {
    Serial.begin(115200);
    SPI.begin(_sclk, _miso, _mosi,2);
    tft1.begin();
    tft2.begin();
    tft3.begin();

    tft1.setRotation(2);
    tft2.setRotation(2);
    tft3.setRotation(2);
}

void loop() {
    tft1.drawIcon(0, 0, &spkOn, 3, WHITE, BLACK, true);
    tft2.drawIcon(0, 0, &spkOn, 3, OLIVE, BLACK, true);
    tft3.drawIcon(0, 0, &spkOn, 3, BLUE, BLACK, true);
    delay(250);
    tft1.drawIcon(0, 0, &spkOff, 3, RED, BLACK, true);
    tft2.drawIcon(0, 0, &spkOff, 3, RED, BLACK, true);
    tft3.drawIcon(0, 0, &spkOff, 3, RED, BLACK, true);
    delay(250);
}