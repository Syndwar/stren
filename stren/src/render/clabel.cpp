#include "clabel.h"

#include "lua/lua_wrapper.h"
#include "engine/engine.h"
#include "engine/engine_handler.h"
#include "repo/fonts_repository.h"
#include "render/renderer.h"

namespace stren
{
CLabel::CLabel()
    : m_colour(Colour::White)
    , m_isWrap(false)
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
        m_glyphs.clear();
        for (const char letter : m_text)
        {
            Glyph glyph(letter, m_fontId, m_colour);
            m_glyphs.push_back(glyph);
        }
    }
    align(rect, alignment);
}

void CLabel::align(const Rect & rect, const int alignment)
{
    int offsetX(0);
    int offsetY(0);
    int rowHeight(0);
    m_textRect.set(0, 0, 0, 0);

    for (Glyph & glyph : m_glyphs)
    {
        const int glyphWidth = glyph.getWidth();
        const int glyphHeight = glyph.getHeight();

        if (m_isWrap)
        {
            if (offsetX + glyphWidth > rect.getWidth())
            {
                offsetX = 0;
                offsetY += rowHeight;
                rowHeight = glyphHeight;
            }
        }

        glyph.moveTo(offsetX, offsetY);

        offsetX += glyphWidth;

        if (rowHeight < glyphHeight)
        {
            rowHeight = glyphHeight;
        }

        if (m_textRect.getHeight() < offsetY + glyphHeight)
        {
            m_textRect.setHeight(offsetY + glyphHeight);
        }
        if (m_textRect.getWidth() < offsetX + glyphWidth)
        {
            m_textRect.setWidth(offsetX + glyphWidth);
        }
    }

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