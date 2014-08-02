#pragma once
#include "Block.h"
#include <vector>
#include <iostream>

using std::vector;
const short int MAX_LEN_ROW = 3;
//enum posBlock {FirstCol=0, SecondCol, ThirdCol};

class Row{
    vector<Block> rowBlocks;
public:
    Row();
    void swapBlocks(int,int);
    
    bool operator==(Row&);
    Block& operator[](int i);
    void changeCol(int,Block);
    ~Row(){rowBlocks.clear();}
    }
};
