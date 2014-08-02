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

#include "s3e.h"
#include "Iw2D.h"
#include <iostream>
#include "Model/StackRow.h"

/*Tweener
 #include "IwTween.h"
 using namespace IwTween;
 extern CTweenManager*       g_pTweener;
 CTweenManager*  g_pTweener = 0;
*/
// FRAME_TIME is the amount of time that a single frame should last in seconds
#define FRAME_TIME  (60.0f / 1000.0f)



int main()
{
    // Initialise the 2D graphics system
    Iw2DInit();
/*  // FONTS
    IwGxInit();
    IwGxSetColClear(0xff, 0xff, 0xff, 0xff);
    IwGxPrintSetColour(128, 128, 128);
    IwResManagerInit();
    IwGxFontInit();
    IwGetResManager()->LoadGroup("./fonts/IwGxFontTTF.group");
*/
    srand(time(NULL));
    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        uint64 new_time = s3eTimerGetMs();
        s3eKeyboardUpdate();
        s3ePointerUpdate();
        
        /* Fonts
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
        IwGxLightingOn();
        */
        
        Iw2DSurfaceClear(0xff000000);
        //render image
        Iw2DFinishDrawing();
        
        //Render Text
        //IwGxFlush();
        Iw2DSurfaceShow();

        // Lock frame rate
        int yield = (int)(FRAME_TIME * 1000 - (s3eTimerGetMs() - new_time));
        if (yield < 0)
            yield = 0;
        // Yield to OS
        s3eDeviceYield(yield);
    }

      Iw2DTerminate();

    return 0;
}
