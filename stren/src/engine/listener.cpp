#include "listener.h"

#include "lua/lua_wrapper.h"

namespace stren
{
void Listener::removeCallback(const Event & event)
{
    auto it = m_callbacks.find(event);
    if (it != m_callbacks.end())
    {
        it->second.reset();
    }
}

void Listener::callBack(const Event & event, Widget * widget)
{
    if (!m_callbacks.empty())
    {
        auto it = m_callbacks.find(event);
        if (it != m_callbacks.end())
        {
            if (it->second)
            {
                it->second->call(widget);
            }
        }
    }
}

void Listener::clear()
{
    m_callbacks.clear();
}

bool Listener::hasCallback(const Event & event) const
{
    return !m_callbacks.empty() && (m_callbacks.find(event) != m_callbacks.end());
}
} // stren