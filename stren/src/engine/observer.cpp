#include "observer.h"

#include "event_listener.h"

namespace stren
{
Observer::Observer()
{
}

Observer::Observer(const std::vector<EventType> & needEvents)
    : m_needEvents(needEvents)
{
}

Observer::~Observer()
{
}

bool Observer::isEventMonitored(const EventType & eventType)
{
    if (m_needEvents.empty()) return true;

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