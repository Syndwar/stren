#include "utils.h"

#include "point.h"
#include "rect.h"
#include "lua_wrapper.h"
#include "logger.h"

namespace stren
{
void tableToPoint(const lua::Table & tbl, Point & point)
{
    if (tbl.isValid())
    {
        point.set(tbl.get(1).getInt(), tbl.get(2).getInt());
    }
}

void tableToRect(const lua::Table & tbl, Rect & rect)
{
    if (tbl.isValid())
    {
        rect.set(tbl.get(1).getInt(), tbl.get(2).getInt(), tbl.get(3).getInt(), tbl.get(4).getInt());
    }
}

void tableToPointsVector(const lua::Table & tbl, std::vector<Point> & points)
{
    points.clear();
    if (tbl.isValid())
    {
        points.resize(tbl.getSize());
        for (size_t i = 1, iEnd = points.size(); i <= iEnd; ++i)
        {
            lua::Table pointTbl(tbl.get(i));
            tableToPoint(pointTbl, points[i - 1]);
        }
    }
}

void tableToRectsVector(const lua::Table & tbl, std::vector<Rect> & rects)
{
    rects.clear();
    if (tbl.isValid())
    {
        rects.resize(tbl.getSize());
        for (size_t i = 1, iEnd = rects.size(); i <= iEnd; ++i)
        {
            lua::Table pointTbl(tbl.get(i));
            tableToRect(pointTbl, rects[i - 1]);
        }
    }
}

void tokenize(const char * input, std::vector<std::string>& output, const char * splitSymbol)
{
    enum { BufferSize = 512 };

    output.clear();

    char buffer[BufferSize] = { 0 };
    strncpy_s(buffer, input, BufferSize);
    char * context = nullptr;
    const char * fieldName = strtok_s(buffer, splitSymbol, &context);
    while (fieldName)
    {
        output.push_back(fieldName);
        fieldName = strtok_s(nullptr, splitSymbol, &context);
    }
}

void assertFullMessage(const char * expr_str, bool expr, const char * file, int line, const char * msg)
{
    if (!expr)
    {
        char buffer[1024];
        sprintf_s(buffer, "Assert failed: %s; \n Expected: %s; \n Source: %s, line %d\n", msg, expr_str, file, line);
        stren::Logger("red") << "[Crash]: " << buffer;

        throw std::exception(buffer);
    }
}
} // stren