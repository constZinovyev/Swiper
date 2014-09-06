#pragma once
#include "BlockView.h"
#include <vector>
#include "scene.h"
#include "device.h"
#include "IwTween.h"
#include "../Controller/input.h"
#include "../Model/GameModel.h"
using std::vector;
#define MAX_LEN_ROW 3
#define MAX_SIZE_LIST 5
#define ANIM_SWAP_DUR  0.2
//extern const short int MAX_LEN_ROW;
//extern const short int MAX_SIZE_LIST;
 extern CTweenManager* g_pTweener;
class PlayerBlocks;
class FieldView{
    vector<vector<BlockView> > field;
    int xOrigin;
    int yOrigin;
    int xBetweenBLock;
    int yBetweenBLock;
    friend class PlayScene;
    friend class MainScene;
    void         clearField();
    void         setupViewSimulator();
    void         setupViewIphone5();
    void         setupViewIphone4();
    static bool clearUpRow;
    static bool animProcessFallDown;
    static bool animProcessNewDownRow;
    
public:
    FieldView();
    static void onCompleteAfterCorrect(CTween* Tween) {
        clearUpRow = true;
        animProcessFallDown = false;
        GameModel::activateTimer(Tween);
    }
        static void onCompleteAfterInCorrect(CTween* Tween) {
            animProcessFallDown = false;
            GameModel::activateTimer(Tween);
        }
    static void afterAnimNewRowDown(CTween* Tween);
    void updateField(vector<vector<int> >);
    void addToScene(Scene*);
    void fieldOneRowUp();
    void animFieldUp();
    void delUpRow();
    void animNewRowDown(vector<vector<int> >);
    void animCorrectTurn(vector<int>,PlayerBlocks&);
    void animInCorrectTurn(vector<int>,PlayerBlocks&,vector<vector<int> >&);
    friend class PlayerBlocks;
    void print();
};

class PlayerBlocks{
    vector<BlockView> plrBlc;
    int xOrigin;
    int yOrigin;
    int xBetweenBLock;
    void            setupViewSimulator();
    void            setupViewIphone5();
    void            setupViewIphone4();
public:
    PlayerBlocks();
    void updateNewBlocks(vector<int> clr);
    void addToScene(Scene*);
    void animMoveOneLeft();
    void animMoveOneRight();
    void animMoveTwoLeft();
    void animMoveTwoRight();
    void animSwapBlocks();
    void animNewBlocks();
    //void setChanged(bool b) {isChanged = b;}
    //void resetChanged()     {isChanged = false;}
    friend class PlayScene;
    friend class MainScene;
    friend class FieldView;
};
extern int t;
extern Device currentDevice;