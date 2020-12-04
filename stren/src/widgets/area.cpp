#include "area.h"

#include "engine/engine_handler.h"
#include "lua/lua_wrapper.h"

namespace stren
{
Area::Area(const std::string & id)
    : Widget(id)
    , m_mouseState(MouseState::Outside)
{
}

Area::~Area()
{
}

void Area::processEvent(const Event & event, bool & isEventCaptured)
{
    if (isEventCaptured) return;
    if (EventType::MouseMove != event.type) return;
     
    const bool hasMouse = isOpened() && getRect().hasCommon(event.pos);
    if (hasMouse)
    {
        if (MouseState::Outside == m_mouseState)
        {
            m_mouseState = MouseState::Over;
            callBack(EventType::MouseOver, this);
        }
        isEventCaptured = true;
    }
    else if (MouseState::Over == m_mouseState)
    {
        m_mouseState = MouseState::Outside;
        callBack(EventType::MouseLeft, this);
    }
}

namespace lua_area
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Area * area = new Area(id);
    EngineHandler::storeInMemoryController(area);
    stack.clear();
    stack.push((void *)area);
    return stack.getSize();
}
} // lua_area

void Area::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_area::create },
        { NULL, NULL }
    };
    stack.loadLibs("Area", functions);
}

} // stren