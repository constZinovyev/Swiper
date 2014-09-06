#include "BlockView.h"

void BlockView::setCoord(float xPos,float yPos){
    block->m_X = xPos;
    block->m_Y = yPos;
}

void BlockView::setColor(int clrBlock,int nextClrBlock){
    //std::cout<<clrBlock<<std::endl;
    if (nextClrBlock == -1)
        nextClrBlock = clrBlock;
    block -> SetAtlas(g_pResources->getFromFirstToSecond(clrBlock,nextClrBlock));
}

BlockView* BlockView::operator=(CSprite* snd){
   // std::cout<<"OPER="<<std::endl;
    return this;
}
bool BlockView::isEmpty(){
    return g_pResources->getFromFirstToSecond() == block->GetAtlas();
}
BlockView::BlockView(const BlockView& copy){
    block = copy.block;
    //std::cout<< "COPY"<<std::endl;
}

BlockView::BlockView(){
    block = new CSprite();
    if (currentDevice.isIphone5){
        setupViewIphone5();
    }else
        if (currentDevice.isSimulator){
            setupViewSimulator();
        }else if(currentDevice.isIphone4){
            setupViewIphone4();
        }
    setColor(0,0);
    block -> m_W = g_pResources->getFromFirstToSecond(1,1)->GetFrameWidth();
    block -> m_H = 0;
//    block -> m_H = g_pResources->getFromFirstToSecond(1,1)->GetFrameHeight();
}

void BlockView::setupViewSimulator(){
    block->m_ScaleX = 0.5f;
    block->m_ScaleY = 0.5f;
};
void BlockView::setupViewIphone5(){
    
};
void BlockView::setupViewIphone4(){
    block->m_ScaleX = coefForIPhone4;
    block->m_ScaleY = coefForIPhone4;
    
};
