/*
 * (C) 2001-2013 Marmalade.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// Includes
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;

namespace Iw2DSceneGraph {

//------------------------------------------------------------------------------
// CColor
//------------------------------------------------------------------------------
CColor::CColor()
{
    r = g = b = a = 0xff;
}

CColor::CColor(uint8 r, uint8 g, uint8 b, uint8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

//------------------------------------------------------------------------------
// CAtlas
//------------------------------------------------------------------------------
CAtlas::CAtlas() : m_Image(NULL)
{
}
//------------------------------------------------------------------------------
CAtlas::CAtlas(int width, int height, int numFrames, CIw2DImage* image)
{
	m_Image = image;
	m_FrameWidth = width;
	m_FrameHeight = height;

	// Generate frames
	int w = (int)image->GetWidth();
	int x = 0, y = 0;
	for (int t = 0; t < numFrames; t++)
	{
		m_Frames.push_back(CIwRect(x, y, width, height));
		x += width;
		if (x >= w)
		{
			x = 0;
			y += height;
		}
	}
}
//------------------------------------------------------------------------------
CIw2DImage* CAtlas::GetImage()
{
	return m_Image;
}
//------------------------------------------------------------------------------
int CAtlas::GetNumFrames() const
{
	return m_Frames.size();
}
//------------------------------------------------------------------------------
int CAtlas::GetFrameWidth() const
{
	return m_FrameWidth;
}
//------------------------------------------------------------------------------
int CAtlas::GetFrameHeight() const
{
	return m_FrameHeight;
}
//------------------------------------------------------------------------------
const CIwRect& CAtlas::GetFrame(int index) const
{
	return m_Frames[index];
}

//------------------------------------------------------------------------------
// CDrawable
//------------------------------------------------------------------------------
CDrawable::CDrawable()
{
    m_DebugDraw = false;
    SET32(m_DebugColor, 0xff808080);
}
//------------------------------------------------------------------------------
void CDrawable::PreRender()
{
    // Set Iw2D transform
    Iw2DSetTransformMatrix(m_MatGlobal);

    // Set Iw2D color (and alpha)
    uint8 a = (uint8)(m_Color.a * m_Alpha);
    Iw2DSetColour(((*(uint32*)&m_Color) & 0xffffff) + (a << 24));
}
//------------------------------------------------------------------------------
void CDrawable::Update(float deltaTime, float alphaMul)
{
    // Any tweens
#ifdef IW_2DSCENEGRAPH_USE_TWEEN
    m_Tweener.Update(deltaTime);
#endif
    // Children
    CNode::Update(deltaTime, alphaMul);
}
//------------------------------------------------------------------------------
void CDrawable::Render()
{
    if (m_DebugDraw)
    {
        Iw2DSetColour(*(uint32*)&m_DebugColor);
        Iw2DDrawRect(CIwFVec2::g_Zero, CIwFVec2(m_W, m_H));
    }
    // Children
    CNode::Render();
}

//------------------------------------------------------------------------------
// CSprite
//------------------------------------------------------------------------------
CSprite::CSprite()
{
    m_Image = NULL;
	m_Atlas = NULL;
    nextAtlas=NULL;
	m_AnimTime = 0;
	m_AnimRepeat = -1;
    AnimProcess = false;

    // Let's make sprites have a red DebugColor
    SET32(m_DebugColor, 0xff0000ff);
}
//------------------------------------------------------------------------------
void CSprite::SetImage(CIw2DImage* pImage)
{
    if (pImage!=NULL){
        m_Image = pImage;
        m_W = pImage->GetWidth();
        m_H = pImage->GetHeight();
    }
}
//------------------------------------------------------------------------------
CIw2DImage* CSprite::GetImage()
{
	return m_Image;
}
//------------------------------------------------------------------------------
void CSprite::SetAtlas(CAtlas* pAtlas,CAtlas* pnAtlas)
{
	m_Atlas = pAtlas;
    nextAtlas = pnAtlas;
	m_Image = pAtlas->GetImage();
	m_AnimTime = 0;
    AnimProcess = false;
}
//------------------------------------------------------------------------------
CAtlas* CSprite::GetAtlas()
{
	return m_Atlas;
}
//------------------------------------------------------------------------------
void CSprite::SetAnimDuration(float duration)
{
	m_AnimDuration = duration;
	m_AnimTime = 0;
}
//------------------------------------------------------------------------------
void CSprite::SetAnimRepeat(int count)
{
	m_AnimRepeat = count;
}
//------------------------------------------------------------------------------
void CSprite::Update(float deltaTime, float alphaMul)
{
    if (m_AnimRepeat > 0)
        AnimProcess = true;
    else
        AnimProcess = false;
	if (m_Atlas != NULL && m_AnimRepeat != 0 && AnimProcess)
	{
        //AnimProcess = true;
		m_AnimTime += deltaTime;
		if (m_AnimTime >= m_AnimDuration)
		{
			if (m_AnimRepeat > 0)
				m_AnimRepeat--;
			while (m_AnimTime >= m_AnimDuration)
            {
                m_AnimTime = 0;
                if (nextAtlas != NULL){
                    CAtlas* p = m_Atlas;
                    m_Atlas = nextAtlas;
                    nextAtlas = p;
                    m_Image = m_Atlas->GetImage();
                }
            }
		}
	}

	CDrawable::Update(deltaTime, alphaMul);
}
//------------------------------------------------------------------------------
void CSprite::Render()
{
	if (!m_IsVisible)
		return;

    PreRender();
	if (m_Atlas)
	{
		int frame = (int)((m_AnimTime * m_Atlas->GetNumFrames()) / m_AnimDuration);
		const CIwRect& rc = m_Atlas->GetFrame(frame);
		m_W = rc.w;
		m_H = rc.h;
		Iw2DDrawImageRegion(m_Image, CIwFVec2(0, 0), CIwFVec2(rc.x, rc.y), CIwFVec2(rc.w, rc.h));
	}
	else
    if (m_Image)
        Iw2DDrawImage(m_Image, CIwFVec2::g_Zero);

    // Children
    CDrawable::Render();
}

//------------------------------------------------------------------------------
// CLabel
//------------------------------------------------------------------------------
CLabel::CLabel()
{
    m_Font = NULL;
    m_Text = "";
    m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    m_AlignVer = IW_2D_FONT_ALIGN_TOP;

    // Let's make labels have a green DebugColor
    SET32(m_DebugColor, 0xff00ff00);
}
//------------------------------------------------------------------------------
void CLabel::Render()
{
	if (!m_IsVisible)
		return;

    if (m_Font && m_Text.size())
    {
        Iw2DSetFont(m_Font);

        // If m_W not explicitly set, set to width of text on single line
        if (m_W == 0.0f)
            m_W = (float)Iw2DGetStringWidth(m_Text.c_str());

        // If m_H not explicitly set, set to height of font (i.e. height of single line)
        if (m_H == 0.0f)
            m_H = (float)m_Font->GetHeight();
        
        PreRender();
        Iw2DDrawString(m_Text.c_str(),
            CIwFVec2::g_Zero, CIwFVec2(m_W, m_H),
            m_AlignHor, m_AlignVer); 
    }
    // Children
    CDrawable::Render();
}

} // namespace Iw2DSceneGraph
