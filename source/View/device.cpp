#include "device.h"
Device::Device(){
}
void Device::init(){
    isIphone4 = Iw2DGetSurfaceWidth() == IPHONE4_WIDTH && Iw2DGetSurfaceHeight() == IPHONE4_HEIGHT;
    isIphone5 = Iw2DGetSurfaceWidth() == IPHONE5_WIDTH && Iw2DGetSurfaceHeight() == IPHONE5_HEIGHT;
    isSimulator = Iw2DGetSurfaceWidth() == SIMULATOR_WIDTH && Iw2DGetSurfaceHeight() == SIMULATOR_HEIGHT;
}

Device currentDevice;