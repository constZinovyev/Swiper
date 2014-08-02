#include "StackRow.h"

class GameModel{
    StackRow stack;
    Row playerRow;
    int score;
public:
    GameModel();
    bool isСonform();
    void effectAfterCorrectTurn();
    void effectAfterMistakeTurn();
    void addScore(int i = 1);
    void effectClearButton();
};