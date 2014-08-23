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

#include "Input.h"
#include <iostream>

Input* g_pInput = 0;

/**
 * @fn    void Input::TouchButtonCB(s3ePointerEvent* event)
 *
 * @brief The system will call this callback when the user touches the screen.
 *
 * @param event   If non-null, the event.
 */
void Input::TouchButtonCB(s3ePointerEvent* event)
{
    if (g_pInput->ignoreInput)
        return;
    
    //std::cout<<"TOUCH"<<std::endl;
    g_pInput->m_PrevTouched = g_pInput->m_Touched;
    g_pInput->m_Touched = event->m_Pressed != 0;
    g_pInput->m_X = event->m_x;
    g_pInput->m_Y = event->m_y;
    
    if(g_pInput->Motion || g_pInput->StartMotion){
        
        g_pInput->FinishMotion = true;
        g_pInput->Motion = false;
        g_pInput->StartMotion = false;
    }else{
        g_pInput->swipeLeft = false;
        g_pInput->swipeRight = false;
        g_pInput->swipeDown = false;
        g_pInput->didSwipe = false;
        g_pInput->ignoreSwipe = false;
        g_pInput->StartMotion = true;
        g_pInput->xStartSwipe = g_pInput->m_X;
        g_pInput->yStartSwipe = g_pInput->m_Y;
        g_pInput->Motion = true;
    }
    
}

/**
 * @fn    void Input::TouchMotionCB(s3ePointerMotionEvent* event)
 *
 * @brief The system will call this callback when the user moves their finger on the screen.
 *
 * @param event   If non-null, the event.
 */
void Input::TouchMotionCB(s3ePointerMotionEvent* event)
{
    //std::cout<<"MOTION"<<std::endl;
    if (g_pInput->ignoreInput)
        return;
    if (g_pInput->StartMotion){
        g_pInput->StartMotion = false;
        g_pInput->Motion = true;
    }
    if (g_pInput->Motion) {
        g_pInput->m_X = event->m_x;
        g_pInput->m_Y = event->m_y;
    }
    if (g_pInput->isMotion() && !g_pInput->ignoreSwipe){
        CIwSVec2 dirGest;
        dirGest.x =  g_pInput->m_X - g_pInput->xStartSwipe;
        dirGest.y =  g_pInput->m_Y - g_pInput->yStartSwipe;
        float lenSwipe = dirGest.GetLength();
        //std::cout << g_pInput->xStartSwipe <<" " << g_pInput->yStartSwipe<< std::endl;
        //std :: cout << lenSwipe << std::endl;
        if (lenSwipe >= 15 && !g_pInput->didSwipe){
            CIwSVec2 xDecart = CIwSVec2(1, 0);
            float cosDir = (xDecart.x * dirGest.x - xDecart.y * dirGest.y)/lenSwipe;
            if (cosDir >= sqrt(3)/2.0 && cosDir <= 1){
                g_pInput-> swipeRight = true;
                g_pInput->didSwipe = true;
                
            } else  if (cosDir < 1/2.0 && cosDir >-1/2.0){
                g_pInput->swipeDown = true;
                g_pInput->didSwipe = true;
                
            }
            else if (cosDir <= -sqrt(3)/2.0 && cosDir >= -1){
                g_pInput->swipeLeft = true;
                g_pInput->didSwipe = true;
            }
            
        }
        //std :: cout << g_pInput->swipeRight << " " << g_pInput->swipeDown << " " << g_pInput->swipeLeft << std :: endl;
        
    }
}

/**
 * @fn    void Input::MultiTouchButtonCB(s3ePointerTouchEvent* event)
 *
 * @brief The system will call this callback when the user touches the screen.
 *
 * @param event   If non-null, the event.
 */
