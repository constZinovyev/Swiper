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

#if !defined(_INPUT_H)
#define _INPUT_H

#include "s3ePointer.h"
#include "IwGeom.h"
#include "IwTween.h"
#include <iostream>

using namespace IwTween;

#define MAX_TOUCHES     10
class Input;
extern Input* g_pInput;
/**
 * @class Input
 *
 * @brief Input - The Input class is responsible for handling all pointer input.
 *
 * Example usage:
 * @code
 *    // Set up input systems
 *    g_pInput = new Input();
 *
 *    // Update
 *    while (!s3eDeviceCheckQuitRequest())
 *    {
 *        // Update input system
 *        g_pInput->Update();
 *    }
 *
 *    // Cleanup
 *    delete g_pInput;
 * @endcode
 */
class Input
{
public:
    int             m_X, m_Y;           // Touched position
    bool            m_Touched;          // Touched status
    bool            m_PrevTouched;      // Previous touched status
    bool            StartMotion;
    bool            FinishMotion;
    bool            Motion;
    int             xStartSwipe, yStartSwipe;
    bool            swipeLeft, swipeRight, swipeDown;
    bool            didSwipe;

public:
    bool            ignoreSwipe;
    bool            ignoreInput;
    Input();
    static void     onIgnoreInput(CTween* pTween) {g_pInput->Restart();g_pInput->ignoreInput = true;std::cout<< "ON"<<std::endl;}
    static void     offIgnoreInput(CTween* pTween) {g_pInput->ignoreInput = false;std::cout<< "OFF"<<std::endl;}

    /**
     * @fn    void Input::Update()
     *
     * @brief Updates the input system, called every frame
     */
    void            Update();
    /**
     * @fn    void Input::Reset()
     *
     * @brief Resets touch status, usually called after a touch event has been acknowledged
     */
    static void     Restart();
    void            Reset();
    bool isFinish() {return FinishMotion;};
    bool isStart()  {return StartMotion;}
    bool isMotion() {return Motion;}
    bool isSwipeLeft() {return swipeLeft;}
    bool isSwipeRight() {return swipeRight;}
    bool isSwipeDown() {return swipeDown;}
    bool wasSwipe()    {return didSwipe;}
    void afterSwipeDown();
    void afterSwipeLeft();
    void afterSwipeRight();
    void setIgnoreSwipe() { ignoreSwipe = true;}
    void notIgnoreSwipe() { ignoreSwipe = false;}
   

    // Callbacks
    static void     TouchButtonCB(s3ePointerEvent* event);
    static void     TouchMotionCB(s3ePointerMotionEvent* event);
    static void     MultiTouchButtonCB(s3ePointerTouchEvent* event);
    static void     MultiTouchMotionCB(s3ePointerTouchMotionEvent* event);
};



#endif  // _INPUT_H
