#include "engine/keyboard.h"

#include "engine/action.h"
#include "engine/event.h"
#include "lua/lua_wrapper.h"

namespace stren
{
///
/// class KeyboardAction
///
struct KeyboardAction
{
    EventType                   eventType;
    std::string                 key;
    IAction *                   action;
    ///
    /// Constructor
    ///
    KeyboardAction(const EventType et, const std::string & k, IAction * a)
        : eventType(et)
        , key(k)
        , action(a)
    {
    }
    ///
    /// Destructor
    ///
    ~KeyboardAction()
    {
        if (action)
        {
            delete action;
            action = nullptr;
        }
    }
};
///
/// class Keyboard
///
Keyboard::Keyboard()
{
}

void Keyboard::update(const size_t dt)
{
}

void Keyboard::processEvent(const Event & event, bool & isEventCaptured)
{
    if (!isEventCaptured)
    {
        for (KeyboardAction * ka : m_actions)
        {
            if (ka &&  EventType::KeyPressed == ka->eventType && event.key == ka->key)
            {
                if (EventType::KeyDown == event.type)
                {
                    ka->action->exec();
                    isEventCaptured = true;
                    break;
                }
                else if (EventType::KeyUp == event.type)
                {
                    ka->action->cancel();
                    isEventCaptured = true;
                    break;
                }
            }
        }
    }
}

size_t Keyboard::addAction(const EventType eventType, const std::string & key, IAction * action)
{
    KeyboardAction * keyAction = new KeyboardAction(eventType, key, action);
    const size_t iEnd = m_actions.size();
    for (size_t i = 0; i < iEnd; ++i)
    {
        if (!m_actions[i])
        {
            m_actions[i] = keyAction;
            return i;
        }
    }
    m_actions.push_back(keyAction);

    return iEnd;
}

void Keyboard::removeAction(const size_t key)
{
    if (key < (int)m_actions.size())
    {
        if (m_actions[key])
        {
            delete m_actions[key];
            m_actions[key] = nullptr;
        }
    }
}
} // stren