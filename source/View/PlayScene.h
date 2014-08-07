#pragma once
#include "resources.h"
#include "scene.h"
#include "FieldView.h"
#include "../Model/GameModel.h"
#include "../Controller/input.h"
#include <string>
#include <sstream>
using std::string;
class PlayScene: public Scene{
    GameModel modelForView;
    CSprite* background;
    FieldView field;
    PlayerBlocks playerBlc;
    float x;
    float y;
    string score;
    //ScoreView score;
public:
    PlayScene();
    //PlayScene();
    ~PlayScene();
    void UpdateView();
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    void            Render();
    void scoreToString(int score);
    void            RenderText();
};