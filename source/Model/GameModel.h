#pragma once
#include "StackRow.h"
#include "s3eSecureStorage.h"
#include "IwTween.h"
using namespace IwTween;

#define FRAME_RATE 60
#define MAX_SPEED 200
#define MIN_SPEED 48
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
    bool correctTurn;
    bool inCorrectTurn;
    
    int score;
    int highScore;
    vector<int> plrBlocks;
    vector<vector<int> > field;
    friend class GameModel;
    friend class PlayScene;
public:
    DataForView();
    void Reset();
    void print();
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
    static void disactivateTimer(CTween* Tween) {stopTimer = true;}//std::cout << stopTimer<<std::endl;}
    static void activateTimer(CTween*  Tween){stopTimer = false;}//std::cout << stopTimer<<std::endl;}
    
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


