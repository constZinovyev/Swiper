#include "StackRow.h"

class GameModel{
protected:
    StackRow stack;
    Row playerRow;
    int score;
public:
    GameModel();
    bool isConform();
    void effectAfterCorrectTurn();
    void effectAfterMistakeTurn();
    void addScore(int i = 1);
    void effectClearButton();
    const GameModel& getModel()       { return *this;};
    vector<int> getPlayerRow();
    vector<vector<int> > getStack();
    friend class PlayScene;
};