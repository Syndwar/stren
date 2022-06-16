#ifndef STREN_SOUNDS_REPOSITORY
#define STREN_SOUNDS_REPOSITORY

#include <unordered_map>

#include "sound.h"

namespace lua
{
    class Table;
}

namespace stren
{
///
/// class SoundsRepository
///
class SoundsRepository
{
private:
    static Sound                            kEmptySound;    ///< empty sound
    bool                                    m_isReady;      ///< flag if repository was initialized
    std::unordered_map<std::string, Sound>  m_sounds;       ///< loaded sounds

public:
    ///
    /// Constructor
    ///
    SoundsRepository();
    ///
    /// initialize sound repository
    ///
    void initialize(const lua::Table & tbl);
    ///
    /// free loaded sounds
    ///
    void release();
    ///
    /// returns required sound
    ///
    Sound & getSound(const std::string & id);
};
} // stren

#endif // STREN_SOUNDS_REPOSITORY
