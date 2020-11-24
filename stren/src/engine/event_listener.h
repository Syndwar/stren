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
class IListener
{
protected:
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
};
///
/// class EventListener
///
class EventListener : public IListener
{
public:
    ///
    /// notify observers
    ///
    void notify(const Event & event, bool & isEventCaptured);
};

///
/// class UpdateEventListener
///
class UpdateEventListener : public IListener
{
public:
    ///
    /// @todo
    ///
    void update(const size_t dt);
};

///
/// class RenderEventListener
///
class RenderEventListener : public IListener
{
public:
    ///
    /// @todo
    ///
    void render();
};

} // stren

#endif // STREN_EVENT_LISTENER_H
