#ifndef STREN_UTILS_H
#define STREN_UTILS_H

#include <vector>
#include "common/string_ext.h"

namespace stren
{
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
