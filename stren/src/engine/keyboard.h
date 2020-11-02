#ifndef STREN_KEYBOARD_H
#define STREN_KEYBOARD_H

#include <vector>
#include <memory>

#include "common/string_ext.h"

namespace stren
{
class Event;
class IAction;

struct KeyboardAction;

enum class EventType;
///
/// class Keyboard
///
class Keyboard
{
private:
    std::vector<KeyboardAction *> m_actions;
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
} // stren
#endif // STREN_KEYBOARD_H
