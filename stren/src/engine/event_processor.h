#ifndef EVENT_PROCESSOR_H
#define EVENT_PROCESSOR_H

#include "common/point.h"
#include "engine/event.h"

union SDL_Event;

namespace stren
{
///
/// class EventProcessor
///
class EventProcessor
{
private:
    Point m_mousPos;    ///< stores mouse position
    Event m_event;      ///< stores latest event
public:
    ///
    /// Constructor
    ///
    EventProcessor();
    ///
    /// returns latest event
    ///
    const Event & getEvent();
    ///
    /// get mouse position
    ///
    const Point & getMousePos();
};

} // stren

#endif // EVENT_PROCESSOR_H
