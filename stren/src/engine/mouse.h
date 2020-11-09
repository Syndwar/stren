#ifndef STREN_MOUSE_H
#define STREN_MOUSE_H

#include <vector>
#include <memory>

#include "common/string_ext.h"
#include "engine/event.h"

namespace stren
{
class IAction;

struct MouseAction
{
    int                         eventType;
    Event::MouseButton          button;
    std::unique_ptr<IAction>    action;
    ///
    /// Constructor
    ///
    MouseAction();
    ///
    /// Constructor
    ///
    MouseAction(const int et, const Event::MouseButton b, IAction * a);
    ///
    /// @todo
    ///
    void reset();
    ///
    /// @todo
    ///
    void reset(const int et, const Event::MouseButton b, IAction * a);
    ///
    /// @todo
    ///
    bool isEmpty() const;
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
    size_t addAction(const int eventType, const Event::MouseButton button, IAction * action);
    ///
    /// @todo
    ///
    void removeAction(const size_t key);
};

} // stren
#endif // STREN_MOUSE_H
