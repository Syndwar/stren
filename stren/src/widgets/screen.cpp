#include "screen.h"

#include "lua_stack.h"
#include "lua_value.h"

namespace stren
{
Screen::Screen(const std::string & id)
    : Container(id)
{
    setState(ViewState::Closed);
}

Screen::~Screen()
{
}


int createScreen(lua_State * L)
{
    lua::Stack stack(1);
    const std::string id = stack.get(1).getString();
    Screen * screen = new Screen(id);
    stack.clear();
    stack.push((void *)screen);
    return stack.getSize();
}

void Screen::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", createScreen },
        { NULL, NULL }
    };
    stack.loadLibs("Screen", functions);
}
} // stren