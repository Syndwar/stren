#ifndef STREN_GLYPH_H
#define STREN_GLYPH_H

#include "rect.h"
#include "colour.h"

namespace stren {

class ITexture;
///
/// class Glyph
///
class Glyph
{
private:
    ITexture *  m_texture;            ///< the font texture
    Rect        m_srcRect;            ///< glyph's place on the texture
    Rect        m_dstRect;            ///< glyph's place on the screen
    Colour      m_colour;             ///< glyph's colour
public:
    ///
    /// Default Constructor
    ///
    Glyph();
    ///
    /// Constructor
    ///
    Glyph(const char letter, const std::string & fontId, const Colour & colour);
    ///
    /// Copy constructor
    ///
    Glyph(const Glyph & glyph);
    ///
    /// get glyph's width
    ///
    inline int getWidth() const { return m_srcRect.getWidth(); }
    ///
    /// get glyph's height
    ///
    inline int getHeight() const { return m_srcRect.getHeight(); }
    ///
    /// render glyph on the screen
    ///
    void render();
    ///
    /// change glyph's position on the screen
    ///
    void moveTo(const int x, const int y) { m_dstRect.moveTo(x, y);}
    ///
    /// change glyph's position on the screen
    ///
    void moveBy(const int dx, const int dy) { m_dstRect.moveBy(dx, dy); }
}; // class Glyph
}
#endif // STREN_GLYPH_H
