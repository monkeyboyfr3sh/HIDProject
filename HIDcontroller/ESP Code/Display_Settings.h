// Display_Settings.h
#include <SSD_13XX.h>
#include "Display_Resources.h"

//Number of Screens
#define NUM_SCREEN 3
//This will select the default screen responsible for system output/debugging
#define CONSOLE_SELECT 0

//SPI/TFT Pin Definitions
#define _cs     9   //self CS
#define _dc     7   // DC
#define _rst    6   // TFT RESET

class Display_Settings
{
protected:
    int screenCount = NUM_SCREEN;
    //CS Pin Definitions
    int CSArray[NUM_SCREEN] =
    {
        /*Screen 0 CS*/    18,
        /*Screen 1 CS*/    19,
        /*Screen 2 CS*/    20
    };
public:
    //This array 
    //This is a screen that will be default for debug/system output
    SSD_13XX *ConsoleScreen;
    SSD_13XX ScreenArray[NUM_SCREEN] =
    {
        SSD_13XX(CSArray[0],_dc),
        SSD_13XX(CSArray[1],_dc),
        SSD_13XX(CSArray[2],_dc)
    };
    void begin();
    
    //Goes through each screen object and displays its count
    void countScreen();

    //Clears chosen screen
    void clearScreen(int ScreenSelect);
    //Clears all screen
    void clearScreen();

    void setImageAll();//Not working properly
    
    //Prints text on specified screen
    void printText(int ScreenSelect, char *text);
    //Prints text on all screens
    void printText(char *text);

    //Currently flashes speaker Icon and delays by outputdelay
    void playIcon(int OutputDelay);
    //void playIcon(int ScreenSelect, int OutputDelay);

    //Sets TextScale for specific screen to Scale
    void setTextScale(int ScreenSelect,int Scale);
    //Sets TextScale for all screen to Scale
    void setTextScale(int Scale);

    //Sets rotation for specific screen to ScreenRotation
    void setRotation(int ScreenSelect,int ScreenRotation);
    //Sets rotation for all screen to ScreenRotation
    void setRotation(int ScreenRotation);
};