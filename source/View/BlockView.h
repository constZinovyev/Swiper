#pragma once
#include "resources.h"
#include "device.h"
#include <iostream>
class BlockView{
    CSprite* block;
public:
    void setColor(int curBlc,int nxtBlc = -1);
    void setCoord(float,float);
    CSprite* getSprite(){return block;}
    BlockView();
    ~BlockView() {}
    void            setupViewSimulator();
    void            setupViewIphone5();
    void            setupViewIphone4();

    
};

class ScoreView{
    
    
};

extern Device currentDevice;