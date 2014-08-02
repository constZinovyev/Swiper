#include "Block.h"

bool Block::operator==(Block& snd){
    return clr == snd.clr;
}

bool Block::operator!=(Block& snd){
    return clr != snd.clr;
}

bool Block::isEmpty(){
    return clr == Empty;
}