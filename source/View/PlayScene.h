#pragma once
#include "resources.h"
#include "scene.h"
#include "FieldView.h"
#include "../Model/GameModel.h"
#include "../Controller/input.h"
#include "Button.h"
#include <string>
#include <sstream>

using std::string;

class PlayScene: public Scene{
    GameModel modelForView;
    CSprite* background;
    CSprite* backAfterDie;
    Button* buttonInfo;
    Button* buttonRetry;
    FieldView field;
    PlayerBlocks playerBlc;
    string score;
    string bestScore;
    friend class MainScene;
public:
    PlayScene();
    ~PlayScene();
    void            UpdateView();
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    void            Render();
    void            scoreToString(int,int);
    void            RenderText();
    void            setupViewSimulator();
    void            setupViewIphone5();
    void            setupViewIphone4();
    void            setupTextSimulator();
    void            setupTextIphone5();
    void            setupTextIphone4();
};

extern Device currentDevice;