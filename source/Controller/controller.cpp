#include "Controller.h"
Controller* g_pController;
void Controller::Update(){
    //std::cout << g_pInput->ignoreInput << std::endl;
    MainScene* menu = (MainScene*)g_pSceneManager->Find("main");
    PlayScene* play = (PlayScene*)g_pSceneManager->Find("play");
    Scene* currentScene = g_pSceneManager->GetCurrent();
    if (currentScene == menu){
        controlMenuScene();
    }else
    if (currentScene == play){
        controlPlayScene();
    }
}

void Controller::controlMenuScene(){
    MainScene* menu = (MainScene*)g_pSceneManager->Find("main");
    if (g_pInput->isSwipeLeft()){
        menu->actionSwipeLeft();
        g_pInput->afterSwipeLeft();
    }else if (g_pInput->isSwipeRight()){
        menu->actionSwipeRight();
        g_pInput->afterSwipeRight();
    }else
        if (g_pInput->isSwipeDown() && menu->posBlockStart == menu->Right)
        {
            g_pInput->afterSwipeDown();
            menu->actionSwipeDown();

        }
        else{
            if(g_pInput->isStart()){
                if (menu->buttonApp->isPressed() || menu->buttonStart->isPressed() || menu->buttonInfo->isPressed())
                    g_pInput->setIgnoreSwipe();
            }else
                if(g_pInput->isFinish()){
                    g_pInput->Reset();
                    if (menu->buttonApp->isPressed()){
                        //ACTION
                        std::cout << "APP MENU" << std::endl;
                        
                    }else
                        if (menu->buttonInfo->isPressed()){
                            //ACTION
                            std::cout << "INFO MENU" << std::endl;
                            
                        }else
                            if (menu->buttonStart->isPressed()){
                                //ACTION
                                std::cout << "START MENU" << std::endl;
                                
                            }
                }
            
        }
    
}

void Controller::controlPlayScene(){
    PlayScene* play = (PlayScene*)g_pSceneManager->Find("play");
    
    if (!gameModel.isGameOver()){
        gameModel.updateTimer();
        if (g_pInput->isSwipeLeft()){
            gameModel.motionLeft();
            g_pInput->afterSwipeLeft();
        }
        else if (g_pInput->isSwipeRight()){
            gameModel.motionRight();
            g_pInput->afterSwipeRight();
        }
        else if (g_pInput->isSwipeDown()){
            if (gameModel.isConform()){
                gameModel.effectAfterCorrectTurn();
                //gameModel.onTimer();
            }
            else{
                gameModel.effectAfterMistakeTurn();
            }
            g_pInput->afterSwipeDown();
        }
        g_pInput->Reset();
    }else
        //MENU AFTER DIE
        if (gameModel.isGameOver()){
            play->showAfterDieMenu();
                if (g_pInput->isFinish()){
                    g_pInput->Reset();
                    if (play->buttonInfo->isPressed()){
                        //ACTION
                    }
                    if (play->buttonRetry->isPressed()){
                        play->hideAfterDieMenu();
                        gameModel.newGame();
                }
            }
        }
    
    gameModel.updateDataForView();
}