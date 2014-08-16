#pragma once
#include "scene.h"
#include "resources.h"
#include "Button.h"
#include "PlayScene.h"
class MainScene:public Scene{
    enum PositionBlock {Anim = 0, Left, Right};
    CSprite* background;
    CSprite* blockStart;
    PositionBlock posBlockStart;
    Button*  buttonStart;
    Button*  buttonInfo;
    Button*  buttonApp;
    CSprite* test;
    bool startTouchButton;
    float LeftPos;
    float RightPos;
public:
    MainScene();
    ~MainScene();
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    void            Render();
    void            RenderText();
    void            setupViewSimulator();
    void            setupViewIphone5();
    void            setupViewIphone4();
};

extern Device currentDevice;