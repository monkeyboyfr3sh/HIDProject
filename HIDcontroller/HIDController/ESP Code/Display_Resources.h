// Display_Resources.h
#include <SSD_13XX.h>
namespace msShell14 {
#include "_fonts/msShell14.c"
}
namespace orbitron14 {
#include "_fonts/orbitron14.c"
}
namespace mono_mid {
#include "_fonts/mono_mid.c"
}
#include "_icons/spkOn.c"
#include "_icons/spkOff.c"

#include "_images/hands.c"
#include "_images/wifi2.c"
#include "_images/wifi2s.c"
#include "_images/wifi2sr.c"

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
		msShell14::Font,
		mono_mid::mono_mid
	};

	tIcon iconArray[ICON_COUNT] = {
		spkOn,
		spkOff
	};
};