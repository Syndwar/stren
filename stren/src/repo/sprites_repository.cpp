#include "sprites_repository.h"

#include "lua/lua_wrapper.h"
#include "utils/utils.h"

namespace stren
{

SpritesRepository::SpritesRepository()
    : m_isReady(false)
{
}

bool SpritesRepository::initialize()
{
    if (!m_isReady)
    {
        m_sprites.clear();
        lua::Table tbl("Sprites");
        for (size_t i = 1, i_end = tbl.getSize(); i <= i_end; ++i)
        {
            lua::Table spriteTbl(tbl.get(i));
            const std::string textureId = spriteTbl.get("texture").getString();
            const std::string id = spriteTbl.get("id").getString();
            const std::string colour = spriteTbl.get("colour").getString();

            const lua::Table rectTable(spriteTbl.get("rect"));
            if (rectTable.isValid())
            {
                Rect rect;
                if (4 == rectTable.getSize())
                {
                    lua::tableToRect(rectTable, rect);
                }
                m_sprites[id] = Sprite(textureId, rect, colour);
            }
        }
        m_isReady = true;
    }

    return m_isReady;
}

Sprite * SpritesRepository::getSprite(const std::string & spriteId)
{
    auto it = m_sprites.find(spriteId);
    if (m_sprites.end() != it)
    {
        return &it->second;
    }
    return nullptr;
}

void SpritesRepository::release()
{
    if (m_isReady)
    {
        m_sprites.clear();
        m_isReady = false;
    }
}

} // stren