#include "PlayScene.h"

void PlayScene::scoreToString(){
    int scoreInt = dataFromModel.score;
    int best = dataFromModel.highScore;
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
    if (currentDevice.isSimulator){
        setupTextSimulator();
    }else
        if (currentDevice.isIphone5){
            setupTextIphone5();
        }else
            if(currentDevice.isIphone4){
                setupTextIphone4();
            }
    IwGxFontSetCol(0xff000000);
    //Set the alignment within the formatting rect
    IwGxFontSetAlignmentVer(IW_GX_FONT_ALIGN_MIDDLE);
    IwGxFontSetAlignmentHor(IW_GX_FONT_ALIGN_CENTRE);
    
    // Draw title text
    IwGxFontSetFont(g_pResources->getFont());
    IwGxFontDrawText(score.c_str(),score.size());
    
    if (dataFromModel.gameOver){
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


void PlayScene::updateFromModel(){
    scoreToString();
}


void PlayScene::Update(float deltaTime, float alphaMul){
    if (!m_IsActive)
        return;
    //UPDATE SCORE, PLR BLOCK, FIELD
    //updateFromModel();
    //std::cout << dataFromModel.newPlrRow << " " << dataFromModel.correctTurn << " " << std::endl;
    //std::cout << FieldView::animProcessNewDownRow << std::endl;
    //dataFromModel.print();
    
    if(field.clearUpRow){
        field.clearUpRow = false;
        field.delUpRow();
    }
    
    
    if (!dataFromModel.newRowDown && !FieldView::animProcessNewDownRow)
    {
        if (dataFromModel.correctTurn){
            dataFromModel.correctTurn = false;
            field.animCorrectTurn(dataFromModel.plrBlocks, playerBlc);
        }
        if (dataFromModel.inCorrectTurn ){
            dataFromModel.inCorrectTurn = false;
            field.print();
            dataFromModel.print();
            field.animInCorrectTurn(dataFromModel.plrBlocks,playerBlc,dataFromModel.field);
            field.print();
            dataFromModel.print();
        }
        if (dataFromModel.newPlrRow ){
            //std::cout<<"NEW BLOCKS"<<std::endl;
            dataFromModel.newPlrRow = false;
            playerBlc.updateNewBlocks(dataFromModel.plrBlocks);
            playerBlc.animNewBlocks();
        }
    }
    //if (FieldView::downRowBusy)
    //    std :: cout << "1" << std::endl;
    
    if(dataFromModel.newRowDown && !FieldView::animProcessFallDown){
        dataFromModel.newRowDown = false;
        field.animNewRowDown(dataFromModel.field);
        //Scene::Update(deltaTime, alphaMul);
    }
    if(dataFromModel.blockSwap){
        dataFromModel.blockSwap = false;
        //std::cout<<"SWAP"<<std::endl;
        playerBlc.animSwapBlocks();

    }
    if(dataFromModel.twoLeft){
        dataFromModel.twoLeft = false;
        ///std::cout<<"2 LEFT"<<std::endl;
        playerBlc.animMoveTwoLeft();

    }
    if(dataFromModel.twoRight){
        dataFromModel.twoRight = false;
        //std::cout<<"2 RIGHT"<<std::endl;
        playerBlc.animMoveTwoRight();

    }
    if(dataFromModel.oneLeft){
        dataFromModel.oneLeft = false;
        //std::cout<<"1 LEFT"<<std::endl;
        playerBlc.animMoveOneLeft();

    }
    if(dataFromModel.oneRight){
        dataFromModel.oneRight = false;
        //std::cout<<"1 RIGHT"<<std::endl;
        playerBlc.animMoveOneRight();
    }
    if(dataFromModel.newGame){
        dataFromModel.newGame = false;
        field.clearField();
    }
    //IN GAME
    if (m_IsInputActive && m_Manager->GetCurrent() == this){
        
    }
    updateFromModel();
    Scene::Update(deltaTime, alphaMul);
}

void PlayScene::Render(){
    Scene::Render();
    if (this->m_IsVisible)
    {
        Scene* scn = g_pSceneManager->Find("main");
        scn -> m_IsVisible = false;
    }
}

void PlayScene::showAfterDieMenu(){
    float newX = Iw2DGetSurfaceWidth()/2.0;
    float newY = Iw2DGetSurfaceHeight()/2.0;
    float out = -newY;
    backAfterDie->m_X = newX;
    backAfterDie->m_Y = newY;
    float xQuarBack = backAfterDie->m_W * backAfterDie->m_ScaleX/4.0;
    float yQuarBack = backAfterDie->m_H * backAfterDie->m_ScaleY/4.0;
    buttonRetry->setPosition(newX-xQuarBack, newY+yQuarBack);
    buttonInfo->setPosition(newX+xQuarBack, newY+yQuarBack);
}

void PlayScene::hideAfterDieMenu(){
    int out = - Iw2DGetSurfaceHeight();
    buttonRetry->setPosition(out, out);
    buttonInfo->setPosition(out, out);
    backAfterDie->m_X = out;
    backAfterDie->m_Y = out;
}
PlayScene::PlayScene(DataForView& data):dataFromModel(data){
    Scene::Init();
    //INIT BACKGROUND
    background = new CSprite();
    background->m_X = 0;
    background->m_Y = 0;
    AddChild(background);
    
    playerBlc.addToScene(this);
    field.addToScene(this);
    
    //INIT BACKGROUND AFTER DIE
    float x = -Iw2DGetSurfaceWidth();
    float y = -Iw2DGetSurfaceHeight();
    backAfterDie = new CSprite();
    backAfterDie->m_X = x;
    backAfterDie->m_Y = y;
    backAfterDie->m_AnchorY = 0.5;
    backAfterDie->m_AnchorX = 0.5;
    AddChild(backAfterDie);
    
    //INIT BUTTON CONTINUE
    buttonRetry = new Button(this,x,y,NULL,"");
    buttonRetry->setAnchor(0.5, 0.5);
    
    //INIT BUTTON INFO
    buttonInfo = new Button(this,x,y,NULL,"");
    buttonInfo->setAnchor(0.5, 0.5);
    
    if (currentDevice.isSimulator){
        setupViewSimulator();
    }else
        if (currentDevice.isIphone5){
            setupViewIphone5();
        }else
            if(currentDevice.isIphone4){
                setupViewIphone4();
            }
    
    //FIRST RENDER
    //field.updateField(modelForView->getStack());
    //playerBlc.updateBlocks(modelForView->getPlayerRow());
}

PlayScene::~PlayScene(){
    delete buttonRetry;
    delete buttonInfo;
}

void PlayScene::setupViewSimulator(){
    background->SetImage(g_pResources->getMenuBG());
    background->m_ScaleX = 0.5f;
    background->m_ScaleY = 0.5f;
    
    backAfterDie->SetImage(g_pResources->getBackAfterDie());
    backAfterDie->m_ScaleX = 0.5f;
    backAfterDie->m_ScaleY = 0.5f;
    
    buttonRetry->setScale(0.5, 0.5);
    buttonRetry->setImage(g_pResources->getRetry());
    
    buttonInfo->setScale(0.5, 0.5);
    buttonInfo->setImage(g_pResources->getInfo());
    
}

void PlayScene::setupViewIphone5(){
    background->SetImage(g_pResources->getMenuBG());
    
    backAfterDie->SetImage(g_pResources->getBackAfterDie());
    
    buttonRetry->setImage(g_pResources->getRetry());
    
    buttonInfo->setImage(g_pResources->getInfo());
}

void PlayScene::setupViewIphone4(){
    background->SetImage(g_pResources->getBGiPhone4());
    
    backAfterDie->SetImage(g_pResources->getBackAfterDie());
    backAfterDie->m_ScaleX = 0.6;
    backAfterDie->m_ScaleY = 0.6;
    
    buttonInfo->setImage(g_pResources->getInfo());
    buttonInfo->setScale(0.6,0.6);
    
    buttonRetry->setImage(g_pResources->getRetry());
    buttonRetry->setScale(0.6,0.6);
}

void PlayScene::setupTextSimulator(){
    float width = Iw2DGetSurfaceWidth()/10.0;
    float height = width;
    float x = Iw2DGetSurfaceWidth()/20.0;
    float y = Iw2DGetSurfaceHeight()*9/10.0;
    IwGxFontSetRect(CIwRect(x,y,width,height));
}

void PlayScene::setupTextIphone4(){
    float width = Iw2DGetSurfaceWidth()/10.0;
    float height = width;
    float x = Iw2DGetSurfaceWidth()/20.0;
    float y = Iw2DGetSurfaceHeight()*9/10.0;
    IwGxFontSetRect(CIwRect(x,y,width,height));}

void PlayScene::setupTextIphone5(){
    float width = Iw2DGetSurfaceWidth()/10.0;
    float height = width;
    float x = Iw2DGetSurfaceWidth()/20.0;
    float y = Iw2DGetSurfaceHeight()*9/10.0;
    IwGxFontSetRect(CIwRect(x,y,width,height));
}