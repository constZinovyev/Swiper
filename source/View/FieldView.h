#pragma once
#include "BlockView.h"
//#include "../Model/StackRow.h"
#include <vector>
#include "scene.h"
using std::vector;
#define MAX_LEN_ROW 3
#define MAX_SIZE_LIST 6
//extern const short int MAX_LEN_ROW;
//extern const short int MAX_SIZE_LIST;

class FieldView{
    vector<vector<BlockView> > field;
    float xOrigin;
    float yOrigin;
    float xBetweenBLock;
    float yBetweenBLock;
    friend class PlayScene;
    void clearField();
    
public:
    FieldView();
    void updateField(vector<vector<int> >);
    void addToScene(Scene*);
};

class PlayerBlocks{
    BlockView plrBlc[MAX_LEN_ROW];
    float xOrigin;
    float yOrigin;
    float xBetweenBLock;
public:
    PlayerBlocks();
    void updateBlocks(vector<int> clr);
    void addToScene(Scene*);
    
    
};