#include "mouse.h"

#include "engine/action.h"

namespace stren
{
///
/// class MouseAction
///
MouseAction::MouseAction()
    : eventType(EventType::None)
{
}

MouseAction::MouseAction(const int et, const Event::MouseButton b, IAction * a)
    : eventType(et)
    , button(b)
    , action(a)
{
}

void MouseAction::reset()
{
    action.reset();
    button = Event::MouseButton::None;
    eventType = EventType::None;
}

void MouseAction::reset(const int et, const Event::MouseButton b, IAction * a)
{
    action.reset(a);
    button = b;
    eventType = et;
}

bool MouseAction::isEmpty() const
{
    return EventType::None == eventType && Event::MouseButton::None == button && action;
}
///
/// class Mouse
///
Mouse::Mouse()
{
}

void Mouse::update(const size_t dt)
{
}

void Mouse::processEvent(const Event & event, bool & isEventCaptured)
{
    switch (event.type)
    {
    case EventType::MouseUp:
    case EventType::MouseDown:
    case EventType::MouseMove:
    case EventType::MouseWheel:
    {
        for (auto & ka : m_actions)
        {
            if (!ka.isEmpty() && event.mouseButton == ka.button || Event::MouseButton::None == ka.button)
            {
                if (ka.eventType & event.type)
                {
                    if (ka.action->exec(event, isEventCaptured))
                    {
                        if (!isEventCaptured)
                        {
                            isEventCaptured = true;
                        }
                    }
                }
            }
        }
    }
    break;
    };
}

size_t Mouse::addAction(const int eventType, const Event::MouseButton button, IAction * action)
{
    const size_t iEnd = m_actions.size();
    for (size_t i = 0; i < iEnd; ++i)
    {
        if (m_actions[i].isEmpty())
        {
            m_actions[i].reset(eventType, button, action);
            return i;
        }
    }
    m_actions.resize(iEnd + 1);
    m_actions[iEnd].reset(eventType, button, action);

    return iEnd;
}

void Mouse::removeAction(const size_t key)
{
    if (key < (int)m_actions.size())
    {
        if (!m_actions[key].isEmpty())
        {
            m_actions[key].reset();
        }
    }
}
} //stren