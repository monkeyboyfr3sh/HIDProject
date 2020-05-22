#include "Display_Settings.h"

void Display_Settings::begin()
{
	tft = SSD_13XX(CSArray[1], _dc, _rst);

	SPI.begin(_sclk, _miso, _mosi, _cs);
	tft.begin();
}

void Display_Settings::playIconAll()
{
}

