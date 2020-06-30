#include "glyph.h"

#include "engine_handler.h"
#include "point.h"
#include "sprite.h"
#include "texture.h"

namespace stren
{
Glyph::Glyph()
    : m_texture(nullptr)
{
}

Glyph::Glyph(const char letter, const std::string & fontId, const Colour & colour)
    : m_colour(colour)
{
    m_texture = EngineHandler::getTexture(fontId);
    if (m_texture)
    {
        if (FontTexture * texture = m_texture->toFontTexture())
        {
            m_srcRect = texture->getGlyphRect(letter);
        }
        m_dstRect = m_srcRect;
    }
}

Glyph::Glyph(const Glyph & glyph)
    : m_texture(glyph.m_texture)
    , m_srcRect(glyph.m_srcRect)
    , m_dstRect(glyph.m_dstRect)
    , m_colour(glyph.m_colour)
{
}

void Glyph::render()
{
    if (m_texture)
    {
        m_texture->render(m_srcRect, m_dstRect, 0, Sprite::Flip::None, Point::getEmpty(), m_colour);
    }
}
} // stren