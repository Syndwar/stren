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

namespace lua_screen
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Screen * screen = new Screen(id);
    stack.clear();
    stack.push((void *)screen);
    return stack.getSize();
}
} // lua_screen

void Screen::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_screen::create },
        { NULL, NULL }
    };
    stack.loadLibs("Screen", functions);
}
} // stren