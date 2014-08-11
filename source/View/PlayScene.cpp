#include "PlayScene.h"

void PlayScene::scoreToString(int scoreInt,int best){
    std::stringstream s1;
    s1 << scoreInt;
    score = s1.str();
    std::stringstream s2;
    s2 << best;
    bestScore = s2.str();
    
}
void PlayScene::RenderText(){
    if (!m_IsInputActive)
        return;
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
    IwGxFontDrawText(score.c_str(),score.size());
    
    if (modelForView.isGameOver()){
        IwGxFontSetCol(0xff000000);
        float width = backAfterDie->m_W*backAfterDie->m_ScaleX;
        float height = backAfterDie->m_H*backAfterDie->m_ScaleY;
        float x = backAfterDie->m_X - width * backAfterDie->m_AnchorX;
        float y = backAfterDie->m_Y - height * backAfterDie->m_AnchorY - height*0.1;
        
        IwGxFontSetRect(CIwRect(x,y,width,height));
        
        //Set the alignment within the formatting rect
        IwGxFontSetAlignmentVer(IW_GX_FONT_ALIGN_MIDDLE);
        IwGxFontSetAlignmentHor(IW_GX_FONT_ALIGN_CENTRE);
        
        // Draw title text
        IwGxFontSetFont(g_pResources->getFont());
        string inBack = "Your Score:\n" + score + "\nBest Score:\n"+bestScore;
        IwGxFontDrawText(inBack.c_str(),inBack.size());
    }
}
void PlayScene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
    Scene::Update(deltaTime, alphaMul);
    //UPDATE SCORE, PLR BLOCK, FIELD
    scoreToString(modelForView.score, modelForView.bestScore);
    field.updateField(modelForView.getStack());
    playerBlc.updateBlocks(modelForView.getPlayerRow());
    //IN GAME
    if (m_IsInputActive && !modelForView.isGameOver()){
        ++modelForView.timer;
        if(modelForView.timer%modelForView.getSpeed() == 0){
            std::cout << " EFFECT IN TIMER " << std::endl;
            modelForView.effectIntTimer();
        }
        //if (g_pInput->ignoreSwipe)
          //  std::cout<<"IGNORE"<<std::endl;
        if (g_pInput->isSwipeLeft()){
            std::cout << " SWIPE LEFT " << std::endl;
            modelForView.motionLeft();
            g_pInput->afterSwipeLeft();
        }
        else if (g_pInput->isSwipeRight()){
            std::cout << " SWIPE RIGHT " << std::endl;
            modelForView.motionRight();
            g_pInput->afterSwipeRight();
        }
        else if (g_pInput->isSwipeDown()){
            std::cout << " SWIPE DOWN " << std::endl;
            if (modelForView.isConform()){
                std::cout << " CORRECT TURN " << std::endl;
                modelForView.effectAfterCorrectTurn();
            }
            else{
                std::cout << " INCORRECT TURN " << std::endl;
                modelForView.effectAfterMistakeTurn();
            }
            g_pInput->afterSwipeDown();
        }
        g_pInput->Reset();
    }
    //MENU AFTER DIE
    else if (modelForView.isGameOver()){
        float newX = Iw2DGetSurfaceWidth()/2.0;
        float newY = Iw2DGetSurfaceHeight()/2.0;
        float out = -newY;
        backAfterDie->m_X = newX;
        backAfterDie->m_Y = newY;
        float xQuarBack = backAfterDie->m_W * backAfterDie->m_ScaleX/4.0;
        float yQuarBack = backAfterDie->m_H * backAfterDie->m_ScaleY/4.0;
        buttonRetry->setPosition(newX-xQuarBack, newY+yQuarBack);
        buttonInfo->setPosition(newX+xQuarBack, newY+yQuarBack);
        if (m_IsInputActive && m_Manager->GetCurrent() == this){
            if (g_pInput->isFinish()){
                g_pInput->Reset();
                if (buttonInfo->isPressed()){
                    //ACTION
                    std::cout<<"INFO GAME"<<std::endl;
                }
                if (buttonRetry->isPressed()){
                    //Action
                    std::cout<<"RETRY GAME"<<std::endl;
                    buttonRetry->setPosition(out,out);
                    buttonInfo->setPosition(out, out);
                    backAfterDie->m_X = out;
                    backAfterDie->m_Y = out;
                    modelForView.newGame();
                }
            }
            /*if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
            {
                g_pInput->Reset();
                int x = g_pInput->m_X;
                int y = g_pInput->m_Y;
                if (buttonRetry->isPressed(x,y))
                {
                    modelForView.newGame();
                    buttonRetry->setPosition(-1*newX, -1*newY);
                }
            }*/
        }
    }
}

void PlayScene::Render()
{
    Scene::Render();
}

PlayScene::PlayScene(){
    Scene::Init();
    //INIT BACKGROUND
    background = new CSprite();
    background->SetImage(g_pResources->getMenuBG());
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
    //INIT BACKGROUND AFTER DIE
    float x = -Iw2DGetSurfaceWidth()/2.0;
    float y = -Iw2DGetSurfaceHeight()/2.0;
    backAfterDie = new CSprite();
    backAfterDie->SetImage(g_pResources->getBackAfterDie());
    backAfterDie->m_X = x;
    backAfterDie->m_Y = y;
    backAfterDie->m_AnchorY = 0.5;
    backAfterDie->m_AnchorX = 0.5;
    if (Iw2DGetSurfaceHeight() == 568)
    {
        backAfterDie->m_ScaleX = 0.5f;
        backAfterDie->m_ScaleY = 0.5f;
    }
    AddChild(backAfterDie);
    //INIT BUTTON CONTINUE
    CIw2DImage* img = g_pResources->getRetry();
    buttonRetry = new Button(this,x,y,img,"");
    buttonRetry->setAnchor(0.5, 0.5);
    if (Iw2DGetSurfaceHeight() == 568)
    {
        buttonRetry->setScale(0.5, 0.5);
    }
    //INIT BUTTON INFO
    img = g_pResources->getInfo();
    buttonInfo = new Button(this,x,y,img,"");
    buttonInfo->setAnchor(0.5, 0.5);
    if (Iw2DGetSurfaceHeight() == 568)
    {
        buttonInfo->setScale(0.5, 0.5);
    }
    
    
    //FIRST RENDER
    field.updateField(modelForView.getStack());
    playerBlc.updateBlocks(modelForView.getPlayerRow());
    
    
}

PlayScene::~PlayScene(){
    delete buttonRetry;
    delete buttonInfo;
}