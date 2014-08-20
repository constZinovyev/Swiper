#pragma once
#include "StackRow.h"
#include "s3eSecureStorage.h"
#include "IwTween.h"
using namespace IwTween;

#define FRAME_RATE 30
#define MAX_SPEED 60
#define MIN_SPEED 24
#define STEP_SCORE_UP_SPEED 10

class GameModel{
protected:
    StackRow stack;
    Row playerRow;
    bool blockChanged;
    int score;
    int highScore;
    int timer;
    bool gameOver;
    int speedBlocks;
public:
    static bool stopTimer;
    GameModel();
    ~GameModel();
    void newGame();
    bool isConform();
    bool isGameOver()                 { return gameOver;}
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
    
    
    void resetBlockChanged()          {blockChanged = false;}
    bool getBlockChanged()            {return blockChanged;}
    
    const GameModel& getModel()       { return *this;}

    vector<int> getPlayerRow();
    vector<vector<int> > getStack();

};


