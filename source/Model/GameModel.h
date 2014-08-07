#include "StackRow.h"

class GameModel{
protected:
    StackRow stack;
    Row playerRow;
    int score;
    int timer;
public:
    GameModel();
    bool isConform();
    void effectAfterCorrectTurn();
    void effectAfterMistakeTurn();
    void effectIntTimer();
    void addScore(int i = 1);
    void effectClearButton();
    void motionLeft();
    void motionRight();
    const GameModel& getModel()       { return *this;};
    vector<int> getPlayerRow();
    vector<vector<int> > getStack();
    friend class PlayScene;
};