#include "MainScene.h"

MainScene::MainScene(){
    Scene::Init();
    posBlockStart = Left;
    background = new CSprite();
    background->m_X = 0;
    background->m_Y = 0;
    AddChild(background);
    
    /*test = new CSprite();
    test->m_X = Iw2DGetSurfaceWidth()/2;
    test->m_Y = Iw2DGetSurfaceHeight()/2;
    test->m_AnchorX = test->m_AnchorY = 0.5;
    test->SetAtlas(g_pResources->getFromFirstToSecond(1,2));
    test->SetAnimRepeat(3);
    test->SetAnimDuration(2);*/
    //AddChild(test);
    
    blockStart = new CSprite();
    blockStart->SetImage(g_pResources->getBlocks(3));
    AddChild(blockStart);
    
    buttonStart = new Button(this,0,0,NULL,"");
    buttonInfo = new Button(this,0,0,NULL,"");
    buttonApp = new Button(this,0,0,NULL,"");
    
    if (currentDevice.isSimulator){
        setupViewSimulator();
    }else
        if (currentDevice.isIphone5){
            setupViewIphone5();
        }else
            if(currentDevice.isIphone4){
                setupViewIphone4();
            }
    //blockStart->startAnimAtlas(g_pResources->getLM(), 0.5, 5);
    //blockStart->SetAtlas(g_pResources->getLM());
    //blockStart->SetAnimDuration(0.5);

    
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
        //!!!!!!!
        blockStart->m_X = LeftPos;
    }
    else if (posBlockStart == Right) {
        blockStart->m_X = RightPos;
    }
    
    if (m_IsInputActive && m_Manager->GetCurrent() == this){
        if (g_pInput->isSwipeLeft()){
            posBlockStart = Left;
//            blockStart->startAnimAtlas(g_pResources->getML(),g_pResources->getBlocks(1), 1, 1);
            g_pInput->afterSwipeLeft();
        }else if (g_pInput->isSwipeRight()){
            posBlockStart = Right;
//            blockStart->startAnimAtlas(g_pResources->getML(),g_pResources->getBlocks(1), 1, 1);
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

void MainScene::setupViewSimulator(){
    PlayScene* play =((PlayScene*)g_pSceneManager->Find("play"));
    CIw2DImage* img = g_pResources->getBlocks(1);
    float xOriginField = play->field.xOrigin;
    float x = xOriginField;
    float y = Iw2DGetSurfaceHeight()*8.5/10.0;
    
    background->SetImage(g_pResources->getMenuBG());
    background->m_ScaleX = 0.5f;
    background->m_ScaleY = 0.5f;
    
    blockStart->m_ScaleX = 0.5f;
    blockStart->m_ScaleY = 0.5f;
    blockStart->m_X = x;
    LeftPos = x;
    RightPos = x + img->GetWidth()*0.5 + play->field.xBetweenBLock;
    blockStart->m_Y = Iw2DGetSurfaceHeight()/10.0;
    
    buttonStart->setScale(0.5, 0.5);
    buttonStart->setImage(img);
    buttonStart->setPosition(x, y);
    
    img = g_pResources->getBlocks(3);
    x += play->field.xBetweenBLock + img->GetWidth()*0.5;
    y = Iw2DGetSurfaceHeight()*8.5/10.0;
    buttonInfo->setImage(img);
    buttonInfo->setPosition(x, y);
    buttonInfo->setScale(0.5, 0.5);
    
    img = g_pResources->getBlocks(2);
    x = x*2 - xOriginField;
    y = Iw2DGetSurfaceHeight()*8.5/10.0;
    buttonApp->setImage(img);
    buttonApp->setPosition(x, y);
    buttonApp->setScale(0.5, 0.5);
};

void MainScene::setupViewIphone5(){
    PlayScene* play =((PlayScene*)g_pSceneManager->Find("play"));
    CIw2DImage* img = g_pResources->getBlocks(1);
    float xOriginField = play->field.xOrigin;
    float x = xOriginField;
    float y = Iw2DGetSurfaceHeight()*8.5/10.0;
    
    background->SetImage(g_pResources->getMenuBG());
    
    LeftPos = x;
    RightPos = x + img->GetWidth() + play->field.xBetweenBLock;
    blockStart->m_X = xOriginField;
    blockStart->m_Y = Iw2DGetSurfaceHeight()/10.0;
    
    buttonStart->setImage(img);
    buttonStart->setPosition(x, y);
    
    img = g_pResources->getBlocks(3);
    x += play->field.xBetweenBLock + img->GetWidth();
    y = Iw2DGetSurfaceHeight()*8.5/10.0;
    buttonInfo->setImage(img);
    buttonInfo->setPosition(x, y);
    
    img = g_pResources->getBlocks(2);
    x = x*2 - xOriginField;
    y = Iw2DGetSurfaceHeight()*8.5/10.0;
    buttonApp->setImage(img);
    buttonApp->setPosition(x, y);
};

void MainScene::setupViewIphone4(){
    PlayScene* play =((PlayScene*)g_pSceneManager->Find("play"));
    CIw2DImage* img = g_pResources->getBlocks(1);
    float xOriginField = play->field.xOrigin;
    
    float x = play->field.xOrigin;
    float y = play->field.yOrigin;
    
    background->SetImage(g_pResources->getMenuBG());
    
    LeftPos = x;
    RightPos = x + img->GetWidth()*coefForIPhone4 + play->field.xBetweenBLock;
    blockStart->m_X = play->playerBlc.xOrigin;
    blockStart->m_Y = play->playerBlc.yOrigin;
    blockStart->m_ScaleX = coefForIPhone4;
    blockStart->m_ScaleY = coefForIPhone4;
    
    buttonStart->setImage(img);
    buttonStart->setPosition(x, y);
    buttonStart->setScale(coefForIPhone4,coefForIPhone4);
    
    img = g_pResources->getBlocks(3);
    x += play->field.xBetweenBLock + img->GetWidth()*coefForIPhone4;
    y = Iw2DGetSurfaceHeight()*8.5/10.0;
    buttonInfo->setImage(img);
    buttonInfo->setPosition(x, y);
    buttonInfo->setScale(coefForIPhone4,coefForIPhone4);
    
    img = g_pResources->getBlocks(2);
    x = x*2 - xOriginField;
    y = Iw2DGetSurfaceHeight()*8.5/10.0;
    buttonApp->setImage(img);
    buttonApp->setPosition(x, y);
    buttonApp->setScale(coefForIPhone4,coefForIPhone4);
};