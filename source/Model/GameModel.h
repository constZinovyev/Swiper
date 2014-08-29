#pragma once
#include "StackRow.h"
#include "s3eSecureStorage.h"
#include "IwTween.h"
using namespace IwTween;

#define FRAME_RATE 30
#define MAX_SPEED 100
#define MIN_SPEED 24
#define STEP_SCORE_UP_SPEED 10
//STATE?


class  DataForView{
    bool blockSwap;
    bool oneLeft;
    bool oneRight;
    bool twoLeft;
    bool twoRight;
    bool gameOver;
    bool newPlrRow;
    bool newRowDown;
    bool newRowUp;
    bool fieldUp;
    bool newGame;
    int score;
    int highScore;
    vector<int> plrBlocks;
    vector<vector<int> > field;
    friend class GameModel;
    friend class PlayScene;
public:
    DataForView();
    void Reset();
};

class GameModel{

protected:
    StackRow stack;
    Row playerRow;
    int score;
    int highScore;
    int timer;
    int speedBlocks;
    DataForView data;
public:
    static bool stopTimer;
    GameModel();
    ~GameModel();
    void newGame();
    bool isConform();
    bool isGameOver()                 {return data.gameOver;}
    void effectAfterCorrectTurn();
    void effectAfterMistakeTurn();
    void effectIntTimer();
    void effectClearButton();
    void updateTimer();
    static void onTimer(CTween* pTween) {stopTimer = true;}
    static void offTimer(CTween* pTween){stopTimer = false;}
    
    void saveScoreToFile();
    void addScore(int i = 1);
    void loadHighScore();
    int  getScore()                    { return score;}
    int  getHighScore()                    { return highScore;}
    
    void motionLeft();
    void motionRight();

    int  getSpeed()                   { return speedBlocks;}
    void setSpeed(int x)             { speedBlocks = x;}
    void upSpeed();
    
    DataForView& getDataForView()             {return data;}
    void updateDataForView();
    
    const GameModel& getModel()       { return *this;}

    vector<int> getPlayerRow();
    vector<vector<int> > getStack();

};


