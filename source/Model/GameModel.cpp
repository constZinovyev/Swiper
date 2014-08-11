#include "GameModel.h"

GameModel::GameModel(){
    score = 0;
    bestScore = 0;
    timer = 1;
    speedBlocks = MAX_SPEED;
    stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
    gameOver = false;
}

void GameModel::newGame(){
    stack.destroyStack();
    playerRow.destroy();
    score = 0;
    speedBlocks = MAX_SPEED;
    timer = 1;
    stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
    gameOver = false;
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
        //stack.destroyStack();
        //playerRow.destroy();
        gameOver = true;
    }
    timer = 1;
}
void GameModel::effectAfterCorrectTurn(){
    addScore();
    //std::cout << stack.size()<<std::endl;
    stack.destroyRow();
    if(stack.size() == 0)
        stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
}
void GameModel::effectAfterMistakeTurn(){
    std::cout << "1" << std::endl;
    if (stack.size() < MAX_SIZE_LIST){
        std::cout << "2" << std::endl;
        //stack.addRowDown(stack.generateRow());
        stack.addRowUp(stack.generateRowByTwo(playerRow));
            std::cout << "3" << std::endl;
        playerRow = stack.generateTwoBlocks();
            std::cout << "4" << std::endl;
    }
    else{
        std::cout << "5" << std::endl;
        //playerRow.destroy();
        //stack.destroyStack();
        gameOver = true;
        std::cout << "6" << std::endl;
    }
        std::cout << "7" << std::endl;
}

void GameModel::addScore(int i){
    score += i;
    if (score % 10 == 0 && speedBlocks > MIN_SPEED)
            setSpeed(speedBlocks - MAX_SPEED/10);
    
}