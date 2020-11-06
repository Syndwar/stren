#ifndef STREN_KEYBOARD_H
#define STREN_KEYBOARD_H

#include <vector>
#include <memory>

#include "common/string_ext.h"
#include "engine/action.h"
#include "engine/event.h"

namespace stren
{
///
/// class KeyboardAction
///
struct KeyboardAction
{
    EventType                   eventType;
    std::string                 key;
    std::unique_ptr<IAction>    action;
    ///
    /// Constructor
    ///
    KeyboardAction()
        : eventType(EventType::None)
    {
    }
    ///
    /// Constructor
    ///
    KeyboardAction(const EventType et, const std::string & k, IAction * a)
        : eventType(et)
        , key(k)
        , action(a)
    {
    }
    ///
    /// @todo
    ///
    void reset()
    {
        action.reset();
        key.clear();
        eventType = EventType::None;
    }
    ///
    /// @todo
    ///
    void reset(const EventType et, const std::string & k, IAction * a)
    {
        action.reset(a);
        key = k;
        eventType = et;
    }
    ///
    /// @todo
    ///
    bool isEmpty() const
    {
        return EventType::None == eventType && key.empty() && action;
    }
};

///
/// class Keyboard
///
class Keyboard
{
private:
    std::vector<KeyboardAction> m_actions;      ///< @todo
public:
    ///
    /// Constructor
    ///
    Keyboard();
    ///
    /// @todo
    ///
    void update(const size_t dt);
    ///
    /// @todo
    ///
    void processEvent(const Event & event, bool & isEventCaptured);
    ///
    /// @todo
    ///
    size_t addAction(const EventType eventType, const std::string & key, IAction * action);
    ///
    /// @todo
    ///
    void removeAction(const size_t key);
};

struct MouseAction
{
    EventType                   eventType;
    Event::MouseButton          button;
    std::unique_ptr<IAction>    action;
    ///
    /// Constructor
    ///
    MouseAction()
        : eventType(EventType::None)
    {
    }
    ///
    /// Constructor
    ///
    MouseAction(const EventType et, const Event::MouseButton b, IAction * a)
        : eventType(et)
        , button(b)
        , action(a)
    {
    }
    ///
    /// @todo
    ///
    void reset()
    {
        action.reset();
        button = Event::MouseButton::None;
        eventType = EventType::None;
    }
    ///
    /// @todo
    ///
    void reset(const EventType et, const Event::MouseButton b, IAction * a)
    {
        action.reset(a);
        button = b;
        eventType = et;
    }
    ///
    /// @todo
    ///
    bool isEmpty() const
    {
        return EventType::None == eventType && Event::MouseButton::None == button && action;
    }
};

///
/// class Mouse
///
class Mouse
{
private:
    std::vector<MouseAction> m_actions;      ///< @todo
public:
    ///
    /// Constructor
    ///
    Mouse();
    ///
    /// @todo
    ///
    void update(const size_t dt);
    ///
    /// @todo
    ///
    void processEvent(const Event & event, bool & isEventCaptured);
    ///
    /// @todo
    ///
    size_t addAction(const EventType eventType, const Event::MouseButton button, IAction * action);
    ///
    /// @todo
    ///
    void removeAction(const size_t key);
};
} // stren
#endif // STREN_KEYBOARD_H
