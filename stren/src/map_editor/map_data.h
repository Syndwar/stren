#ifndef STREN_MAP_DATA_H
#define STREN_MAP_DATA_H

#include <map>
#include <vector>
#include "string_ext.h"

namespace stren
{
///
/// class MapData
///
class MapData
{
public:
    struct EntityData
    {
        enum class Type
        {
            Item = 0,
            Unit,
            Object
        };

        Type type;
        std::string id;
        std::string sprite;
    };
private:
    std::map<std::string, size_t> m_map;
    std::vector<EntityData> m_data;
public:
    ///
    /// Constructor
    ///
    MapData();
    ///
    /// @todo
    ///
    const EntityData & getEntityData(const std::string & id) const;
    ///
    /// @todo
    ///
    const std::vector<EntityData> & getFullData() const
    {
        return m_data;
    }

};
} // stren

#endif // !STREN_MAP_DATA_H
