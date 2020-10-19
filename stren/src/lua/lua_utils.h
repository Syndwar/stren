#ifndef STREN_LUA_UTILS_H
#define STREN_LUA_UTILS_H

#include <vector>

namespace stren
{
class Point;
class Rect;
} // stren

namespace lua
{
class Table;
///
/// convert lua::Table to the Point
///
void tableToPoint(const Table & tbl, stren::Point & point);
///
/// convert lua::Table to the vector with Points
///
void tableToPointsVector(const Table & tbl, std::vector<stren::Point> & points);
///
/// convert lua::Table to the rect
///
void tableToRect(const Table & tbl, stren::Rect & rect);
///
/// convert lua::Table to the vector with Rects
///
void tableToRectsVector(const Table & tbl, std::vector<stren::Rect> & rects);
} // lua
#endif // STREN_LUA_WRAPPER_H