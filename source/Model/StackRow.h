#pragma once
#include "Row.h"
#include <list>
#include <map>
using std::list;
using std::map;

const short int MAX_SIZE_LIST = 7;
class StackRow{
    list<Row> modelRowStack;
    //Row genRow;
public:
    StackRow();
    Row& firstRow()         {return modelRowStack.front();}
    void destroyRow()       {modelRowStack.pop_back();}
    void addRowUp(Row r)    {modelRowStack.push_front(r);}
    void addRowDown(Row r)  {modelRowStack.push_back(r);}
    int  size()             {return modelRowStack.size();}
    Row generateRow();
    Row generateTwoBlocks();
    Row generateRowByTwo(Row);
    //void destroyLastRow();
    void destroyStack();
    
};
