#include "clabel.h"

#include "lua/lua_wrapper.h"
#include "engine/engine_handler.h"
#include "repo/fonts_repository.h"
#include "render/renderer.h"

namespace stren
{
CLabel::CLabel()
    : m_colour(Colour::White)
{
}

void CLabel::setText(const std::string & text)
{
    m_text = EngineHandler::getTextByAlias(text);
    if (m_text.empty())
    {
        m_text = text;
    }
}

void CLabel::update(const Rect & rect, const int alignment)
{
    if (!m_text.empty() && !m_fontId.empty())
    {
        m_textRect.moveTo(0, 0);
        m_glyphs.clear();
        int offsetX(0);
        int offsetY(0);
        for (const char letter : m_text)
        {
            Glyph newGlyph(letter, m_fontId, m_colour);
            newGlyph.moveTo(offsetX, offsetY);
            const int glyphWidth = newGlyph.getWidth();
            const int glyphHeight = newGlyph.getHeight();
            offsetX += glyphWidth;

            if (m_textRect.getHeight() < glyphHeight)
            {
                m_textRect.setHeight(glyphHeight);
            }
            m_textRect.setWidth(offsetX);

            m_glyphs.push_back(newGlyph);
        }
    }
    align(rect, alignment);
}

void CLabel::align(const Rect & rect, const int alignment)
{
    const int oldX = m_textRect.getX();
    const int oldY = m_textRect.getY();
    rect.align(m_textRect, alignment);
    const int dx = m_textRect.getX() - oldX;
    const int dy = m_textRect.getY() - oldY;

    for (Glyph & glyph : m_glyphs)
    {
        glyph.moveBy(dx, dy);
    }
}

void CLabel::render()
{
    if (!m_glyphs.empty())
    {
        for (Glyph & glyph : m_glyphs)
        {
            glyph.render();
        }
    }
}

} // stren