void Input::MultiTouchButtonCB(s3ePointerTouchEvent* event)
{
    if (g_pInput->ignoreInput)
        return;
    g_pInput->m_PrevTouched = g_pInput->m_Touched;
    g_pInput->m_Touched = event->m_Pressed != 0;
    g_pInput->m_X = event->m_x;
    g_pInput->m_Y = event->m_y;
    if(g_pInput->Motion || g_pInput->StartMotion){
        g_pInput->FinishMotion = true;
        g_pInput->Motion = false;
        g_pInput->StartMotion = false;
    }else{
        g_pInput->StartMotion = true;
        g_pInput->swipeLeft = false;
        g_pInput->swipeRight = false;
        g_pInput->swipeDown = false;
        g_pInput->didSwipe = false;
        g_pInput->ignoreSwipe = false;
        
        g_pInput->xStartSwipe = g_pInput->m_X;
        g_pInput->yStartSwipe = g_pInput->m_Y;
    }
    
}

/**
 * @fn    void Input::MultiTouchMotionCB(s3ePointerTouchMotionEvent* event)
 *
 * @brief The system will call this callback when the user moves their finger on the screen.
 *
 * @param event   If non-null, the event.
 */
void Input::MultiTouchMotionCB(s3ePointerTouchMotionEvent* event)

{
    
    if (g_pInput->ignoreInput)
        return;
    if (g_pInput->StartMotion){
        g_pInput->StartMotion = false;
        g_pInput->Motion = true;
    }
    if (g_pInput->Motion) {
        g_pInput->m_X = event->m_x;
        g_pInput->m_Y = event->m_y;
    }
    if (g_pInput->isMotion() && !g_pInput->ignoreSwipe){
        CIwSVec2 dirGest;
        dirGest.x =  g_pInput->m_X - g_pInput->xStartSwipe;
        dirGest.y =  g_pInput->m_Y - g_pInput->yStartSwipe;
        float lenSwipe = dirGest.GetLength();
        if (lenSwipe >= 15 && !g_pInput->didSwipe){
            CIwSVec2 xDecart = CIwSVec2(1, 0);
            float cosDir = (xDecart.x * dirGest.x - xDecart.y * dirGest.y)/lenSwipe;
            if (cosDir >= sqrt(3)/2.0 && cosDir <= 1){
                g_pInput->swipeRight = true;
                g_pInput->didSwipe = true;
                //BUGS edit
            } else  if (cosDir < 1/2.0 && cosDir >-1/2.0){// && g_pInput->yStartSwipe - dirGest.y > 0){
                g_pInput->swipeDown = true;
                g_pInput->didSwipe = true;
            }
            else if (cosDir <= -sqrt(3)/2.0 && cosDir >= -1){
                g_pInput->swipeLeft = true;
                g_pInput->didSwipe = true;
            }
        }
    }
}

Input::Input() : m_X(0), m_Y(0), m_Touched(false), m_PrevTouched(false)
{
    ignoreSwipe = false;
    swipeLeft = false;
    swipeDown = false;
    ignoreInput = false;
    swipeRight = false;
    FinishMotion = false;
    Motion = false;
    StartMotion = false;
    didSwipe = false;
    xStartSwipe = 0;
    yStartSwipe = 0;
    
    // Set touch event callback handlers, single and multi-touch devices have different callbacks assigned
    if (s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) != 0)
    {
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, 0);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, 0);
    }
    else
    {
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)TouchButtonCB, 0);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)TouchMotionCB, 0);
    }
}

void Input::Update()
{
    s3ePointerUpdate();
}
void Input::Restart(){
    g_pInput->ignoreSwipe = false;
    g_pInput->ignoreInput = false;
    g_pInput->swipeLeft = false;
    g_pInput->swipeDown = false;
    g_pInput->swipeRight = false;
    g_pInput->didSwipe = false;
    g_pInput->FinishMotion = false;
    g_pInput->Motion = false;
    g_pInput->StartMotion = false;
    g_pInput->xStartSwipe = 0;
    g_pInput->yStartSwipe = 0;
    g_pInput->m_PrevTouched = false;
    g_pInput->m_Touched = false;
}

void Input::Reset()
{
    FinishMotion = false;
    m_PrevTouched = false;
    m_Touched = false;
}

void Input::afterSwipeDown(){g_pInput->swipeDown = false;};
void Input::afterSwipeLeft(){g_pInput->swipeLeft = false;};
void Input::afterSwipeRight(){g_pInput->swipeRight = false;};

