#include "sounds_repository.h"

#include "lua/lua_wrapper.h"

namespace stren
{
Sound SoundsRepository::kEmptySound;

SoundsRepository::SoundsRepository()
    : m_isReady(false)
{
}

void SoundsRepository::initialize(const lua::Table & tbl)
{
    if (!m_isReady)
    {
        for (size_t i = 1, iEnd = tbl.getSize(); i <= iEnd; ++i)
        {
            lua::Table soundTable(tbl.get(i));
            const std::string id = soundTable.get("id").getString();
            const std::string filename = soundTable.get("filename").getString();
            m_sounds[id] = Sound(id, filename);
        }
        m_isReady = true;
    }
}

Sound & SoundsRepository::getSound(const std::string & id)
{
    auto it = m_sounds.find(id);
    if (it != m_sounds.end())
    {
        return it->second;
    }
    return SoundsRepository::kEmptySound;
}

void SoundsRepository::release()
{
    if (m_isReady)
    {
        for (auto & it : m_sounds)
        {
            it.second.release();
        }
        m_sounds.clear();
        m_isReady = false;
    }
}
} // stren