#include "texts_repository.h"

#include "lua/lua_wrapper.h"

namespace stren
{
TextsRepository::TextsRepository()
    : m_isReady(false)
{
}

bool TextsRepository::initialize()
{
    if (!m_isReady)
    {
        lua::Table tbl("Texts");
        for (size_t i = 1, iEnd = tbl.getSize(); i <= iEnd; ++i)
        {
            lua::Table textTable(tbl.get(i));
            const std::string id = textTable.get("id").getString();
            m_texts[id] = textTable.get("text").getString();
        }
        m_isReady = true;
    }
    return m_isReady;
}

const std::string & TextsRepository::getText(const std::string & alias) const
{
    auto it = m_texts.find(alias);
    if (it != m_texts.end())
    {
        return it->second;
    }
    return String::kEmpty;
}

void TextsRepository::release()
{
    if (m_isReady)
    {
        m_texts.clear();
        m_isReady = false;
    }
}
} // stren