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
    else if ("MouseOver" == type)       return EventType::MouseOver;
    else if ("MouseLeft" == type)       return EventType::MouseLeft;
    else if ("KeyUp_W" == type)         return EventType::KeyUp_W;
    else if ("KeyDown_W" == type)       return EventType::KeyDown_W;
    else if ("KeyUp_A" == type)         return EventType::KeyUp_A;
    else if ("KeyDown_A" == type)       return EventType::KeyDown_A;
    else if ("KeyUp_D" == type)         return EventType::KeyUp_D;
    else if ("KeyDown_D" == type)       return EventType::KeyDown_D;
    else if ("KeyUp_S" == type)         return EventType::KeyUp_S;
    else if ("KeyDown_S" == type)       return EventType::KeyDown_S;
    else if ("KeyUp_Grave" == type)     return EventType::KeyUp_Grave;
    else if ("KeyDown_Grave" == type)   return EventType::KeyDown_Grave;
    else if ("KeyUp_F1" == type)        return EventType::KeyUp_F1;
    else if ("KeyDown_F1" == type)      return EventType::KeyDown_F1;
    else if ("KeyUp_F2" == type)        return EventType::KeyUp_F2;
    else if ("KeyDown_F2" == type)      return EventType::KeyDown_F2;
    else if ("KeyUp_F3" == type)        return EventType::KeyUp_F3;
    else if ("KeyDown_F3" == type)      return EventType::KeyDown_F3;
    return EventType::Unknown;
}

EventType Event::getType() const
{
    switch (type)
    {
    case EventType::KeyDown:
    {
        if ("W" == key) { return EventType::KeyDown_W; }
        if ("A" == key) { return EventType::KeyDown_A; }
        if ("D" == key) { return EventType::KeyDown_D; }
        if ("S" == key) { return EventType::KeyDown_S; }
        if ("`" == key) { return EventType::KeyDown_Grave; }
        if ("F1" == key) { return EventType::KeyDown_F1; }
        if ("F2" == key) { return EventType::KeyDown_F2; }
        if ("F3" == key) { return EventType::KeyDown_F3; }
    }
    break;
    case EventType::KeyUp:
    {
        if ("W" == key) { return EventType::KeyUp_W; }
        if ("A" == key) { return EventType::KeyUp_A; }
        if ("D" == key) { return EventType::KeyUp_D; }
        if ("S" == key) { return EventType::KeyUp_S; }
        if ("`" == key) { return EventType::KeyUp_Grave; }
        if ("F1" == key) { return EventType::KeyUp_F1; }
        if ("F2" == key) { return EventType::KeyUp_F2; }
        if ("F3" == key) { return EventType::KeyUp_F3; }
    }
    break;
    case EventType::MouseDown:
    {
        return EventType::MouseDown;
    }
    break;
    case EventType::MouseUp:
    {
        return EventType::MouseUp;
    }
    break;
    }
    return type;
}

} // stren