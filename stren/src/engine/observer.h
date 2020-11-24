#ifndef STREN_OBSERVER_H
#define STREN_OBSERVER_H

#include <vector>

namespace stren
{
class Event;
enum class EventType;
///
/// class Observer
///
class Observer
{
private:
    std::vector<EventType>  m_needEvents;          ///< @todo
public:
    ///
    /// Constructor
    ///
    Observer();
    ///
    /// Constructor
    ///
    Observer(const std::vector<EventType> & needEvents);
    ///
    /// Destructor
    ///
    virtual ~Observer();
    ///
    /// notify child class
    ///
    virtual void notify() = 0;
    ///
    /// notify child class
    ///
    virtual void notify(const Event & event, bool & isEventCaptured) = 0;
    ///
    /// notify child class
    ///
    virtual void notify(const size_t dt) = 0;
    ///
    /// returns if given event type is registered for this observer
    ///
    bool isEventMonitored(const EventType & eventType);
};

} // stren

#endif // STREN_OBSERVER_H
