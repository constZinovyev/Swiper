#pragma once
#include "resources.h"
#include <iostream>
class BlockView{
    CSprite* block;
public:
    void setColor(int);
    void setCoord(float,float);
    CSprite* getSprite(){return block;}
    BlockView();
    ~BlockView() {}
    
};

class ScoreView{
    
    
};