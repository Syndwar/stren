#include "event.h"

namespace stren
{
Event::Event()
    : type(EventType::None)
    , mouseButton(MouseButton::None)
    , mod(KeyMod::None)
{
}

Event::Event(EventType type)
    : type(type)
    , mouseButton(MouseButton::None)
    , mod(KeyMod::None)
{
}

void Event::clear()
{
    type = EventType::None;
    mod = KeyMod::None;
    mouseButton = MouseButton::None;
    pos.set(0, 0);
}

EventType Event::strToType(const std::string & type)
{
    if ("KeyUp" == type)                return EventType::KeyUp;
    else if ("KeyDown" == type)         return EventType::KeyDown;
    else if ("MouseUp" == type)         return EventType::MouseUp;
    else if ("MouseDown" == type)       return EventType::MouseDown;
    else if ("MouseMove" == type)       return EventType::MouseMove;
    else if ("MouseWheel" == type)      return EventType::MouseWheel;
    else if ("MouseClicked" == type)    return EventType::MouseClicked;
    else if ("WidgetOpened" == type)    return EventType::WidgetOpened;
    else if ("WidgetClosed" == type)    return EventType::WidgetClosed;
    else if ("WidgetDelete" == type)    return EventType::WidgetDelete;
    else if ("WidgetOpening" == type)   return EventType::WidgetOpening;
    else if ("WidgetClosing" == type)   return EventType::WidgetClosing;
    else if ("TimerElapsed" == type)    return EventType::TimerElapsed;
    else if ("SysQuit" == type)         return EventType::SysQuit;
    return EventType::Unknown;
}


} // stren