#ifndef STREN_MUSIC_REPOSITORY
#define STREN_MUSIC_REPOSITORY

#include <unordered_map>
#include "music.h"

namespace lua
{
    class Table;
}

namespace stren
{
///
/// class MusicRepository
///
class MusicRepository
{
private:
    static Music                 kEmptyMusic;           ///< empty sound
    bool                         m_isReady;             ///< flag if repository was initialized
    std::unordered_map<std::string, Music> m_tracks;    ///< loaded tracks
public:
    ///
    /// Constructor
    ///
    MusicRepository();
    ///
    /// initialize music repository
    ///
    void initialize(const lua::Table & tbl);
    ///
    /// free loaded music tracks
    ///
    void release();
    ///
    /// returns music track
    ///
    Music & getMusic(const std::string & id);
};
} // stren
#endif // STREN_MUSIC_REPOSITORY
