#include "Row.h"

Row::Row(){
    for (int i = 0; i < MAX_LEN_ROW; ++i){
        rowBlocks.push_back(Block());
    }
}

vector<int> Row::getRowToInt(){
    vector<int> temp;
    for(int i = 0; i < MAX_LEN_ROW;++i){
        temp.push_back(rowBlocks[i].getColor());
    }
    return temp;
}

void Row::swapBlocks(int fst, int snd){
    Block temp = rowBlocks[fst];
    rowBlocks[fst] = rowBlocks[snd];
    rowBlocks[snd] = temp;
    
}

bool Row::operator==(Row& snd){
    bool finishOp = true;
    bool isTrue;
    for (int i = 0; i < MAX_LEN_ROW; ++i){
        if (isTrue = (rowBlocks[i] == snd.rowBlocks[i]))
            finishOp = finishOp && true;
        else
        if ((rowBlocks[i].isEmpty()) || (snd.rowBlocks[i].isEmpty()))
            finishOp = finishOp && true;
        else
        if (rowBlocks[i] != snd.rowBlocks[i])
            finishOp = finishOp && false;
            
    }
    return finishOp;
};

void Row::changeCol(int i, Block blc){
    rowBlocks[i] = blc;
}

Block& Row::operator[](int i){
    if (i >=0 && i<MAX_LEN_ROW)
        return rowBlocks[i];
    else
        exit(0);
}