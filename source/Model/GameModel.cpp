#include "GameModel.h"

bool GameModel::stopTimer;

DataForView::DataForView(){
    blockSwap = false;
    oneLeft = false;
    oneRight = false;
    twoLeft = false;
    twoRight = false;
    gameOver = false;
    newPlrRow = false;
    newRowDown = false;
    fieldUp = false;
    correctTurn = false;
    inCorrectTurn = false;
    score = 0;
    highScore = 0;
    plrBlocks.clear();
    field.clear();
}

void DataForView::Reset(){
    *this = DataForView();
}

void GameModel::updateDataForView(){
    data.score = score;
    data.highScore = highScore;
    data.plrBlocks = getPlayerRow();
    data.field = getStack();
};

void GameModel::loadHighScore(){
    highScore = 0;
    s3eSecureStorageGet(&highScore,sizeof(highScore));
    s3eSecureStorageError errorSecureStorage = s3eSecureStorageError();
    if (errorSecureStorage == S3E_SECURESTORAGE_ERR_NONE)
    {
        //std::cout << "NO PROBLEM" << std::endl;
        //std::cout << highScore << std::endl;
    }else {
        highScore = 0;
        std::cout << "ERROR OPEN FILE TO HIGHSCORE" << std::endl;
        s3eSecureStoragePut(&highScore, sizeof(highScore));
    }
}
GameModel::GameModel(){
    loadHighScore();
    newGame();
}

GameModel::~GameModel(){
    saveScoreToFile();
}

void GameModel::newGame(){
    data.Reset();
    stack.destroyStack();
    playerRow.destroy();
    score = 0;
    speedBlocks = MAX_SPEED;
    timer = 1;
    stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
    data.newPlrRow = true;
    data.newRowDown = true;
    data.newGame = true;
    GameModel::stopTimer = false;
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
    bool isCorrect = stack.firstRow() == playerRow;
    if (isCorrect){
        data.correctTurn = true;
    }else
    {
        data.inCorrectTurn = true;
    }
    return isCorrect;
}
void GameModel::motionLeft(){
    if (playerRow[0].isEmpty()){
        playerRow.swapBlocks(0, 1);
        playerRow.swapBlocks(1, 2);
        data.twoLeft =  true;
    }
    else if (playerRow[1].isEmpty()){
        playerRow.swapBlocks(1, 2);
        data.oneLeft = true;
        }
    else{
        playerRow.swapBlocks(0, 1);
        data.blockSwap = true;
    }
}

void GameModel::motionRight(){
    if (playerRow[2].isEmpty()){
        playerRow.swapBlocks(1, 2);
        playerRow.swapBlocks(0, 1);
        data.twoRight = true;
    }
    else if (playerRow[1].isEmpty()){
        playerRow.swapBlocks(0, 1);
        data.oneRight = true;
    }
    else{
        playerRow.swapBlocks(1, 2);
        data.blockSwap = true;
    }
}

void GameModel::effectClearButton(){
    addScore(stack.size());
    stack.destroyStack();
    stack.addRowDown(stack.generateRow());
    playerRow = stack.generateTwoBlocks();
    data.newPlrRow = true;
    data.newRowDown = true;
}

void GameModel::updateTimer(){
    if (GameModel::stopTimer){
        std::cout<<"STOPTIMER"<<std::endl;
        return;
    }
    ++timer;
    if(timer % speedBlocks == 0){
        effectIntTimer();
    }
}

void GameModel::effectIntTimer(){
    if (stack.size() < MAX_SIZE_LIST){
        stack.addRowDown(stack.generateRow());
        data.fieldUp = true;
        data.newRowDown = true;
    }else{
        //stack.destroyStack();
        //playerRow.destroy();
        if (score > highScore){
            highScore = score;
            saveScoreToFile();
        }
        data.gameOver = true;
    }
    timer = 1;
}
void GameModel::effectAfterCorrectTurn(){
    addScore();
    //std::cout << stack.size()<<std::endl;
    stack.destroyRow();
    if(stack.size() == 0){
        stack.addRowDown(stack.generateRow());
        data.newRowDown = true;
    }
    playerRow = stack.generateTwoBlocks();
    data.newPlrRow = true;
    
    
}
void GameModel::effectAfterMistakeTurn(){
    if (stack.size() < MAX_SIZE_LIST){
        //stack.addRowDown(stack.generateRow());
        stack.addRowUp(stack.generateRowByTwo(playerRow));
        playerRow = stack.generateTwoBlocks();
        data.newPlrRow = true;
    }
    else{
        //playerRow.destroy();
        //stack.destroyStack();
        if (score > highScore){
            highScore = score;
            saveScoreToFile();
        }
        data.gameOver = true;
    }
}

void GameModel::addScore(int i){
    score += i;
}

void GameModel::upSpeed(){
    if (score % STEP_SCORE_UP_SPEED == 0 && speedBlocks > MIN_SPEED)
        setSpeed(speedBlocks - MAX_SPEED/10);
};
void GameModel::saveScoreToFile(){
    s3eSecureStoragePut(&highScore, sizeof(highScore));
};
