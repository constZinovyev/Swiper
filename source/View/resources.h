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
    CIw2DImage*     backAfterDie;
    CIw2DImage*     imgButtonStart;
    CIw2DImage*     Info;
    CIw2DImage*     Retry;
    CIw2DImage*     Blocks[MAX_BLOCK_TYPES+1];
    CIw2DImage*     listScore;
    CIwGxFont*      Font;
//    CAtlas*         GemAtlases[MAX_GEM_TYPES];
public:
    CIw2DImage*     getMenuBG()                 { return MenuBG; }
    CIw2DImage*     getRetry()                 { return Retry; }
    CIw2DImage*     getInfo()                 { return Info; }
    CIw2DImage*     getBackAfterDie()             { return backAfterDie; }
    CIw2DImage*     getBlocks(int i)            { return Blocks[i];}
    CIw2DImage*     getButStart()               { return imgButtonStart;}
    CIwGxFont*      getFont()                   { return Font;}
//    CAtlas*         getGemAtlas(int index)      { return GemAtlases[index]; }
    

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;

#endif  // __RESOURCES_H
