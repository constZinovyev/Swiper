#pragma once
#include "Row.h"
#include <list>
#include <map>
#include <iostream>


using std::list;
using std::map;

//const short int MAX_SIZE_LIST = 7;
#define MAX_SIZE_LIST 6
class StackRow{
    vector<Row> modelRowStack;
    //Row genRow;
public:
    StackRow();
    Row firstRow()         {return modelRowStack[modelRowStack.size()-1];}
    Row& takeRow(int i)     {return modelRowStack[i];}
    void destroyRow()       {modelRowStack.pop_back();}
    void addRowDown(Row r); 
    void addRowUp(Row r)  {modelRowStack.push_back(r);}
    int  size()             {return modelRowStack.size();}
    Row generateRow();
    Row generateTwoBlocks();
    Row generateRowByTwo(Row);
    //void destroyLastRow();
    void destroyStack();
    friend class FieldView;
};
