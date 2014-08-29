#pragma once
#include "input.h"
#include "../View/MainScene.h"
#include "../View/PlayScene.h"

class Controller{
    GameModel& gameModel;
public:
    void controlPlayScene();
    void controlMenuScene();
    void Update();
    Controller(GameModel& model):gameModel(model){};
    
};

extern Controller* g_pController;