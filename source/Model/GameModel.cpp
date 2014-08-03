#include "GameModel.h"

GameModel::GameModel(){
    
    stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
}
vector<vector<int> > GameModel::getStack(){
    vector<vector<int> > temp;
    for(int i = 0;i < stack.size();++i)
        temp.push_back(stack.takeRow(i).getRowToInt());
    return temp;
}
vector<int> GameModel::getPlayerRow(){
    return playerRow.getRowToInt();
}
bool GameModel::isConform(){
    return stack.firstRow() == playerRow;
}

void GameModel::effectClearButton(){
    addScore(stack.size());
    stack.destroyStack();
    stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
    
}

void GameModel::effectAfterCorrectTurn(){
    addScore();
    stack.destroyRow();
    stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
}
void GameModel::effectAfterMistakeTurn(){
    if (stack.size() < MAX_SIZE_LIST-2){
        stack.addRowDown(stack.generateRow());
        stack.addRowUp(stack.generateRowByTwo(playerRow));
        playerRow = stack.generateTwoBlocks();
    }
}

void GameModel::addScore(int i){
    score += i;
}