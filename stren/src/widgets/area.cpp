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

    switch (event.type)
    {
    case EventType::MouseDown:
    case EventType::MouseUp:
    {
        if (getRect().hasCommon(event.pos))
        {
            isEventCaptured = true;
        }
    }
    break;
    case EventType::MouseMove:
    {
        if (getRect().hasCommon(event.pos))
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
    break;
    default:
    break;
    }
}

namespace lua_area
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    const size_t handler = EngineHandler::storeInMemoryController(new Area(id));
    stack.push(handler);
    return 1;
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