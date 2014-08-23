#pragma once
#include "BlockView.h"
//#include "../Model/StackRow.h"
#include <vector>
#include "scene.h"
#include "device.h"
#include "IwTween.h"
#include "Input.h"

using std::vector;
#define MAX_LEN_ROW 3
#define MAX_SIZE_LIST 5
#define ANIM_SWAP_DUR  0.2
//extern const short int MAX_LEN_ROW;
//extern const short int MAX_SIZE_LIST;
 extern CTweenManager* g_pTweener;

class FieldView{
    vector<vector<BlockView> > field;
    int xOrigin;
    int yOrigin;
    int xBetweenBLock;
    int yBetweenBLock;
    friend class PlayScene;
    friend class MainScene;
    void            clearField();
    void            setupViewSimulator();
    void            setupViewIphone5();
    void            setupViewIphone4();
    
public:
    FieldView();
    void updateField(vector<vector<int> >);
    void addToScene(Scene*);
    void animFieldUp();
    void animNewRowDown();
};

class PlayerBlocks{
    BlockView plrBlc[MAX_LEN_ROW];
    bool isChanged;
    int xOrigin;
    int yOrigin;
    int xBetweenBLock;
    void            setupViewSimulator();
    void            setupViewIphone5();
    void            setupViewIphone4();
public:
    PlayerBlocks();
    void updateBlocks(vector<int> clr);
    void addToScene(Scene*);
    void animMoveOneLeft();
    void animMoveOneRight();
    void animMoveTwoLeft();
    void animMoveTwoRight();
    void animSwapBlocks();
    void animNewBlocks(vector<int> clr);
    void setChanged(bool b) {isChanged = b;}
    void resetChanged()     {isChanged = false;}
    friend class PlayScene;
    friend class MainScene;
};

extern Device currentDevice;