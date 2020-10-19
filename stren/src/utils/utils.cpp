#include "utils.h"

#include "point.h"
#include "rect.h"
#include "lua_wrapper.h"
#include "logger.h"

namespace stren
{
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