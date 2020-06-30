#include "observer.h"

#include "event_listener.h"

namespace stren
{
Observer::Observer(EventListener * listener)
    : m_listener(listener)
{
    if (m_listener)
    {
        m_listener->add(this);
    }
}

Observer::Observer(EventListener * listener, const std::vector<EventType> & needEvents)
    : m_listener(listener)
    , m_needEvents(needEvents)
{
    if (m_listener)
    {
        m_listener->add(this);
    }
}

Observer::Observer(const Observer & observer)
    : m_listener(observer.m_listener)
    , m_needEvents(observer.m_needEvents)
{
    if (m_listener)
    {
        m_listener->add(this);
    }
}

Observer::Observer(Observer && observer)
    : m_listener(observer.m_listener)
    , m_needEvents(std::move(observer.m_needEvents))
{
    if (m_listener)
    {
        m_listener->remove(&observer);
        observer.m_listener = nullptr;

        m_listener->add(this);
    }
}

Observer::~Observer()
{
    if (m_listener)
    {
        m_listener->remove(this);
    }
}

Observer & Observer::operator=(const Observer & observer)
{
    m_listener = observer.m_listener;
    m_needEvents = observer.m_needEvents;
    if (m_listener)
    {
        m_listener->add(this);
    }
    return *this;
}

Observer & Observer::operator=(Observer && observer)
{
    m_listener = observer.m_listener;
    m_needEvents = std::move(observer.m_needEvents);

    if (m_listener)
    {
        m_listener->remove(&observer);
        observer.m_listener = nullptr;

        m_listener->add(this);
    }
    return *this;
}

bool Observer::isEventMonitored(const EventType & eventType)
{
    for (const EventType type : m_needEvents)
    {
        if (type == eventType)
        {
            return true;
        }
    }
    return false;
}
} // stren