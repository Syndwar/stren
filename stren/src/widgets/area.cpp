#include "area.h"

#include "action.h"
#include "lua_wrapper.h"

namespace stren
{
Area::Area(const std::string & id)
    : Widget(id)
    , m_actionEvent(EventType::None)
    , m_mouseState(MouseState::Outside)
{
}

Area::~Area()
{
}

void Area::processEvent(const Event & event, bool & isEventCaptured)
{
    const bool hasMouse = !isEventCaptured && getRect().hasCommon(event.pos);
    if (event.type == m_actionEvent)
    {
        if (hasMouse)
        {
            if (MouseState::Outside == m_mouseState)
            {
                callAction(true);
                m_mouseState = MouseState::Over;
            }
            isEventCaptured = true;
        }
        else
        {
            if (MouseState::Over == m_mouseState)
            {
                callAction(false);
                m_mouseState = MouseState::Outside;
            }
        }
    }
}

void Area::setAction(EventType eventType, IAction * action)
{
    m_action.reset(action);
    m_actionEvent = eventType;
}

void Area::callAction(const bool isEnabled)
{
    if (m_action)
    {
        if (isEnabled)
        {
            m_action->exec();
        }
        else
        {
            m_action->cancel();
        }
    }
}

namespace lua_area
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Area * area = new Area(id);
    stack.clear();
    stack.push((void *)area);
    return stack.getSize();
}

int setAction(lua_State * L)
{
    lua::Stack stack(3);
    Area * area = (Area *)stack.get(1).getUserData();
    if (area)
    {
        const std::string eventId = stack.get(2).getString();
        IAction * action = (IAction *)stack.get(3).getUserData();
        area->setAction(Event::strToType(eventId), action);
    }
    stack.clear();
    return 0;
}
} // lua_area

void Area::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_area::create },
        { "setAction", lua_area::setAction },
        { NULL, NULL }
    };
    stack.loadLibs("Area", functions);
}

} // stren