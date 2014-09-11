#include "FieldView.h"
//#include <iostream>
bool FieldView::clearUpRow;
bool FieldView::animProcessFallDown;
bool FieldView::animProcessNewDownRow;
void FieldView::print(){
    std::cout << "{{{{{{{{{{{{{{{" << std :: endl;
    for (int i = field.size()-1; i >= 0; --i){
        std :: cout << i << " " << field[i][0].getSprite()->m_Y << std::endl;
    }
    std::cout << "}}}}}}}}}}}}}}}" << std :: endl;
}
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
    /*for (int i = 0; i < MAX_LEN_ROW; ++i){
        newDownRow.push_back(BlockView());
        newDownRow[i].getSprite()->m_X = xOrigin + i * w * newDownRow[i].getSprite()->m_ScaleX + i * xBetweenBLock;
        newDownRow[i].getSprite()->m_Y = yOrigin;
        newDownRow[i].setColor(1,1);
    }*/
    //CAtlas*      img = g_pResources->getFromFirstToSecond(1,1);
    for (int i = 0; i < MAX_SIZE_LIST+1; ++i){
        field.push_back(vector<BlockView>());
        for(int j = 0; j < MAX_LEN_ROW; ++j)
        {
            field[i].push_back(BlockView());
            float x = xOrigin + j*w*field[i][j].getSprite()->m_ScaleX + j*xBetweenBLock;
            float y = yOrigin - (i)*h*field[i][j].getSprite()->m_ScaleY - (i)*yBetweenBLock;;
            //std::cout << x << " " <<y << std::endl;
            field[i][j].setCoord(x,y);
        }
    }
    clearField();
}

void FieldView::updateField(vector<vector<int> > temp){
    clearField();
    for(int i =0; i < temp.size(); ++i)
        for(int j =0; j < temp[i].size();++j){
            field[i][j].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond(temp[i][j],temp[i][j]));
        }
}

//WITHOUS FIRST ROW
void FieldView::clearField(){
    
    for(int i =1; i < field.size();++i)
        for(int j =0; j < field[i].size();++j)
            field[i][j].setColor(0,0);
    clearUpRow = false;
    animProcessFallDown = false;
    animProcessNewDownRow = false;
}

void FieldView::addToScene(Scene* scn){
    for(int i =0; i < field.size();++i)
        for(int j =0; j < field[i].size();++j)
            scn->AddChild(field[i][j].getSprite());
  /*  for(int i = 0; i < newDownRow.size();++i)
        scn->AddChild(newDownRow[i].getSprite());
*/
}

void FieldView::fieldOneRowUp(){
    for(int i = field.size()-1; i >0; --i)
        for (int j = 0; j < field[i].size(); ++j) {

            field[i][j].getSprite()->m_X = field[i-1][j].getSprite()->m_X;
            field[i][j].getSprite()->m_Y = field[i-1][j].getSprite()->m_Y;
            field[i][j].getSprite()->SetAtlas(field[i-1][j].getSprite()->GetAtlas());
        }
}
void FieldView::animFieldUp(){
    fieldOneRowUp();
    float sizeCell = g_pResources->getFromFirstToSecond(1,1)->GetFrameHeight()*field[0][0].getSprite()->m_ScaleY;
    for(int i = 1; i < field.size(); ++i)
        for (int j = 0; j < field[i].size(); ++j) {
            float nextPos = field[i][j].getSprite()->m_Y - yBetweenBLock - sizeCell;
            g_pTweener->Tween(0.2f,FLOAT,&field[i][j].getSprite()->m_Y,nextPos,END);
        }
}
void FieldView::animNewRowDown(vector<vector<int> > temp){
    //clearField();
    animFieldUp();
    int first = IwRand()%3;
    int second;
    int third;
    do{
        second = IwRand()%3;
    }while(first==second);
    
    do{
        third = IwRand()%3;
    }while(first==third || second ==third);
    
    float sizeCell = g_pResources->getFromFirstToSecond(1,1)->GetFrameHeight()*field[0][0].getSprite()->m_ScaleY;
    field[0][first].getSprite()->m_Y = IwGxGetScreenHeight()  + sizeCell;
    field[0][second].getSprite()->m_Y =IwGxGetScreenHeight()  + 2 * sizeCell;
    field[0][third].getSprite()->m_Y = IwGxGetScreenHeight()  + 3 * sizeCell;
        for(int i =0; i < temp[0].size();++i){
            field[0][i].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond(temp[0][i],temp[0][i]));
        }
    animProcessNewDownRow = true;
    g_pTweener->Tween(0.2f,FLOAT,&field[0][first].getSprite()->m_Y,(float)yOrigin,END);
    g_pTweener->Tween(0.3f,FLOAT,&field[0][second].getSprite()->m_Y,(float)yOrigin,END);
    g_pTweener->Tween(0.4f,FLOAT,&field[0][third].getSprite()->m_Y,(float)yOrigin,ONCOMPLETE,FieldView::afterAnimNewRowDown,END);
}

