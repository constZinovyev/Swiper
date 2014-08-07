#include "GameModel.h"

GameModel::GameModel(){
    score = 0;
    timer = 0;
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
void GameModel::motionLeft(){
    if (playerRow[0].isEmpty()){
        playerRow.swapBlocks(0, 1);
        playerRow.swapBlocks(1, 2);
    }
    else if (playerRow[1].isEmpty()){
        playerRow.swapBlocks(1, 2);
        }
    else
        playerRow.swapBlocks(0, 1);
}

void GameModel::motionRight(){
    if (playerRow[2].isEmpty()){
        playerRow.swapBlocks(1, 2);
        playerRow.swapBlocks(0, 1);
    }
    else if (playerRow[1].isEmpty()){
        playerRow.swapBlocks(0, 1);
    }
    else
        playerRow.swapBlocks(1, 2);
}

void GameModel::effectClearButton(){
    addScore(stack.size());
    stack.destroyStack();
    stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
    
}

void GameModel::effectIntTimer(){
    if (stack.size() < MAX_SIZE_LIST){
        stack.addRowDown(stack.generateRow());
    }else{
        stack.destroyStack();
        score = 0;
    }
}
void GameModel::effectAfterCorrectTurn(){
    addScore();
    //std::cout << stack.size()<<std::endl;
    stack.destroyRow();
    if(stack.size() == 0)
        stack.addRowDown(stack.generateRow());
    //stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
}
void GameModel::effectAfterMistakeTurn(){
    if (stack.size() < MAX_SIZE_LIST){
        //stack.addRowDown(stack.generateRow());
        stack.addRowUp(stack.generateRowByTwo(playerRow));
        playerRow = stack.generateTwoBlocks();
    }
    else{
        stack.destroyStack();
        score = 0;
    }
}

void GameModel::addScore(int i){
    score += i;
}