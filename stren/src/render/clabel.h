#ifndef STREN_CLABEL_H
#define STREN_CLABEL_H

#include <vector>

#include "glyph.h"

namespace stren
{
///
/// class CLabel
///
class CLabel
{
private:
    Colour              m_colour;    ///< @todo
    std::string         m_text;      ///< @todo
    std::string         m_fontId;    ///< @todo
    Rect                m_textRect;  ///< @todo
    std::vector<Glyph>  m_glyphs;    ///< @todo
public:
    ///
    /// Constructor
    ///
    CLabel();
    ///
    /// changes current text colour
    ///
    inline void setColour(const Colour & colour) { m_colour = colour; }
    ///
    /// returns current text colour
    ///
    inline const Colour & getColour() const { return m_colour; }
    ///
    /// changes current font
    ///
    inline void setFont(const std::string & fontId) { m_fontId = fontId; }
    ///
    /// returns current font
    ///
    inline const std::string & getFont() const { return m_fontId; }
    ///
    /// changes current text
    ///
    void setText(const std::string & text);
    ///
    /// returns current text
    ///
    const std::string & getText() const { return m_text; }
    ///
    /// render glyphs
    ///
    void render();
    ///
    /// update glyphs
    ///
    void update(const Rect & rect, const int alignment);
    ///
    /// align glyphs
    ///
    void align(const Rect & rect, const int alignment);
};
} // stren

#endif // STREN_CLABEL_H
