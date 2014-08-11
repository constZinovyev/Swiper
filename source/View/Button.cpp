#include "Button.h"

Button::Button(Scene* scn,float x, float y, CIw2DImage* img,string s){
    
    buttonSprite = new CSprite();
    buttonSprite->m_X = x;
    buttonSprite->m_Y = y;
    buttonSprite->SetImage(img);
    buttonSprite->m_AnchorX=0.0f;
    buttonSprite->m_AnchorY=0.0f;
    scn->AddChild(buttonSprite);
    
    textOnButton = s;
    /*textButton = new CLabel();
     textButton->m_X = buttonSprite->m_X;
     textButton->m_Y = buttonSprite->m_Y;
     //textButton->m_W = 320;
     //textButton->m_H = 100;
     textButton->m_Text = s.c_str();
     textButton->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
     textButton->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
     textButton->m_Font = g_pResources->getFont();
     textButton->m_AnchorX = 0.5f;
     textButton->m_AnchorY = 0.5f;
     textButton->m_ScaleX = 1;
     textButton->m_ScaleY = 1;
     textButton->m_Color =  CColor(0xff, 0xff,0xff,0xff);
     scn->AddChild(textButton);*/
}

void Button::setScale(float x, float y)
{
    buttonSprite->m_ScaleX = x;
    buttonSprite->m_ScaleY = y;
}
void Button::setAnchor(float x, float y)
{
    buttonSprite->m_AnchorX = x;
    buttonSprite->m_AnchorY = y;
}
void Button::setPosition(const float xPos, const float yPos){
    buttonSprite->m_X = xPos;
    buttonSprite->m_Y = yPos;
}

bool Button::isPressed(int x,int y){
    if (x<0 || y <0){
        x = g_pInput->m_X;
        y = g_pInput->m_Y;
    }
    return buttonSprite->HitTest(x, y);
}
void Button::renderText(){
    float width = buttonSprite->m_W;
    float height = buttonSprite->m_H;
    float x = buttonSprite->m_X;
    float y = buttonSprite->m_Y;
    
    IwGxFontSetRect(CIwRect(x,y,width,height));
    
    //Set the alignment within the formatting rect
    IwGxFontSetAlignmentVer(IW_GX_FONT_ALIGN_MIDDLE);
    IwGxFontSetAlignmentHor(IW_GX_FONT_ALIGN_CENTRE);
    
    // Draw title text
    IwGxFontSetFont(g_pResources->getFont());
    IwGxFontDrawText(textOnButton.c_str(),textOnButton.size());
    
}
void Button::setImage(CIw2DImage* img){
    buttonSprite -> SetImage(img);
    buttonSprite -> m_W = buttonSprite -> GetImage() -> GetWidth();
    buttonSprite -> m_H = buttonSprite -> GetImage() -> GetHeight();
}
Button::~Button(){
    
}