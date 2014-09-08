#include "Block.h"

bool Block::operator==(const Block& snd){
    return clr == snd.clr;
}

bool Block::operator!=(const Block& snd){
    return clr != snd.clr;
}

bool Block::isEmpty() const{
    return clr == Empty;
}