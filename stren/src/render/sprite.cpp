#include "sprite.h"

#include "colour.h"
#include "engine_handler.h"
#include "texture.h"

namespace stren
{
Sprite::Sprite()
    : m_texture(nullptr)
    , m_isDirty(true)
    , m_colour(Colour::Black)
{
}

Sprite::Sprite(const std::string & textureId, const Rect & rect, const Colour & colour)
    : m_texture(nullptr)
    , m_textureId(textureId)
    , m_rect(rect)
    , m_isDirty(true)
    , m_colour(colour)
{
}

void Sprite::render(const Rect & destRect, const double angle, const int flip, const Point & center)
{
    if (m_isDirty)
    {
        m_texture = EngineHandler::getTexture(m_textureId);
        m_isDirty = false;
    }
    if (m_texture)
    {
        m_texture->render(m_rect, destRect, angle, flip, center, m_colour);
    }
}
} // stren