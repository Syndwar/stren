#include "area.h"

#include "engine/action.h"
#include "engine/engine_handler.h"
#include "lua/lua_wrapper.h"

namespace stren
{
///
/// class AreaAction
///
class AreaAction : public IAction
{
private:
    Area *  m_container;     ///< container who created the action
public:
    ///
    /// Constructor
    ///
    AreaAction(Area * container)
        : IAction()
        , m_container(container)
    {
    }
    ///
    /// Destructor
    ///
    virtual ~AreaAction() {}
    ///
    /// Start action
    ///
    virtual bool exec() override
    {
        return false;
    }
    ///
    /// Start action
    ///
    virtual bool exec(const Event & event) override
    {
        if (m_container)
        {
            const bool hasMouse = m_container->getRect().hasCommon(event.pos);
            if (hasMouse)
            {
                //if (event.type == m_actionEvent)
                //{
                //    if (hasMouse)
                //    {
                //        if (MouseState::Outside == m_mouseState)
                //        {
                //            if (m_action)
                //            {
                //                m_action->exec(event);
                //            }
                //            m_mouseState = MouseState::Over;
                //        }
                //        isEventCaptured = true;
                //    }
                //    else
                //    {
                //        if (MouseState::Over == m_mouseState)
                //        {
                //            if (m_action)
                //            {
                //                //m_action->cancel(event);
                //            }
                //            m_mouseState = MouseState::Outside;
                //        }
                //    }
                //}
                return true;
            }
        }
        return false;
    }
};
///
/// class Area
///
Area::Area(const std::string & id)
    : Widget(id)
    , m_actionEvent(EventType::None)
    , m_mouseState(MouseState::Outside)
    , m_actionKey(0)
{
    IAction * action = createAction();
    m_actionKey = EngineHandler::addMouseAction(EventType::MouseMove, Event::MouseButton::None, action);
}

Area::~Area()
{
    EngineHandler::removeKeyboardAction(m_actionKey);
}

void Area::setAction(EventType eventType, IAction * action)
{
    m_action.reset(action);
    m_actionEvent = eventType;
}

IAction * Area::createAction()
{
    IAction * action = new AreaAction(this);
    return action;
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