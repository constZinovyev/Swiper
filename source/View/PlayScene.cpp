#include "PlayScene.h"

void PlayScene::UpdateView(){
    
}

void PlayScene::scoreToString(int scoreInt){
    std::stringstream ss;
    ss << scoreInt;
    score = ss.str();
    
}
void PlayScene::RenderText(){
    IwGxFontSetCol(0xff000000);
    float width = Iw2DGetSurfaceWidth()/10.0;
    float height = width;
    float x = Iw2DGetSurfaceWidth()/20.0;
    float y = Iw2DGetSurfaceHeight()*9/10.0;
    
    IwGxFontSetRect(CIwRect(x,y,width,height));
    
    //Set the alignment within the formatting rect
    IwGxFontSetAlignmentVer(IW_GX_FONT_ALIGN_MIDDLE);
    IwGxFontSetAlignmentHor(IW_GX_FONT_ALIGN_CENTRE);
    
    // Draw title text
    IwGxFontSetFont(g_pResources->getFont());
    IwGxFontDrawText(score.c_str(),1);
}
void PlayScene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
    Scene::Update(deltaTime, alphaMul);
    ++modelForView.timer;
    scoreToString(modelForView.score);
   // std::cout << score<<std::endl;
    field.updateField(modelForView.getStack());
    playerBlc.updateBlocks(modelForView.getPlayerRow());
    //field.updateField(modelForView.getStack());
    //playerBlc.updateBlocks(modelForView.getPlayerRow());
    
    /*bool swipeleft = false;
    bool swiperight = false;
    bool swipedown = false;*/
    
    if(modelForView.timer%60 == 0){
        modelForView.effectIntTimer();
    }
    if (m_IsInputActive){

    if (g_pInput->isSwipeLeft()){
        modelForView.motionLeft();
        
        g_pInput->swipeLeft = false;
    }
    else if (g_pInput->isSwipeRight()){
        modelForView.motionRight();
        
        g_pInput->swipeRight = false;
    }
    else if (g_pInput->isSwipeDown()){
        
        if (modelForView.isConform())
            modelForView.effectAfterCorrectTurn();
        else
            modelForView.effectAfterMistakeTurn();
        g_pInput->swipeDown = false;
        }
        g_pInput->Reset();
    }
    
   /* if (m_IsInputActive){
        
    if(g_pInput->isStart())
    {
        std::cout << "START"<<g_pInput->m_X<<std::endl;
        //background->SetImage(g_pResources->getBlocks(1));
        //g_pInput->StartMotion = false;
        //g_pInput->Reset();
        //modelForView.motionLeft();
        //modelForView.effectAfterCorrectTurn();
        //modelForView.effectAfterMistakeTurn();
        //field.updateField(modelForView.getStack());
        //playerBlc.updateBlocks(modelForView.getPlayerRow());
        
    }
    else if (g_pInput->isFinish()){
            //background->SetImage(g_pResources->getBlocks(3));
            std::cout << "FINISH"<<g_pInput->m_X<<std::endl;
            g_pInput->Reset();
    }
    else if (g_pInput->isMotion())
    {
                        //background->SetImage(g_pResources->getBlocks(2));
            //std::cout << "MOTION"<<std::endl;
        
    }
    else{
        //background->SetImage(g_pResources->getBlocks(0));
    }
    }*/
}

void PlayScene::Render()
{
    Scene::Render();
}

PlayScene::PlayScene(){
    Scene::Init();
    background = new CSprite();
    background->SetImage(g_pResources->getMenuBG());
//        background->SetImage(g_pResources->getBlocks(0));
    background->m_X = 0;
    background->m_Y = 0;
    if (Iw2DGetSurfaceHeight() == 568)
    {
        background->m_ScaleX = 0.5f;
        background->m_ScaleY = 0.5f;
    }
    AddChild(background);
    playerBlc.addToScene(this);
    field.addToScene(this);
    field.updateField(modelForView.getStack());
    playerBlc.updateBlocks(modelForView.getPlayerRow());
}

PlayScene::~PlayScene(){
    
    
}