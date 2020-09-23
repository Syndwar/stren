#include "map_editor/map_data.h"

#include "lua/lua_table.h"
#include "lua/lua_value.h"

namespace stren
{
MapData::MapData()
{
    std::vector<std::string> sections = { "Items", "Units", "Objects" };

    for (size_t j = 0, jEnd = sections.size(); j < jEnd; ++j)
    {
        const std::string & sectionId = sections[j];
        lua::Table tbl(sectionId);
        for (size_t i = 1, iEnd = tbl.getSize(); i <= iEnd; ++i)
        {
            lua::Table dataTbl(tbl.get(i));
            const std::string id = dataTbl.get("id").getString();
            const std::string spriteId = dataTbl.get("sprite").getString();
            m_map[id] = m_data.size();
            m_data.push_back(EntityData{ static_cast<EntityData::Type>(j), id, spriteId });
        }
    }
}

const MapData::EntityData & MapData::getEntityData(const std::string & id) const
{
    auto it = m_map.find(id);
    if (it != m_map.end())
    {
        if (it->second < m_data.size())
        {
            return m_data.at(it->second);
        }
    }
    static EntityData emptyData;
    return emptyData;
}

} // stren