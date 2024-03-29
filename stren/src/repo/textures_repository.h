#ifndef STREN_TEXTURES_REPO_H
#define STREN_TEXTURES_REPO_H

#include <unordered_map>

#include "common/string_ext.h"
#include "render/image_texture.h"

namespace stren
{
///
/// Textures Repository, stores textures that were asked for
///
class TexturesRepository
{
private:
    bool                                          m_isReady;    ///< flag if repository is loaded and ready
    std::unordered_map<std::string, ImageTexture> m_textures;   ///< loaded textures

public:
    ///
    ///Constructor
    ///
    TexturesRepository();
    ///
    /// initialize repository
    ///
    bool initialize();
    ///
    /// release loaded textures
    ///
    void release();
    ///
    /// returns specific texture
    ///
    ITexture * getTexture(const std::string & textureId);
};

} // stren

#endif // STREN_TEXTURES_REPO_H
