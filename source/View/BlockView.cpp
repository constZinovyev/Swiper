#include "BlockView.h"


void BlockView::setCoord(float xPos,float yPos){
    block->m_X = xPos;
    block->m_Y = yPos;
}

void BlockView::setColor(int clrBlock){
    std::cout<<clrBlock<<std::endl;
    block -> SetImage(g_pResources->getBlocks(clrBlock));
    block -> m_W = block -> GetImage() -> GetWidth();
    block -> m_H = block -> GetImage() -> GetHeight();
}
BlockView::BlockView(){
    block = new CSprite();
    if (Iw2DGetSurfaceHeight() == 568)
    {
        block->m_ScaleX = 0.5f;
        block->m_ScaleY = 0.5f;
    }
    setColor(0);
}