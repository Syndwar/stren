#include "fonts_repository.h"

#include "SDL_ttf.h"

#include "lua_wrapper.h"
#include "logger.h"
namespace stren {

FontsRepository::FontsRepository()
    : m_isReady(false)
{
}

bool FontsRepository::initialize()
{
    if (!m_isReady)
    {
        m_fonts.clear();
        lua::Table tbl("Fonts");
        Logger("green") << "[Engine] Initialize SDL TTF fonts";
        if (-1 == TTF_Init()) return false;

        Logger("green") << "[Engine] Create fonts repository";

        for (size_t i = 1, i_end = tbl.getSize(); i <= i_end; ++i)
        {
            lua::Table font_tbl(tbl.get(i));
            const std::string id = font_tbl.get("id").getString();
            const std::string filename = font_tbl.get("file").getString();
            const int size = font_tbl.get("size").getInt();
            const std::string glyphs = font_tbl.get("glyphs").getString();

            m_fonts[id] = FontTexture(filename, size, glyphs);
        }

        Logger("green") << "[Engine] Clear SDL TTF fonts";
        TTF_Quit();
        m_isReady = true;
    }
    return m_isReady;
}

void FontsRepository::release()
{
    if (m_isReady)
    {
        m_fonts.clear();
        m_isReady = false;
    }
}

ITexture * FontsRepository::getTexture(const std::string & fontId)
{
    auto it = m_fonts.find(fontId);
    if (it != m_fonts.end())
    {
        return &it->second;
    }
    return nullptr;
}

} // stren