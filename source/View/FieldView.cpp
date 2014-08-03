#include "FieldView.h"
FieldView::FieldView(){
    xOrigin = Iw2DGetSurfaceWidth()/4.0f;
    yOrigin = Iw2DGetSurfaceHeight()*8.6f/10.0f;
    xBetweenBLock = Iw2DGetSurfaceWidth()/20.0f;
    yBetweenBLock = Iw2DGetSurfaceWidth()/25.0f;
    CIw2DImage* img = g_pResources->getBlocks(0);
    
    for (int i = 0;i < MAX_SIZE_LIST;++i){
        field.push_back(vector<BlockView>());
        for(int j = 0; j < MAX_LEN_ROW;++j)
        {
            field[i].push_back(BlockView());
            float x = xOrigin + j*img->GetWidth()*field[i][j].getSprite()->m_ScaleX + j*xBetweenBLock;
            float y = yOrigin - i*img->GetHeight()*field[i][j].getSprite()->m_ScaleY - i*yBetweenBLock;;
            field[i][j].setCoord(x,y);
            field[i][j].setColor(0);
        }
        
        }
}
void FieldView::updateField(vector<vector<int> > temp){
    clearField();
    for(int i =0; i < temp.size();++i)
        for(int j =0; j < temp[i].size();++j)
            field[i][j].getSprite()->SetImage(g_pResources->getBlocks( temp[i][j]));
}
void FieldView::clearField(){
    for(int i =0; i < field.size();++i)
        for(int j =0; j < field[i].size();++j)
            field[i][j].getSprite()->SetImage(g_pResources->getBlocks(0));
}
void FieldView::addToScene(Scene* scn){
    for(int i =0; i < field.size();++i)
        for(int j =0; j < field[i].size();++j)
            scn->AddChild(field[i][j].getSprite());
}






void PlayerBlocks::updateBlocks(vector<int> clr){
    for(int i = 0; i < MAX_LEN_ROW; ++i){
        plrBlc[i].setColor(clr[i]);
    }
}
void PlayerBlocks::addToScene(Scene* scn){
    for (int i = 0; i < MAX_LEN_ROW; ++i)
        scn->AddChild(plrBlc[i].getSprite());
}
PlayerBlocks::PlayerBlocks(){
    xOrigin = Iw2DGetSurfaceWidth()/4.0f;
    yOrigin = Iw2DGetSurfaceHeight()*0.2f/10.0f;
    xBetweenBLock = Iw2DGetSurfaceWidth()/20.0f;
    CIw2DImage* img = g_pResources->getBlocks(0);
    
    for(int i = 0; i < MAX_LEN_ROW; ++i){
        plrBlc[i].setColor(1);
        if (Iw2DGetSurfaceHeight() == 568)
        {
            plrBlc[i].getSprite()->m_ScaleX = 0.5f;
            plrBlc[i].getSprite()->m_ScaleY = 0.5f;
        }
        float x = xOrigin + i*img->GetWidth()*plrBlc[i].getSprite()->m_ScaleX + i*xBetweenBLock;
        float y = yOrigin;
        plrBlc[i].setCoord(x, y);
        
    }
}