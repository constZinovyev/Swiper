#pragma once
#include "resources.h"
#include "scene.h"
#include "FieldView.h"
#include "../Model/GameModel.h"

class PlayScene: public Scene{
    GameModel& modelForView;
    CSprite* background;
    FieldView field;
    PlayerBlocks playerBlc;
    //ScoreView score;
public:
    PlayScene(GameModel &gameMdl);
    //PlayScene();
    ~PlayScene();
    void UpdateView();
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    void            Render();
};