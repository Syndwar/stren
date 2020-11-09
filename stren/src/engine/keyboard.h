#ifndef STREN_KEYBOARD_H
#define STREN_KEYBOARD_H

#include <vector>
#include <memory>

#include "common/string_ext.h"
#include "engine/event.h"

namespace stren
{
class IAction;

///
/// class KeyboardAction
///
struct KeyboardAction
{
    int                         eventType;
    std::string                 key;
    std::unique_ptr<IAction>    action;
    ///
    /// Constructor
    ///
    KeyboardAction();
    ///
    /// Constructor
    ///
    KeyboardAction(const int et, const std::string & k, IAction * a);
    ///
    /// @todo
    ///
    void reset();
    ///
    /// @todo
    ///
    void reset(const int et, const std::string & k, IAction * a);
    ///
    /// @todo
    ///
    bool isEmpty() const;
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
    size_t addAction(const int eventType, const std::string & key, IAction * action);
    ///
    /// @todo
    ///
    void removeAction(const size_t key);
};
} // stren
#endif // STREN_KEYBOARD_H