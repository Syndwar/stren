#include "event_listener.h"

#include "event.h"
#include "observer.h"

namespace stren
{
void EventListener::add(Observer * observer)
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

void EventListener::remove(Observer * observer)
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

void EventListener::notify(Event & event)
{
    for (int i = m_observers.size() - 1; i >= 0; --i)
    {
        Observer * observer = m_observers[i];
        if (observer && observer->isEventMonitored(event.type))
        {
            observer->notify(event);
        }
    }
}
} // stren