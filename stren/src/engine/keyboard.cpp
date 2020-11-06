#include "engine/keyboard.h"

#include "lua/lua_wrapper.h"

namespace stren
{
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
        switch (event.type)
        {
        case EventType::KeyDown:
        case EventType::KeyUp:
        {
            for (auto & ka : m_actions)
            {
                if (!ka.isEmpty() && event.key == ka.key || ka.key.empty())
                {
                    if (ka.eventType == event.type)
                    {
                        if (ka.action->exec(event))
                        {
                            isEventCaptured = true;
                            break;
                        }
                    }
                }
            }
        }
        break;
        }
    }
}

size_t Keyboard::addAction(const EventType eventType, const std::string & key, IAction * action)
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
    if (!isEventCaptured)
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
                    if (ka.eventType == event.type)
                    {
                        if (ka.action->exec(event))
                        {
                            isEventCaptured = true;
                            break;
                        }
                    }
                }
            }
        }
        break;
        };
    }
}

size_t Mouse::addAction(const EventType eventType, const Event::MouseButton button, IAction * action)
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

} // stren