#ifndef STREN_EVENT_LISTENER_H
#define STREN_EVENT_LISTENER_H

#include <vector>

namespace stren
{

class Event;
class Observer;
///
/// class EventListener
///
class EventListener
{
private:
    std::vector<Observer *> m_observers; ///< @todo
public:
    ///
    /// add observer
    ///
    void add(Observer * observer);
    ///
    /// remove observer
    ///
    void remove(Observer * observer);
    ///
    /// notify observers
    ///
    void notify(Event & event);
};

} // stren

#endif // STREN_EVENT_LISTENER_H