void FieldView::afterAnimNewRowDown(CTween* Tween){
    animProcessNewDownRow = false;
}
void FieldView::animCorrectTurn(vector<int> vecPLr,PlayerBlocks& plr){
    int firstNotEmptyRow = -1;
    float newPosY = 0;
    for (int i = field.size()-1; i >= 0; --i){
        if (field[i][0].getSprite()->GetAtlas() != g_pResources->getFromFirstToSecond(0,0))
        {
            firstNotEmptyRow = i;
            break;
        }
    }
    if (firstNotEmptyRow == -1){
        std::cout << "ERROR 100" << std::endl;
        return;
    }
    //std::cout<<firstNotEmptyRow<<std::endl;
    //PROBLEM
    float time = (field.size() - firstNotEmptyRow+1)*0.05f;
    firstNotEmptyRow++;
    for (int i = 0;i < MAX_LEN_ROW; ++i){
        
        field[firstNotEmptyRow][i].getSprite()->SetAtlas(plr.plrBlc[i].getSprite()->GetAtlas());
        newPosY = (float)field[firstNotEmptyRow-1][i].getSprite()->m_Y;
        field[firstNotEmptyRow][i].getSprite()->m_Y = (float)plr.plrBlc[i].getSprite()->m_Y;
        plr.plrBlc[i].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond());
        g_pTweener->Tween(time,FLOAT,&field[firstNotEmptyRow][i].getSprite()->m_Y,newPosY*1.0f,ONSTART,GameModel::disactivateTimer,ONCOMPLETE,onCompleteAfterCorrect,END);
    }
    animProcessFallDown = true;
}

void FieldView::delUpRow(){
        std::cout << "CORRECT" << std::endl;
    int firstNotEmptyRow = -1;
    float newPosY = 0;
    for (int i = field.size()-1; i >= 0; --i){
        if (field[i][0].getSprite()->GetAtlas() != g_pResources->getFromFirstToSecond(0,0) || field[i][2].getSprite()->GetAtlas() != g_pResources->getFromFirstToSecond(0,0))
        {
            firstNotEmptyRow = i;
            break;
        }
    }
    for (int j = field.size()-1; j >=firstNotEmptyRow-1;--j)
    for (int i = 0;i < MAX_LEN_ROW; ++i){
        field[j][i].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond());
    }
    float h = g_pResources->getFromFirstToSecond(1, 1)->GetFrameHeight();
    for (int i = 0;i < MAX_LEN_ROW; ++i){
        field[firstNotEmptyRow][i].getSprite()->m_Y = yOrigin - firstNotEmptyRow*h*field[firstNotEmptyRow][i].getSprite()->m_ScaleY - firstNotEmptyRow*yBetweenBLock;
    }
    
    
}

