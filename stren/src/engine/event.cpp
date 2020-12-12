#include "event.h"

#include "utils/utils.h"

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

Event::Event(const std::string & typeStr)
    : type(EventType::None)
    , mouseButton(MouseButton::None)
    , mod(KeyMod::None)
{
    parse(typeStr);
}

void Event::clear()
{
    type = EventType::None;
    mod = KeyMod::None;
    mouseButton = MouseButton::None;
    pos.set(0, 0);
}

void Event::parse(const std::string & typeStr)
{
    std::vector<std::string> output;
    tokenize(typeStr.c_str(), output, "_");
    if (!output.empty())
    {
        type = strToType(output[0]);
        if (output.size() > 1)
        {
            key = strToKey(output[1]);
        }
    }
}

std::string Event::strToKey(const std::string & keyStr)
{
    if ("Grave" == keyStr)
    {
        return "`";
    }
    return keyStr;
}

EventType Event::strToType(const std::string & typeStr)
{
    if ("KeyUp" == typeStr)                return EventType::KeyUp;
    else if ("KeyDown" == typeStr)         return EventType::KeyDown;
    else if ("MouseUp" == typeStr)         return EventType::MouseUp;
    else if ("MouseDown" == typeStr)       return EventType::MouseDown;
    else if ("MouseMove" == typeStr)       return EventType::MouseMove;
    else if ("MouseWheel" == typeStr)      return EventType::MouseWheel;
    else if ("MouseClicked" == typeStr)    return EventType::MouseClicked;
    else if ("WidgetOpened" == typeStr)    return EventType::WidgetOpened;
    else if ("WidgetClosed" == typeStr)    return EventType::WidgetClosed;
    else if ("WidgetDelete" == typeStr)    return EventType::WidgetDelete;
    else if ("WidgetOpening" == typeStr)   return EventType::WidgetOpening;
    else if ("WidgetClosing" == typeStr)   return EventType::WidgetClosing;
    else if ("TimerElapsed" == typeStr)    return EventType::TimerElapsed;
    else if ("SysQuit" == typeStr)         return EventType::SysQuit;
    else if ("MouseOver" == typeStr)       return EventType::MouseOver;
    else if ("MouseLeft" == typeStr)       return EventType::MouseLeft;
    return EventType::Unknown;
}
} // stren