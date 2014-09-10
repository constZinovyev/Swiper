#pragma once
#include "scene.h"
#include <string>
#include "Iw2DSceneGraph.h"
#include "resources.h"
#include "IwGx.h"
#include "../Controller/input.h"
#include "IwTween.h"
using namespace Iw2DSceneGraph;
using namespace Iw2DSceneGraphCore;
using std::string;

class Button{
    CSprite* buttonSprite;
    string textOnButton;
public:
    void setImage(CIw2DImage*);
    void setPosition(const float, const float);
    void setScale(float, float);
    void setAnchor(float, float);
    CSprite* getSprite()    {return buttonSprite;}
    void renderText();
    bool isPressed(int x = -1, int y = -1);
    friend class CTween;
    friend class CTweenManager;
    Button(Scene*,float,float,CIw2DImage*,string);
    ~Button();
};