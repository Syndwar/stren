#ifndef STREN_OBSERVER_H
#define STREN_OBSERVER_H

#include <vector>

namespace stren
{
class Event;
enum EventType;
class EventListener;
///
/// class Observer
///
class Observer
{
private:
    EventListener *         m_listener;            ///< @todo
    std::vector<EventType>  m_needEvents;          ///< @todo
public:
    ///
    /// Default Constructor is forbidden
    ///
    Observer() = delete;
    ///
    /// Constructor
    ///
    Observer(EventListener * listener);
    ///
    /// Constructor
    ///
    Observer(EventListener * listener, const std::vector<EventType> & needEvents);
    ///
    /// Copy Constructor
    ///
    Observer(const Observer & observer);
    ///
    /// Move Constructor
    ///
    Observer(Observer && observer);
    ///
    /// Destructor
    ///
    virtual ~Observer();
    ///
    /// Copy assign operator
    ///
    Observer & operator=(const Observer & observer);
    ///
    /// Move assign operator
    ///
    Observer & operator=(Observer && observer);
    ///
    /// notify child class
    ///
    virtual bool notify(const Event & event) = 0;
    ///
    /// returns if given event type is registered for this observer
    ///
    bool isEventMonitored(const EventType & eventType);
};

} // stren

#endif // STREN_OBSERVER_H
