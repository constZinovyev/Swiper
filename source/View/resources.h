/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#if !defined(__RESOURCES_H)
#define __RESOURCES_H



#include "Iw2D.h"
#include "Iw2DSceneGraph.h"
#include "IwGx.h"
#include "IwGxFont.h"
#include "IwResManager.h"
using namespace Iw2DSceneGraph;
const short int MAX_BLOCK_TYPES = 3;

/**
 * @class Resources
 *
 * @brief Resources class
 *
 * The that manages the lifetime of the following types of resources:
 * - Images
 * - Fonts
 * - Atlases
 */
class Resources
{
protected:
    
    CIw2DImage*     MenuBG;
    CIw2DImage*     BGiPhone4;
    CIw2DImage*     backAfterDie;
    CIw2DImage*     imgButtonStart;
    CIw2DImage*     Info;
    CIw2DImage*     Retry;
    CIw2DImage*     Blocks[MAX_BLOCK_TYPES+1];
    CIw2DImage*     listScore;
    CIw2DImage*     lightToMiddle;
    CIw2DImage*     middleToLight;
    CIwGxFont*      Font;
    CAtlas*     animBetweenBlocks[6];
    CIw2DImage*         imgBlocks[6];
    CIw2DImage* emtBlock;
    CAtlas*         emptyBlock;
public:
    CIw2DImage*     getMenuBG()                 { return MenuBG; }
    CIw2DImage*     getBGiPhone4()                 { return BGiPhone4; }
    CIw2DImage*     getRetry()                 { return Retry; }
    CIw2DImage*     getInfo()                 { return Info; }
    CIw2DImage*     getBackAfterDie()             { return backAfterDie; }
    CIw2DImage*     getBlocks(int i)            { return Blocks[i];}
    CIw2DImage*     getButStart()               { return imgButtonStart;}
    CIwGxFont*      getFont()                   { return Font;}
    CIw2DImage*     getAnimBlocks(int i = 0,int = 0);
    CAtlas*         getFromFirstToSecond(int i = 0,int j = 0);
//    CAtlas*         getGemAtlas(int index)      { return GemAtlases[index]; }
    

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;

#endif  // __RESOURCES_H
