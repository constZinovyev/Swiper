#pragma once
#include "input.h"
#include "../View/MainScene.h"
#include "../View/PlayScene.h"

class Controller{
    
public:
    GameModel& gameModel;
    void controlPlayScene();
    void controlMenuScene();
    void Update();
    Controller(GameModel& model):gameModel(model){};
    static void stopGameTimer(){GameModel::disactivateTimer();}
    static void activateGameTimer(){GameModel::activateTimer();}
    
};

extern Controller* g_pController;