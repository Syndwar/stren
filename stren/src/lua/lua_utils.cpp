#include "lua_utils.h"

#include "common/point.h"
#include "common/rect.h"

#include "lua/lua_table.h"
#include "lua/lua_value.h"

namespace lua
{
void tableToPoint(const Table & tbl, stren::Point & point)
{
    if (tbl.isValid())
    {
        point.set(tbl.get(1).getInt(), tbl.get(2).getInt());
    }
}

void tableToRect(const Table & tbl, stren::Rect & rect)
{
    if (tbl.isValid())
    {
        rect.set(tbl.get(1).getInt(), tbl.get(2).getInt(), tbl.get(3).getInt(), tbl.get(4).getInt());
    }
}

void tableToPointsVector(const Table & tbl, std::vector<stren::Point> & points)
{
    points.clear();
    if (tbl.isValid())
    {
        points.resize(tbl.getSize());
        for (size_t i = 1, iEnd = points.size(); i <= iEnd; ++i)
        {
            Table pointTbl(tbl.get(i));
            tableToPoint(pointTbl, points[i - 1]);
        }
    }
}

void tableToRectsVector(const Table & tbl, std::vector<stren::Rect> & rects)
{
    rects.clear();
    if (tbl.isValid())
    {
        rects.resize(tbl.getSize());
        for (size_t i = 1, iEnd = rects.size(); i <= iEnd; ++i)
        {
            Table pointTbl(tbl.get(i));
            tableToRect(pointTbl, rects[i - 1]);
        }
    }
}
} // lua