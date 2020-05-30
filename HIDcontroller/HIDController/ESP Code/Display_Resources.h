// Display_Resources.h
#include <SSD_13XX.h>

#include "_icons/sdCard.c"
#include "_icons/spkOff.c"
#include "_icons/spkOn.c"

#define FONT_COUNT 2
#define ICON_COUNT 2
#define IMAGE_COUNT 2

//Create more images from image converter here
//About Project:    https://lcd-image-converter.riuson.com/en/about/
//Project Download: https://sourceforge.net/projects/lcd-image-converter/

class Display_Resource
{
public:
	
	tFont fontArray[FONT_COUNT] = {
		//msShell14::Font,
		//mono_mid::mono_mid
	};

	tIcon iconArray[ICON_COUNT] = {
		//spkOn,
		//spkOff
	};
};