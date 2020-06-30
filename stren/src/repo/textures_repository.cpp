#include "textures_repository.h"

#include "SDL.h"

#include "lua_wrapper.h"
#include "texture.h"

namespace stren
{
TexturesRepository::TexturesRepository()
    : m_isReady(false)
{
}

bool TexturesRepository::initialize()
{
    if (!m_isReady)
    {
        lua::Table tbl("Textures");
        for (size_t i = 1, i_end = tbl.getSize(); i <= i_end; ++i)
        {
            lua::Table textureTbl(tbl.get(i));
            const std::string id = textureTbl.get("id").getString();
            const std::string filePath = textureTbl.get("file").getString();
            const bool isAlphaBlend = textureTbl.get("alphaBlending").getBool();
            m_textures[id] = ImageTexture(filePath, isAlphaBlend);
        }
        m_isReady = true;
    }
    return m_isReady;
}

void TexturesRepository::release()
{
    if (m_isReady)
    {
        m_textures.clear();
        m_isReady = false;
    }
}

ITexture * TexturesRepository::getTexture(const std::string & textureId)
{
    auto it = m_textures.find(textureId);
    if (it != m_textures.end())
    {
        return &it->second;
    }
    return nullptr;
}

} // stren