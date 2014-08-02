#include "StackRow.h"
#include <iostream>
Row StackRow::generateRow(){
    
    Row tempRow;
    int numCol;
    for (auto i = 1; i <= COUNT_COLORS;++i){
        do{
        numCol = rand()%MAX_LEN_ROW;
        }while(!tempRow[numCol].isEmpty());
        tempRow[numCol].setColor(ColorBlock(i));
    }
    /*map <ColorBlock,bool> maskRow;
    
    for (int i = 1; i < COUNT_COLORS;++i)
    {
        maskRow.insert(std::pair<ColorBlock,bool>(ColorBlock(i),false));
    }
    
    for (int i = 0; i < MAX_LEN_ROW;++i)
    {
        do{
            tempClr = ColorBlock(rand()%COUNT_COLORS+1);
        }while(maskRow[tempClr]);
        
        maskRow[tempClr] = true;
        tempRow.changeCol(i,tempClr);
    }
*/
    return tempRow;
}
//ПРИВЯЗКА К СРЕДНЕМУ ЭЛЕМЕНТУ
Row StackRow::generateTwoBlocks(){
    bool flag = false;
    Row genRow = modelRowStack.front();
    Row tempRow;
    do{
        tempRow = generateRow();
        tempRow.changeCol(rand()%MAX_LEN_ROW, Empty);
        flag = false;
        if (tempRow[1].isEmpty())
            if(genRow[0] == tempRow[2] && genRow[0] == tempRow[2]){
                flag = true;
            }
    }while(flag);
    return  tempRow;
}

Row StackRow::generateRowByTwo(Row withEmpty){
    bool maskWithEmpty[COUNT_COLORS];
    int lastClr = 0;
    int posEmpty = 0;
    for (auto i = 0; i < COUNT_COLORS; ++i){
        maskWithEmpty[i] = false;
    }
    for (auto i = 0; i < MAX_LEN_ROW; ++i){
        maskWithEmpty[withEmpty[i].getColor()] = true;
        if (withEmpty[i].isEmpty()){
            posEmpty = i;
        }
    }
    do{
        ++lastClr;
    }while(maskWithEmpty[lastClr]);
    withEmpty.changeCol(posEmpty, Block(ColorBlock(lastClr)));
    return withEmpty;
}

StackRow::StackRow(){
    //modelRowStack.push_back(generateRow());
    //playerRow = generateTwoBlocks(modelRowStack.front());
}

void StackRow::destroyStack(){
    modelRowStack.clear();
    modelRowStack.push_back(generateRow());
    playerRow = generateTwoBlocks(modelRowStack.front());
}