#include "listener.h"

#include "lua_wrapper.h"

namespace stren
{

void VmCallback::call(const EventType & type, Widget * sender)
{
    if (!m_callback.empty())
    {
        lua::Function func(m_callback);
        std::vector<lua::Value> values = { static_cast<int>(type), static_cast<void *>(sender) };
        func.call(values);
    }
}

void Listener::addCallback(const EventType & type, const std::string & callback)
{
    m_callbacks[type] = std::make_unique<VmCallback>(callback);
}

void Listener::removeCallback(const EventType & type)
{
    auto it = m_callbacks.find(type);
    if (it != m_callbacks.end())
    {
        m_callbacks[type].reset();
    }
}

void Listener::callBack(const EventType & type, Widget * widget)
{
    if (!m_callbacks.empty())
    {
        auto it = m_callbacks.find(type);
        if (it != m_callbacks.end())
        {
            if (it->second)
            {
                it->second->call(type, widget);
            }
        }
    }
}

void Listener::clear()
{
    m_callbacks.clear();
}

bool Listener::hasCallback(const EventType & type) const
{
    return !m_callbacks.empty() && (m_callbacks.find(type) != m_callbacks.end());
}

} // stren