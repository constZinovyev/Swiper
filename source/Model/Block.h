//
//  Block.h
//  Swiper
//
//  Created by Сonstantin Zinovyev on 02.08.14.
//
//
const short int COUNT_COLORS = 3;
enum ColorBlock {Empty = 0, Light, Normal, Dark};

class Block{
    ColorBlock clr;
public:
    void       setColor(ColorBlock c) { clr = c;}
    ColorBlock getColor()             { return clr;}
    bool       isEmpty();
    bool       operator==(Block& snd);
    bool       operator!=(Block& snd);
    Block():clr(Empty){};
    Block(ColorBlock tmpClr):clr(tmpClr){};
};
