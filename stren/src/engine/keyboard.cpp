#include "engine/keyboard.h"

#include "engine/action.h"

namespace stren
{
///
/// class KeyboardAction
///
KeyboardAction::KeyboardAction()
    : eventType(EventType::None)
{
}

KeyboardAction::KeyboardAction(const int et, const std::string & k, IAction * a)
    : eventType(et)
    , key(k)
    , action(a)
{
}

void KeyboardAction::reset()
{
    action.reset();
    key.clear();
    eventType = EventType::None;
}

void KeyboardAction::reset(const int et, const std::string & k, IAction * a)
{
    action.reset(a);
    key = k;
    eventType = et;
}

bool KeyboardAction::isEmpty() const
{
    return EventType::None == eventType && key.empty() && action;
}

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
    switch (event.type)
    {
    case EventType::KeyDown:
    case EventType::KeyUp:
    {
        for (auto & ka : m_actions)
        {
            if (!ka.isEmpty() && event.key == ka.key || ka.key.empty())
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
    }
}

size_t Keyboard::addAction(const int eventType, const std::string & key, IAction * action)
{
    const size_t iEnd = m_actions.size();
    for (size_t i = 0; i < iEnd; ++i)
    {
        if (m_actions[i].isEmpty())
        {
            m_actions[i].reset(eventType, key, action);
            return i;
        }
    }
    m_actions.resize(iEnd + 1);
    m_actions[iEnd].reset(eventType, key, action);

    return iEnd;
}

void Keyboard::removeAction(const size_t key)
{
    if (key < (int)m_actions.size())
    {
        if (!m_actions[key].isEmpty())
        {
            m_actions[key].reset();
        }
    }
}

} // stren