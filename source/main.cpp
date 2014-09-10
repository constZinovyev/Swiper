/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
#include "s3e.h"
#include "Iw2D.h"
#include <time.h>
#include <iostream>
#include "Model/StackRow.h"
#include "Controller/input.h"
#include "View/PlayScene.h"
#include "View/MainScene.h"
#include "IwTween.h"
//Tweener
 using namespace IwTween;
 extern CTweenManager* g_pTweener;
 CTweenManager*  g_pTweener = 0;

class a{
public:
    static int b;
};
int a::b;

// FRAME_TIME is the amount of time that a single frame should last in seconds
#define FRAME_TIME  (15.0f / 1000.0f)
int main()
{
    //srand(time(NULL));
    // Initialise the 2D graphics syste
    Iw2DInit();
      // FONTS
    IwGxInit();
    IwGxSetColClear(0xff, 0xff, 0xff, 0xff);
    IwGxPrintSetColour(128, 128, 128);
    IwResManagerInit();
    IwGxFontInit();
    IwGetResManager()->LoadGroup("./fonts/IwGxFontTTF.group");
    GameModel* gameModel = new GameModel();
    GameModel::stopTimer = false;

    currentDevice.init();
    g_pSceneManager = new SceneManager();
    g_pTweener = new CTweenManager();
    g_pResources = new Resources();
    g_pInput = new Input();
    g_pController = new Controller(*gameModel);
    
    PlayScene* play = new PlayScene(gameModel->getDataForView());
    play->SetName("play");
    play->Init();
    g_pSceneManager->Add(play);
    
    MainScene* menu = new MainScene();
    menu->SetName("main");
    menu->Init();
    g_pSceneManager->Add(menu);
    g_pSceneManager->Remove(play);
    g_pSceneManager->Add(play);
    
    //g_pSceneManager->SwitchTo(play);
    
    

    g_pSceneManager->SwitchTo(play);
    Iw2DSurfaceClear(0xff0000ff);
  //  int i = 0;
    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        //if(g_pController->gameModel.stopTimer)
        //std::cout << g_pController->gameModel.stopTimer << std :: endl;
//        ++i;
//        std::cout << i << std :: endl;
        
        //render image

        uint64 new_time = s3eTimerGetMs();
        s3eKeyboardUpdate();
        s3ePointerUpdate();
        
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
        IwGxLightingOn();
        g_pController->Update();
        g_pSceneManager->Update(FRAME_TIME);
        g_pTweener->Update(FRAME_TIME);
        
        //Iw2DSurfaceClear(0xff0000ff);
        g_pSceneManager->Render();
        //analise move, update model & update dataforviev
        Iw2DFinishDrawing();
        
        //Render Text
        g_pSceneManager->RenderText();
        IwGxFlush();
        Iw2DSurfaceShow();
        // Lock frame rate
        int yield = (int)(FRAME_TIME * 1000 - (s3eTimerGetMs() - new_time));
        if (yield < 0)
            yield = 0;
        // Yield to OS
        s3eDeviceYield(yield);
    }
    delete gameModel;
    delete g_pResources;
    delete g_pInput;
    delete g_pTweener;
    delete g_pSceneManager;
    delete g_pController;
    IwGxFontTerminate();
    IwResManagerTerminate();
    IwGxTerminate();
    Iw2DTerminate();

    return 0;
}
