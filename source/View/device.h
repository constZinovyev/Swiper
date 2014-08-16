#pragma once
const int SIMULATOR_HEIGHT = 568;
const int SIMULATOR_WIDTH = 320;
const int IPHONE5_HEIGHT = 1336;
const int IPHONE5_WIDTH = 640;
const int IPHONE4_HEIGHT = 960;
const int IPHONE4_WIDTH = 640;

#include "Iw2D.h"
struct Device{
    bool isIphone4;
    bool isIphone5;
    bool isSimulator;
    Device();
    void init();
};
extern Device currentDevice;