#pragma once
#include "input.h"
#include "scene.h"
#include "IwTween.h"
#include "../View/MainScene.h"
#include "../View/PlayScene.h"
class Controller;
extern Controller* g_pController;

class Controller{

public:
    Controller(){g_pController->ignoreAction = false;}
    static bool ignoreAction;
    void controlPlayScene();
    void controlMenuScene();
    static void     onIgnoreAction(CTween* pTween)  {g_pController->ignoreAction = true;}
    static void     offIgnoreAction(CTween* pTween) {g_pController->ignoreAction = false;}
    void Update();
    
};