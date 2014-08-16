#include "StackRow.h"
#include "s3eSecureStorage.h"

#define FRAME_RATE 30
#define MAX_SPEED 48
#define MIN_SPEED 24
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
    GameModel();
    ~GameModel();
    bool isConform();
    void effectAfterCorrectTurn();
    void effectAfterMistakeTurn();
    void effectIntTimer();
    void addScore(int i = 1);
    void effectClearButton();
    void motionLeft();
    void motionRight();
    void resetBlockChanged()          {blockChanged = false;}
    bool getBlockChanged()            {return blockChanged;}
    int  getSpeed()                   { return speedBlocks;}
    void  setSpeed(int x)             { speedBlocks = x;}
    void newGame();
    const GameModel& getModel()       { return *this;}
    bool isGameOver()                 { return gameOver;}
    vector<int> getPlayerRow();
    vector<vector<int> > getStack();
    friend class PlayScene;
    void saveScoreToFile();
};