void FieldView::animInCorrectTurn(vector<int>vecPLr,PlayerBlocks& plr,vector<vector<int> >& fieldFromModel){
    std::cout << "INCORRECT" << std::endl;
    int firstEmptyRow = -1;
    float newPosY = 0;
    for (int i =  0; i < field.size(); ++i){
        if (field[i][0].getSprite()->GetAtlas() == g_pResources->getFromFirstToSecond(0,0) && field[i][2].getSprite()->GetAtlas() == g_pResources->getFromFirstToSecond(0,0))
        {
            firstEmptyRow = i;
            break;
        }
    }
    //std::cout << firstEmptyRow+1 << std ::endl;
    if (firstEmptyRow == -1){
        std::cout << "EXIT FROM ANIMINCORRECTTURN" << std::endl;
        return;
    }
    
    int emptyCell = -1;
    for (int i = 0; i < MAX_LEN_ROW; ++i){
        if (plr.plrBlc[i].getSprite()->GetAtlas() == g_pResources->getFromFirstToSecond(0,0)){
            emptyCell = i;
            break;
        }
    }
    float time = (field.size() - firstEmptyRow+1)*0.05f;
//    std::cout << "firstEmptyRow " << firstEmptyRow << std :: endl;
    for (int i = 0;i < MAX_LEN_ROW; ++i){
        field[firstEmptyRow][i].getSprite()->SetAtlas(plr.plrBlc[i].getSprite()->GetAtlas());
        newPosY = field[firstEmptyRow][i].getSprite()->m_Y;
        field[firstEmptyRow][i].getSprite()->m_Y = plr.plrBlc[i].getSprite()->m_Y;
        plr.plrBlc[i].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond());
        if (emptyCell != i)
            g_pTweener->Tween(time,FLOAT,&field[firstEmptyRow][i].getSprite()->m_Y,newPosY,ONSTART,GameModel::disactivateTimer,ONCOMPLETE,onCompleteAfterInCorrect,END);
        else {
            int clr = -1;
            if (firstEmptyRow> 4 || firstEmptyRow < 0)
                clr = 0;
            else  clr = fieldFromModel[firstEmptyRow][emptyCell];
            field[firstEmptyRow][emptyCell].getSprite()->SetAtlas(g_pResources->getFromFirstToSecond(clr,clr));
        }
        
    }
    //std::cout <<firstEmptyRow+1<<" " << newPosY << std :: endl;
    float scale = field[0][0].getSprite()->m_ScaleX;
    if (emptyCell == 0){
        
        field[firstEmptyRow][emptyCell].getSprite()->m_X =  -g_pResources->getFromFirstToSecond()->GetFrameWidth();
        field[firstEmptyRow][emptyCell].getSprite()->m_Y = newPosY;
        g_pTweener->Tween(time,FLOAT,&field[firstEmptyRow][emptyCell].getSprite()->m_X,(float)xOrigin,END);
        
    }else if (emptyCell == 1){
        
        field[firstEmptyRow][emptyCell].getSprite()->m_X = xOrigin + emptyCell*xBetweenBLock + g_pResources->getFromFirstToSecond()->GetFrameWidth()*scale;
        field[firstEmptyRow][emptyCell].getSprite()->m_Y = - 2*g_pResources->getFromFirstToSecond()->GetFrameHeight();
        g_pTweener->Tween(time,FLOAT,&field[firstEmptyRow][emptyCell].getSprite()->m_Y,newPosY,END);
        
    }else if (emptyCell == 2){
        
        field[firstEmptyRow][emptyCell].getSprite()->m_X = IwGxGetScreenWidth() + 2 * g_pResources->getFromFirstToSecond()->GetFrameWidth();
        field[firstEmptyRow][emptyCell].getSprite()->m_Y = newPosY;
        g_pTweener->Tween(time,FLOAT,&field[firstEmptyRow][emptyCell].getSprite()->m_X,
                          xOrigin + emptyCell * g_pResources->getFromFirstToSecond()->GetFrameWidth()*scale + emptyCell * xBetweenBLock,END);
        
    }
    
    
    animProcessFallDown = true;
}
void PlayerBlocks::updateNewBlocks(vector<int> clr){
    int emptyBlc = 0;
    
    for(int i = 0; i < MAX_LEN_ROW; ++i){
        float sizeCell =g_pResources->getFromFirstToSecond(1,1)->GetFrameHeight() *plrBlc[i].getSprite()->m_ScaleY;
        float y = - sizeCell - 10;
        float x = xOrigin + i*sizeCell + i*xBetweenBLock;
        plrBlc[i].setCoord(x, y);
    }
    
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
            int sndBlc = 0;
            for (int j = 0; j < MAX_LEN_ROW; ++j){
                if (j != i && j != emptyBlc)
                    sndBlc = j;
            }
            int sndClr = clr[sndBlc];
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
    //isChanged = false;
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
    for (int i = 0; i < MAX_LEN_ROW; ++i){
        plrBlc.push_back(BlockView());
    }
    for(int i = 0; i < MAX_LEN_ROW; ++i){
        plrBlc[i].setColor(1);
        if (Iw2DGetSurfaceHeight() == 568)
        {
            plrBlc[i].getSprite()->m_ScaleX = 0.5f;
            plrBlc[i].getSprite()->m_ScaleY = 0.5f;
        }
        float x = xOrigin + i*w*plrBlc[i].getSprite()->m_ScaleX + i*xBetweenBLock;
        float y = - h*plrBlc[i].getSprite()->m_ScaleY - 10;
        plrBlc[i].setCoord(x, y);
        
    }
}

