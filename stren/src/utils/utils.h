#ifndef STREN_UTILS_H
#define STREN_UTILS_H

#include <vector>
#include "string_ext.h"

namespace lua 
{
class Table;
} // lua

namespace stren
{
class Point;
class Rect;
///
/// convert lua::Table to the Point
///
void tableToPoint(const lua::Table & tbl, Point & point);
///
/// convert lua::Table to the vector with Points
///
void tableToPointsVector(const lua::Table & tbl, std::vector<Point> & points);
///
/// convert lua::Table to the rect
///
void tableToRect(const lua::Table & tbl, Rect & rect);
///
/// convert lua::Table to the vector with Rects
///
void tableToRectsVector(const lua::Table & tbl, std::vector<Rect> & rects);
///
/// Splits "input" char string into pieces using "split_symbol" as an anchor.
/// Puts resulting parts into "output" vector.
///
void tokenize(const char * input, std::vector<std::string> & output, const char * splitSymbol);
///
/// Stops application if "value" is false and shows "msg" string.
///
#define assertMessage(Expr, Msg) assertFullMessage(#Expr, Expr, __FILE__, __LINE__, Msg)

void assertFullMessage(const char * expr_str, bool expr, const char * file, int line, const char * msg);
} // stren

#endif // STREN_UTILS_H
