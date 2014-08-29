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
//ПРОБЛЕМА - БЫСТРЫЙ СВАЙП - ВРЕМЯ ЗАНОВО - СДЕЛАТЬ ЗАВИСИМОСТЬ ВРЕМЕНИ ОТ СВАЙПА
void MainScene::actionSwipeLeft(){
    if (posBlockStart != Left){
        posBlockStart = Left;
        g_pTweener->Tween(0.2,FLOAT,&blockStart->m_X,LeftPos,END);//ONSTART,g_pInput->onIgnoreInput,ONCOMPLETE,g_pInput->offIgnoreInput,END);
    }
}
void MainScene::actionSwipeDown(){
    g_pTweener->Tween(0.5,FLOAT,&blockStart->m_Y,820.0f,ONCOMPLETE,afterSwipeDown,END);//ONSTART,g_pInput->onIgnoreInput,ONCOMPLETE,afterSwipeDown,END);
    
}
void MainScene::afterSwipeDown(CTween* Tween){
    //g_pInput->offIgnoreInput;
    PlayScene* game = (PlayScene*)g_pSceneManager->Find("play");
    g_pSceneManager->SwitchTo(game);
    //g_pInput->Restart();
}

void MainScene::actionSwipeRight(){
    if (posBlockStart != Right){
        posBlockStart = Right;
        g_pTweener->Tween(0.2,FLOAT,&blockStart->m_X,RightPos,END);//ONSTART,g_pInput->onIgnoreInput,ONCOMPLETE,g_pInput->offIgnoreInput,END);
    }
}

void MainScene::updateBlockStart(){
    if (posBlockStart == Left){
        blockStart->m_X = LeftPos;
    }
    else if (posBlockStart == Right) {
        blockStart->m_X = RightPos;
    }
}

void MainScene::Update(float deltaTime,float alphaMul){
    if (!m_IsActive)
        return;
    Scene::Update(deltaTime, alphaMul);
    //updateBlockStart();
    if (m_IsInputActive && m_Manager->GetCurrent() == this){
        //g_pController -> Update();
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