void PlayerBlocks::animSwapBlocks(){
    for (int i = 0; i < MAX_LEN_ROW; ++i){
        plrBlc[i].getSprite()->SetAnimRepeat(1);
        plrBlc[i].getSprite()->SetAnimDuration(ANIM_SWAP_DUR);
    }
}

void PlayerBlocks::animMoveOneLeft(){
    float sizeSprite = g_pResources->getFromFirstToSecond()->GetFrameWidth()*plrBlc[0].getSprite()->m_ScaleX;
    g_pTweener->Tween(0.1f,FLOAT,&plrBlc[2].getSprite()->m_X,xOrigin+sizeSprite+xBetweenBLock,END);
    //ONSTART,g_pInput->onIgnoreInput,
    //ONCOMPLETE,g_pInput->offIgnoreInput,END);
     BlockView t = plrBlc[1];
    plrBlc[1] = plrBlc[2];
    plrBlc[2] = t;
    
}

void PlayerBlocks::animMoveOneRight(){
    float sizeSprite = g_pResources->getFromFirstToSecond()->GetFrameWidth()*plrBlc[0].getSprite()->m_ScaleX;
    g_pTweener->Tween(0.1f,FLOAT,&plrBlc[0].getSprite()->m_X,xOrigin+sizeSprite+xBetweenBLock,END);
    //ONSTART,g_pInput->onIgnoreInput,
    //ONCOMPLETE,g_pInput->offIgnoreInput,END);
    BlockView t = plrBlc[1];
    plrBlc[1] = plrBlc[0];
    plrBlc[0] = t;
    
}

void PlayerBlocks::animMoveTwoLeft(){
    float sizeSprite = g_pResources->getFromFirstToSecond()->GetFrameWidth()*plrBlc[0].getSprite()->m_ScaleX;
    g_pTweener->Tween(0.1f,FLOAT,&plrBlc[1].getSprite()->m_X,(float)xOrigin,END);
    //ONSTART,g_pInput->onIgnoreInput,
    //ONCOMPLETE,g_pInput->offIgnoreInput,END);
    g_pTweener->Tween(0.1f,FLOAT,&plrBlc[2].getSprite()->m_X,xOrigin+sizeSprite+xBetweenBLock,END);
    //ONSTART,g_pInput->onIgnoreInput,
    //ONCOMPLETE,g_pInput->offIgnoreInput,END);
    BlockView t = plrBlc[0];
    plrBlc[0] = plrBlc[1];
    plrBlc[1] = plrBlc[2];
    plrBlc[2] = t;
}

void PlayerBlocks::animMoveTwoRight(){
    float sizeSprite = g_pResources->getFromFirstToSecond()->GetFrameWidth()*plrBlc[0].getSprite()->m_ScaleX;
    g_pTweener->Tween(0.1f,FLOAT,&plrBlc[0].getSprite()->m_X,xOrigin+sizeSprite+xBetweenBLock,END);
    //ONSTART,g_pInput->onIgnoreInput,
    //ONCOMPLETE,g_pInput->offIgnoreInput,END);
    g_pTweener->Tween(0.1f,FLOAT,&plrBlc[1].getSprite()->m_X,xOrigin+2*sizeSprite+2*xBetweenBLock,END);
    //ONSTART,g_pInput->onIgnoreInput,
    //END);ONCOMPLETE,g_pInput->offIgnoreInput,END);
    BlockView t = plrBlc[2];
    plrBlc[2] = plrBlc[1];
    plrBlc[1] = plrBlc[0];
    plrBlc[0] = t;
    
}

void PlayerBlocks::animNewBlocks(){
    float sizeSprite = g_pResources->getFromFirstToSecond()->GetFrameHeight()*plrBlc[0].getSprite()->m_ScaleY;
    for (int i = 0; i < MAX_LEN_ROW; ++i){
        //plrBlc[i].getSprite()->m_Y = - sizeSprite - 10;
        g_pTweener->Tween(0.2f,FLOAT,&plrBlc[i].getSprite()->m_Y,(float)yOrigin,END);
        //plrBlc[i].getSprite()->m_Y = yOrigin;
        //ONSTART,g_pInput->onIgnoreInput,
        //ONCOMPLETE,g_pInput->offIgnoreInput,END);
    }
};
void PlayerBlocks::setupViewIphone4(){
    xOrigin = 214;
    yOrigin = 108;
    xBetweenBLock = 6;
    
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
    xOrigin = 214;
    yOrigin = 818;
    xBetweenBLock = 6;
    yBetweenBLock = 6;
    
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