#include "screen.h"

#include "engine/engine_handler.h"
#include "lua/lua_wrapper.h"

namespace stren
{
Screen::Screen(const std::string & id)
    : Container(id)
{
    setState(ViewState::Closed);
    setParent(this);
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
    const size_t handler = EngineHandler::storeInMemoryController(new Screen(id));
    stack.push(handler);
    return 1;
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