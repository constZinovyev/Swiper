#include "MainScene.h"

MainScene::MainScene(){
    Scene::Init();
    posBlockStart = Left;
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
    
    blockStart = new CSprite();
    blockStart->SetImage(g_pResources->getBlocks(3));
    blockStart->m_X = Iw2DGetSurfaceWidth()*5/20.0;
    blockStart->m_Y = Iw2DGetSurfaceHeight()/10.0;
    if (Iw2DGetSurfaceHeight() == 568)
    {
        blockStart->m_ScaleX = 0.5f;
        blockStart->m_ScaleY = 0.5f;
    }
    AddChild(blockStart);
    
    float x = Iw2DGetSurfaceWidth()*5/20.0;
    float y = Iw2DGetSurfaceHeight()*8.5/10.0;
    CIw2DImage* imgButStart = g_pResources->getBlocks(1);
    
    buttonStart = new Button(this,x,y,imgButStart,"");
    if (Iw2DGetSurfaceHeight() == 568)
    {
        buttonStart->setScale(0.5, 0.5);
    }
    x = Iw2DGetSurfaceWidth()*10/20.0;
    y = Iw2DGetSurfaceHeight()*8.5/10.0;
    imgButStart = g_pResources->getBlocks(3);
    
    buttonInfo = new Button(this,x,y,imgButStart,"");
    if (Iw2DGetSurfaceHeight() == 568)
    {
        buttonInfo->setScale(0.5, 0.5);
    }
    x = Iw2DGetSurfaceWidth()*15/20.0;
    y = Iw2DGetSurfaceHeight()*8.5/10.0;
    imgButStart = g_pResources->getBlocks(2);
    
    buttonApp = new Button(this,x,y,imgButStart,"");
    if (Iw2DGetSurfaceHeight() == 568)
    {
        buttonApp->setScale(0.5, 0.5);
    }
    
}

MainScene::~MainScene(){
    delete buttonStart;
    delete buttonApp;
    delete buttonInfo;
}
void MainScene::Render(){
    Scene::Render();
}
void MainScene::RenderText(){
    if (!m_IsInputActive)
        return;
    //buttonStart->renderText();
}

void MainScene::Update(float deltaTime,float alphaMul){
    if (!m_IsActive)
        return;
    Scene::Update(deltaTime, alphaMul);
    //POSITION LEFT / RIGHT
    if (posBlockStart == Left){
        blockStart->m_X = Iw2DGetSurfaceWidth()*5/20.0;
    }
    else if (posBlockStart == Right) {
        blockStart->m_X = Iw2DGetSurfaceWidth()*10/20.0;
    }
    
    if (m_IsInputActive && m_Manager->GetCurrent() == this){
        if (g_pInput->isSwipeLeft()){
            posBlockStart = Left;
            g_pInput->afterSwipeLeft();
        }else if (g_pInput->isSwipeRight()){
            posBlockStart = Right;
            g_pInput->afterSwipeRight();
        }else
        if (g_pInput->isSwipeDown() && posBlockStart == Right)
        {
            g_pInput->afterSwipeDown();
            PlayScene* game = (PlayScene*)g_pSceneManager->Find("play");
            g_pSceneManager->SwitchTo(game);
        }
        else{
            if(g_pInput->isStart()){
                if (buttonApp->isPressed() || buttonStart->isPressed() || buttonInfo->isPressed())
                    g_pInput->setIgnoreSwipe();
            }else
            if(g_pInput->isFinish()){
                g_pInput->Reset();
                if (buttonApp->isPressed()){
                    //ACTION
                    std::cout << "APP MENU" << std::endl;
    
                }else
                if (buttonInfo->isPressed()){
                    //ACTION
                    std::cout << "INFO MENU" << std::endl;
                
                }else
                if (buttonStart->isPressed()){
                        //ACTION
                    std::cout << "START MENU" << std::endl;
                            
                }
            }
                        
        }
    }
}

