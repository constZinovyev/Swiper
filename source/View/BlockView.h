#pragma once
#include "resources.h"
#include "device.h"
#include <iostream>

#define coefForIPhone4 136/165.0f
class BlockView{
    CSprite* block;
public:
    void setColor(int curBlc,int nxtBlc = -1);
    void setCoord(float,float);
    BlockView* operator=(CSprite* arg);
    BlockView(const BlockView&);
    CSprite* getSprite(){return block;}
    bool isEmpty();
    BlockView();
    ~BlockView() {}
    void            setupViewSimulator();
    void            setupViewIphone5();
    void            setupViewIphone4();

    
};


extern Device currentDevice;