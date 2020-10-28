#ifndef STREN_TEXTURES_DATA_H
#define STREN_TEXTURES_DATA_H

#include <map>

#include "common/string_ext.h"
#include "render/sprite.h"

namespace stren
{
class Sprite;
///
/// class SpritesRepository
///
class SpritesRepository
{
private:
    bool                            m_isReady;      ///< flag if repository is loaded and ready
    std::map<std::string, Sprite>   m_sprites;      ///< loaded sprites
public:
    ///
    /// Constructor
    ///
    SpritesRepository();
    ///
    /// initialize repository
    ///
    bool initialize();
    ///
    /// release loaded sprites
    ///
    void release();
    ///
    /// returns sprite for the specific id
    ///
    Sprite * getSprite(const std::string & spriteId);
};
} // stren

#endif