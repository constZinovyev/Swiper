#include "FieldView.h"
//#include <iostream>
FieldView::FieldView(){
    if (currentDevice.isIphone5){
        setupViewIphone5();
    }else if(currentDevice.isIphone4){
        setupViewIphone4();
    }else if (currentDevice.isSimulator){
        setupViewSimulator();
    }
    float w = g_pResources->getFromFirstToSecond(1, 1)->GetFrameWidth();
    float h = g_pResources->getFromFirstToSecond(1, 1)->GetFrameHeight();
    //CAtlas*      img = g_pResources->getFromFirstToSecond(1,1);
    for (int i = 0;i < MAX_SIZE_LIST;++i){
        field.push_back(vector<BlockView>());
        for(int j = 0; j < MAX_LEN_ROW;++j)
        {
            field[i].push_back(BlockView());
            float x = xOrigin + j*w*field[i][j].getSprite()->m_ScaleX + j*xBetweenBLock;
            float y = yOrigin - i*h*field[i][j].getSprite()->m_ScaleY - i*yBetweenBLock;;
            //std::cout << x << " " <<y << std::endl;
            field[i][j].setCoord(x,y);
            field[i][j].setColor(0,0);
        }
        
        }
}
void FieldView::updateField(vector<vector<int> > temp){
    clearField();
    for(int i =0; i < temp.size();++i)
        for(int j =0; j < temp[i].size();++j){
            field[i][j].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond(temp[i][j],temp[i][j]));
        }
}
void FieldView::clearField(){
    for(int i =0; i < field.size();++i)
        for(int j =0; j < field[i].size();++j)
            field[i][j].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond());
}
void FieldView::addToScene(Scene* scn){
    for(int i =0; i < field.size();++i)
        for(int j =0; j < field[i].size();++j)
            scn->AddChild(field[i][j].getSprite());
}

void PlayerBlocks::updateBlocks(vector<int> clr){
    //bool clrBlc[MAX_LEN_ROW+1] = {false,false,false,false};
    int emptyBlc = 0;
    if (isChanged){
        startAnim();
        std::cout<<isChanged<<std::endl;
        resetChanged();
        return;
    }
    if(plrBlc[0].getSprite()->AnimProcess || plrBlc[1].getSprite()->AnimProcess)
        return;
    for(int i = 0; i < MAX_LEN_ROW; ++i){
        if (clr[i] == 0){
            emptyBlc = i;
            break;
        }
    }
    for(int i = 0; i < MAX_LEN_ROW; ++i){
        if (clr[i] == 0)
            plrBlc[i].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond());
        else {
            std::set<int> a;
            a.insert(0);
            a.insert(1);
            a.insert(2);
            a.erase(i);
            a.erase(emptyBlc);
            int sndClr = clr[*a.begin()];
            plrBlc[i].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond(clr[i],sndClr),
                                            g_pResources->getFromFirstToSecond(sndClr,clr[i]));
            
        }
    }
}
void PlayerBlocks::addToScene(Scene* scn){
    for (int i = 0; i < MAX_LEN_ROW; ++i)
        scn->AddChild(plrBlc[i].getSprite());
}
PlayerBlocks::PlayerBlocks(){
    isChanged = false;
    if (currentDevice.isIphone5){
        setupViewIphone5();
    }else if(currentDevice.isIphone4){
        setupViewIphone4();
    }else if (currentDevice.isSimulator){
        setupViewSimulator();
    }
    float w = g_pResources->getFromFirstToSecond(1, 1)->GetFrameWidth();
    float h = g_pResources->getFromFirstToSecond(1, 1)->GetFrameHeight();
    //std::cout << w << " " << h << std::endl;
    
    for(int i = 0; i < MAX_LEN_ROW; ++i){
        plrBlc[i].setColor(1);
        if (Iw2DGetSurfaceHeight() == 568)
        {
            plrBlc[i].getSprite()->m_ScaleX = 0.5f;
            plrBlc[i].getSprite()->m_ScaleY = 0.5f;
        }
        float x = xOrigin + i*w*plrBlc[i].getSprite()->m_ScaleX + i*xBetweenBLock;
        float y = yOrigin;
        plrBlc[i].setCoord(x, y);
        
    }
}

void PlayerBlocks::startAnim(){
    for (int i = 0; i < MAX_LEN_ROW; ++i){
        plrBlc[i].getSprite()->SetAnimRepeat(1);
        plrBlc[i].getSprite()->SetAnimDuration(0.5);
    }
}

void PlayerBlocks::setupViewIphone4(){
    xOrigin = Iw2DGetSurfaceWidth()/4.0f;
    yOrigin = Iw2DGetSurfaceHeight()*0.2f/10.0f;
    xBetweenBLock = Iw2DGetSurfaceWidth()/20.0f;
    
}

void PlayerBlocks::setupViewIphone5(){
    xOrigin = Iw2DGetSurfaceWidth()/6.0f;
    yOrigin = Iw2DGetSurfaceHeight()*0.2f/10.0f;
    xBetweenBLock = Iw2DGetSurfaceWidth()/45.0f;
    
}

void PlayerBlocks::setupViewSimulator(){
    xOrigin = Iw2DGetSurfaceWidth()/6.0f;
    yOrigin = Iw2DGetSurfaceHeight()*0.2f/10.0f;
    xBetweenBLock = Iw2DGetSurfaceWidth()/45.0f;
    
}

void FieldView::setupViewIphone4(){
    xOrigin = Iw2DGetSurfaceWidth()/4.0f;
    yOrigin = Iw2DGetSurfaceHeight()*8.6f/10.0f;
    xBetweenBLock = Iw2DGetSurfaceWidth()/20.0f;
    yBetweenBLock = Iw2DGetSurfaceWidth()/25.0f;
    
}

void FieldView::setupViewIphone5(){
    xOrigin = Iw2DGetSurfaceWidth()/6.0f;
    yOrigin = Iw2DGetSurfaceHeight()*8.5f/10.0f;
    xBetweenBLock = Iw2DGetSurfaceWidth()/45.0f;
    yBetweenBLock = Iw2DGetSurfaceWidth()/45.0f;
    
}

void FieldView::setupViewSimulator(){
    xOrigin = Iw2DGetSurfaceWidth()/6.0f;
    yOrigin = Iw2DGetSurfaceHeight()*8.5f/10.0f;
    xBetweenBLock = Iw2DGetSurfaceWidth()/45.0f;
    yBetweenBLock = Iw2DGetSurfaceWidth()/45.0f;
    
}