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

#ifndef IW_2D_SCENE_GRAPH_H
#define IW_2D_SCENE_GRAPH_H

// Includes
#include "Iw2DSceneGraphCore.h"
#include "Iw2D.h"
#include "IwGxTypes.h"
#include <string>

// Required only if you want tweening support through CDrawable::m_Tweener
#ifdef IW_2DSCENEGRAPH_USE_TWEEN
#include "IwTween.h"
#endif

/**
 * @addtogroup iw2dscenegraph Iw2D Scene Graph API Reference
 * @{
 */

namespace Iw2DSceneGraph {

//------------------------------------------------------------------------------
// CColor
//------------------------------------------------------------------------------
/**
 * Simple color class, providing 8-bit r, g, b and a.
 */
class CColor
{
public:
    CColor();
    CColor(uint8 r, uint8 g, uint8 b, uint8 a);
    uint8 r, g, b, a;
};

//------------------------------------------------------------------------------
// CAtlas
//------------------------------------------------------------------------------
/**
 * Image atlas class, used by sprite aimation system
 */
class CAtlas
{
protected:
	CIw2DImage*				m_Image;
	std::vector<CIwRect>	m_Frames;
	int						m_FrameWidth;
	int						m_FrameHeight;
public:
    CAtlas();
    CAtlas(int width, int height, int numFrames, CIw2DImage* image);
	CIw2DImage*		GetImage();
	int				GetNumFrames() const;
	int				GetFrameWidth() const;
	int				GetFrameHeight() const;
	const CIwRect&	GetFrame(int index) const;
};

//------------------------------------------------------------------------------
// CDrawable
//------------------------------------------------------------------------------
/**
 * A drawable node. Provides color member and shared PreRender() function for setting up
 * transform and color.
 */
class CDrawable : public Iw2DSceneGraphCore::CNode
{
public:
    CDrawable();
    virtual void PreRender();
    virtual void Update(float deltaTime, float alphaMul);
    virtual void Render();

    CColor  m_Color;
    CColor  m_DebugColor;
    bool    m_DebugDraw;
#ifdef IW_2DSCENEGRAPH_USE_TWEEN
    IwTween::CTweenManager m_Tweener;
#endif
};

//------------------------------------------------------------------------------
// CSprite
//------------------------------------------------------------------------------
/**
 * A node that can draw an image at arbitrary transform and color.
 */
class CSprite : public CDrawable
{
protected:
    CIw2DImage* m_Image;                // Current image, if any
	CAtlas*		m_Atlas;                // Current atlas, if any
	float		m_AnimTime;				// Current atlas frame index
	float		m_AnimDuration;			// Atlas animation duration
	int			m_AnimRepeat;			// Number of times to repeat the animation
    CAtlas*     nextAtlas;
    bool AnimProcess;
public:
    CSprite();
    ~CSprite() {};
    bool isAnimProcess() { return AnimProcess;}
    void SetImage(CIw2DImage* pImage);
    CIw2DImage* GetImage();
    void		SetAtlas(CAtlas* pAtlas,CAtlas* pnAtlas = NULL);
	CAtlas*		GetAtlas();
    void		SetAnimDuration(float duration);
    void		SetAnimRepeat(int count);
    void		Update(float deltaTime, float alphaMul);
    void        Render();
};

//------------------------------------------------------------------------------
// CLabel
//------------------------------------------------------------------------------
/**
 * A node that can draw a text label with arbitrary font and text string.
 */
class CLabel : public CDrawable
{
public:
    CLabel();
    ~CLabel() {};

    void SetFont(CIw2DFont* pFont) { m_Font = pFont; }
    void SetText(std::string& text) { m_Text = text; }
    void SetText(const char* text) { m_Text = text; }
    void Render();

    CIw2DFont*      m_Font;
    CIw2DFontAlign  m_AlignHor;
    CIw2DFontAlign  m_AlignVer;
    std::string     m_Text;
};

} // namespace Iw2DSceneGraph

#endif // IW_2D_SCENE_GRAPH_H
