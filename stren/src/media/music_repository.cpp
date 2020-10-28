#include "music_repository.h"

#include "lua/lua_wrapper.h"

namespace stren
{

Music MusicRepository::kEmptyMusic;

MusicRepository::MusicRepository()
    : m_isReady(false)
{
}

void MusicRepository::initialize(const lua::Table & tbl)
{
    if (!m_isReady)
    {
        for (size_t i = 1, i_end = tbl.getSize(); i <= i_end; ++i)
        {
            lua::Table musicTable(tbl.get(i));
            const std::string id = musicTable.get("id").getString();
            const std::string filename = musicTable.get("filename").getString();
            m_tracks[id] = Music(id, filename);
        }
        m_isReady = true;
    }
}

void MusicRepository::release()
{
    if (m_isReady)
    {
        for (auto & it : m_tracks)
        {
            it.second.release();
        }
        m_tracks.clear();
        m_isReady = false;
    }
}

Music & MusicRepository::getMusic(const std::string & id)
{
    auto it = m_tracks.find(id);
    if (it != m_tracks.end())
    {
        return it->second;
    }
    return MusicRepository::kEmptyMusic;
}
} // stren