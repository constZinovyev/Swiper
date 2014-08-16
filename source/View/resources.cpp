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

#include "resources.h"
#include "Iw2D.h"


Resources::Resources(){
    Blocks[0] = Iw2DCreateImage("textures/EmptyBlock.png");
    Blocks[1] = Iw2DCreateImage("textures/Object 1.png");
    Blocks[2] = Iw2DCreateImage("textures/Object 2.png");
    Blocks[3] = Iw2DCreateImage("textures/Object 3.png");
    
    imgBlocks[0]= Iw2DCreateImage("textures/anim12.png");
    imgBlocks[1]= Iw2DCreateImage("textures/anim13.png");
    imgBlocks[2]= Iw2DCreateImage("textures/anim21.png");
    imgBlocks[3]= Iw2DCreateImage("textures/anim23.png");
    imgBlocks[4]= Iw2DCreateImage("textures/anim31.png");
    imgBlocks[5]= Iw2DCreateImage("textures/anim32.png");
    emtBlock = Iw2DCreateImage("textures/EmptyBlock.png");
    imgButtonStart = Iw2DCreateImage("textures/buttonStart.png");
    MenuBG = Iw2DCreateImage("textures/Swiperbackground.png");
    Retry = Iw2DCreateImage("textures/Retry.png");
    Info = Iw2DCreateImage("textures/Info.png");
    //lightToMiddle = Iw2DCreateImage("textures/B-D.png");
    //middleToLight = Iw2DCreateImage("textures/D-B.png");
    backAfterDie = Iw2DCreateImage("textures/BackAfterDie.png");
    Font = (CIwGxFont*)IwGetResManager()->GetResNamed("SansusWR", "CIwGxFont");
    int frame_w = (int)(imgBlocks[0]->GetWidth() / 20.0);
    int frame_h = (int)(imgBlocks[0]->GetHeight()/1);
    for (int i = 0; i < 6; ++i){
        animBetweenBlocks[i] = new CAtlas(frame_w,frame_h,20,imgBlocks[i]);
    }
    
    emptyBlock = new CAtlas(emtBlock->GetWidth(),emtBlock->GetHeight(),1,emtBlock);
    //animLightToMiddle = new CAtlas(frame_w, frame_h, 20, lightToMiddle);
    //frame_w = (int)(middleToLight->GetWidth() / 20.0);
    //frame_h = (int)(middleToLight->GetHeight()/1);
    //animMiddleToLight = new CAtlas(frame_w, frame_h, 20, middleToLight);
    /*// Create atlases
    int frame_w = (int)(Gems[0]->GetWidth() / 5);
    int frame_h = (int)(Gems[0]->GetHeight() / 3);
    for (int t = 0; t < MAX_GEM_TYPES; t++)
        GemAtlases[t] = new CAtlas(frame_w, frame_h, 15, Gems[t]);
    frame_w = (int)(Explosion->GetWidth() / 5);
    frame_h = (int)(Explosion->GetHeight() / 3);
    ExplosionAtlas = new CAtlas(frame_w, frame_h, 15, Explosion);
     */
}

Resources::~Resources(){
    
    delete Blocks[0];
    delete Blocks[1];
    delete Blocks[2];
    delete Blocks[3];
    
    for (int i = 0; i < 6; ++i){
        delete imgBlocks[i];
        delete animBetweenBlocks[i];
    }
    delete emtBlock;
    delete emptyBlock;
    delete imgButtonStart;
    //delete animLightToMiddle;
    //delete animMiddleToLight;
    //delete middleToLight;
    //delete lightToMiddle;
    delete MenuBG;
    delete backAfterDie;
    delete Retry;
    delete Info;
     //IwGxFontDestroyTTFont(GxFont);
    /*for (int t = 0; t < MAX_GEM_TYPES; t++)
    {
        delete Gems[t];
        delete GemAtlases[t];
    }*/
    
}

CIw2DImage* Resources::getAnimBlocks(int i,int j){
    if ( i == 1 && (j == 2 || j == 1))
        return imgBlocks[0];
    if ( i == 1 && j == 3)
        return imgBlocks[1];
    if ( i == 2 && (j == 1 || j == 2))
        return imgBlocks[2];
    if ( i == 2 && j == 3)
        return imgBlocks[3];
    if ( i == 3 && (j == 1 || j == 3))
        return imgBlocks[4];
    if ( i == 3 && j == 2)
        return imgBlocks[5];
    return NULL;
}
CAtlas* Resources::getFromFirstToSecond(int i,int j){
    if ( i == 1 && (j == 2 || j == 1))
        return animBetweenBlocks[0];
    if ( i == 1 && j == 3)
        return animBetweenBlocks[1];
    if ( i == 2 && (j == 1 || j == 2))
        return animBetweenBlocks[2];
    if ( i == 2 && j == 3)
        return animBetweenBlocks[3];
    if ( i == 3 && (j == 1 || j == 3))
        return animBetweenBlocks[4];
    if ( i == 3 && j == 2)
        return animBetweenBlocks[5];
    return emptyBlock;
}
// Global resources
Resources* g_pResources = 0;



