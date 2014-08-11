#include "StackRow.h"
#include "Iw2D.h"

Row StackRow::generateRow(){
    
    Row tempRow;
    int numCol;
    for (int i = 1; i <= COUNT_COLORS;++i){
        do{
            numCol = IwRand()%MAX_LEN_ROW;//rand()%MAX_LEN_ROW;
        }while(!tempRow[numCol].isEmpty());
        tempRow[numCol].setColor(ColorBlock(i));
        //std::cout << numCol << " ";
    }
    //std :: cout << std :: endl;
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
void StackRow::addRowDown(Row r){
    if(modelRowStack.size()<MAX_SIZE_LIST){
    std::vector<Row>::iterator it;
    it = modelRowStack.begin();
        it = modelRowStack.insert ( it , r );}
}
//ПРИВЯЗКА К СРЕДНЕМУ ЭЛЕМЕНТУ
Row StackRow::generateTwoBlocks(){
    bool flag = false;
    Row genRow = firstRow();
    Row tempRow;
    do{
        tempRow = generateRow();
        tempRow.changeCol(IwRand()%MAX_LEN_ROW, Empty);//(rand()%MAX_LEN_ROW, Empty);
        flag = false;
        //std::cout << tempRow[0].getColor() << "+"<<tempRow[1].getColor()<<" " << tempRow[2].getColor() << " " << std::endl;
        //std::cout << genRow[0].getColor() << "-"<<genRow[1].getColor()<<" " << genRow[2].getColor() << " " << std::endl;
        if (tempRow[1].isEmpty()){
            if(genRow[0] == tempRow[2] && genRow[0] == tempRow[2]){
                flag = true;
                continue;
            }}else
        if (tempRow[0].isEmpty()){
            //std::cout<<"FIRST EMPTY"<<std::endl;
            if ((genRow[0] == tempRow[1] || genRow[0] == tempRow[2])&&(genRow[2] == tempRow[1] || genRow[2] == tempRow[2]))
            {
                flag = true;
                continue;
            }
        }else
        if (tempRow[2].isEmpty()){
            //std::cout<<"THIRD EMPTY"<<std::endl;
            if ((genRow[0] == tempRow[0] || genRow[0] == tempRow[1])&&(genRow[2] == tempRow[0] || genRow[2] == tempRow[1]))
            {
                flag = true;
                continue;
                }
        }
        
    }while(flag);
    return  tempRow;
}

Row StackRow::generateRowByTwo(Row withEmpty){
    bool maskWithEmpty[COUNT_COLORS];
    int lastClr = 0;
    int posEmpty = 0;
    for (int i = 0; i < COUNT_COLORS; ++i){
        maskWithEmpty[i] = false;
    }
    for (int i = 0; i < MAX_LEN_ROW; ++i){
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
    //modelRowStack.push_back(generateRow());
   // playerRow = generateTwoBlocks();//(modelRowStack.front());
}