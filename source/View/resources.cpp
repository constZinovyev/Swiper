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


Resources::Resources()
{
    Blocks[0] = Iw2DCreateImage("textures/Object0.png");
    Blocks[1] = Iw2DCreateImage("textures/Object1.png");
    Blocks[2] = Iw2DCreateImage("textures/Object2.png");
    Blocks[3] = Iw2DCreateImage("textures/Object3.png");
    MenuBG = Iw2DCreateImage("textures/Swiperbackground.png");
    MenuBGtest = Iw2DCreateImage("textures/Swiperbackground1.png");
    
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

Resources::~Resources()
{
    
    delete Blocks[0];
    delete Blocks[1];
    delete Blocks[2];
    delete Blocks[3];
    delete MenuBG;
    delete MenuBGtest;
    /*for (int t = 0; t < MAX_GEM_TYPES; t++)
    {
        delete Gems[t];
        delete GemAtlases[t];
    }*/
    
}

// Global resources
Resources* g_pResources = 0;



