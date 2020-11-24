#include "event_listener.h"

#include "event.h"
#include "observer.h"

namespace stren
{
///
/// class IListener
///
void IListener::add(Observer * observer)
{
    if (observer)
    {
        for (size_t i = 0, iEnd = m_observers.size(); i < iEnd; ++i)
        {
            if (!m_observers[i])
            {
                m_observers[i] = observer;
                return;
            }
        }

        m_observers.push_back(observer);
    }
}

void IListener::remove(Observer * observer)
{
    if (observer)
    {
        for (size_t i = 0, iEnd = m_observers.size(); i < iEnd; ++i)
        {
            if (m_observers[i] == observer)
            {
                m_observers[i] = nullptr;
                break;
            }
        }
    }
}
///
/// class EventListener
///
void EventListener::notify(const Event & event, bool & isEventCaptured)
{
    if (m_observers.empty()) return;

    for (size_t i = m_observers.size(); i > 0; --i)
    {
        Observer * observer = m_observers[i - 1];
        if (observer && observer->isEventMonitored(event.type))
        {
            observer->notify(event, isEventCaptured);
        }
    }
}
///
/// class UpdateEventListener
///
void UpdateEventListener::update(const size_t dt)
{
    if (m_observers.empty()) return;

    for (size_t i = m_observers.size(); i > 0; --i)
    {
        Observer * observer = m_observers[i - 1];
        if (observer)
        {
            observer->notify(dt);
        }
    }
}
///
/// class RenderEventListener
///
void RenderEventListener::render()
{
    if (m_observers.empty()) return;

    for (size_t i = m_observers.size(); i > 0; --i)
    {
        Observer * observer = m_observers[i - 1];
        if (observer)
        {
            observer->notify();
        }
    }
}
} // stren