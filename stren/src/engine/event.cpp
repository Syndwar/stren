#include "event.h"

namespace stren
{
std::vector<std::string> Event::kEventTypes = {
    "None",
    "Unknown",
    "KeyUp",
    "KeyDown",
    "MouseUp",
    "MouseDown",
    "MouseMove",
    "MouseWheel",
    "MouseClicked",
    "WidgetOpened",
    "WidgetClosed",
    "WidgetDelete",
    "WidgetOpening",
    "WidgetClosing",
    "TimerElapsed",
    "SysQuit",
};

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

} // stren