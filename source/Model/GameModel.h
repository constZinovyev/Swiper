#include "StackRow.h"
#include "s3eSecureStorage.h"

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
    int  getScore()                    { return score;}
    int  getHighScore()                    { return highScore;}
    void setSpeed(int x)             { speedBlocks = x;}
    void newGame();
    void loadHighScore();
    const GameModel& getModel()       { return *this;}
    bool isGameOver()                 { return gameOver;}
    vector<int> getPlayerRow();
    vector<vector<int> > getStack();
    void updateTimer();
    void saveScoreToFile();
    void upSpeed();
};