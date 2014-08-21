#pragma once
#include "input.h"
#include "scene.h"
#include "../View/MainScene.h"
#include "../View/PlayScene.h"

class Controller{
public:
    void controlPlayScene();
    void controlMenuScene();
    void Update();
    
};

extern Controller* g_pController;