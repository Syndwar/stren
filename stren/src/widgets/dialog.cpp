#include "dialog.h"

#include "lua_wrapper.h"

namespace stren
{
Dialog::Dialog(const std::string & id /* = String::kEmpty */)
    : Container(id)
{
    setState(ViewState::Closed);
}

Dialog::~Dialog()
{
}

namespace lua_dialog
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Dialog * dlg = new Dialog(id);
    stack.clear();
    stack.push((void *)dlg);
    return stack.getSize();
}
} // lua_screen

void Dialog::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_dialog::create },
        { NULL, NULL }
    };
    stack.loadLibs("Dialog", functions);
}
} // stren