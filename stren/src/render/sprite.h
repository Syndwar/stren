#ifndef STREN_SPRITE_H
#define STREN_SPRITE_H

#include "common/rect.h"
#include "common/string_ext.h"
#include "common/colour.h"

namespace stren
{

class ITexture;
///
/// class Sprite
///
class Sprite
{
public:
    enum Flip
    {
        None = 0x00000000,
        Horizontal = 0x00000001,
        Vertical = 0x00000002
    };                                   ///< possible flip values
private:

    bool            m_isDirty;           ///< @todo
    ITexture *      m_texture;           ///< texture interface
    Rect            m_rect;              ///< sprite rectangle
    std::string     m_textureId;         ///< @todo
    Colour          m_colour;            ///< sprite render colour
public:
    ///
    /// Default Constructor
    ///
    Sprite();
    ///
    /// Constructor
    ///
    Sprite(const std::string & textureId, const Rect & rect, const Colour & colour);
    ///
    /// @todo
    ///
    void render(const Rect & destRect, const double angle, const int flip, const Point & center);
};
} // stren
#endif // STREN_SPRITE_H
