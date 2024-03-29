#ifndef STREN_FONTS_REPOSITORY_H
#define STREN_FONTS_REPOSITORY_H

#include "common/string_ext.h"
#include "render/font_texture.h"

namespace stren
{
///
/// class FontsRepository
///
class FontsRepository
{
private:
    bool                                            m_isReady; /// flag if repository is loaded and ready
    std::unordered_map<std::string, FontTexture>    m_fonts;   ///< loaded fonts
public:
    ///
    /// Constructor
    ///
    FontsRepository();
    ///
    /// initialize repository
    ///
    bool initialize();
    ///
    /// release loaded fonts
    ///
    void release();
    ///
    /// returns texture for the specific font
    ///
    ITexture * getTexture(const std::string & fontId);
};

} // stren

#endif // STREN_FONTS_REPOSITORY_H
