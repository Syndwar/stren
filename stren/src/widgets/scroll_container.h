#ifndef STREN_SCROLL_CONTAINER_H
#define STREN_SCROLL_CONTAINER_H

#include "container.h"
#include "timer.h"
#include "action.h"
#include "camera.h"

namespace stren
{
class IAction;
///
/// class ScrollContainer provides an ability to move objects inside it around the screen
///
class ScrollContainer : public Container
{
public:
    enum ScrollDirection
    {
        None = 0x0000,
        Left = 0x0001,
        Right = 0x002,
        Up = 0x004,
        Down = 0x008,
    };                                        ///< scroll directions list enum

    static const std::map<ScrollDirection, std::string> kScrollDirections;    ///< scroll directions list in strings
                                      
private:
    int             direction_;                ///< scroll direction
    size_t          updateInterval_;           ///< update scroll container interval in milliseconds
    int             speed_;                    ///< scrolling speed
    int             wheelSpeed_;               ///< mouse wheel scrolling speed
    Rect            contentRect_;              ///< rectangle that incorporates all widgets in the scroll container
    Point           maxOffset_;                ///< maximum objects offset (depends on scroll container rect and content rect)
    Point           offset_;                   ///< current objects offset
    Point           target_;                   ///< position where scroll container should move
    Timer           timer_;                    ///< update timer
    Camera          camera_;                   ///< camera that is used to move objects and limit their visibility
public:
    ///
    /// Constructor
    ///
    ScrollContainer(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~ScrollContainer();
    ///
    /// process incoming system events, returns true if the event was processed, otherwise - returns false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
    ///
    /// scroll to x, y position instantly
    ///
    void jumpTo(const int x, const int y);
    ///
    /// scroll to x, y position
    ///
    void scrollTo(const int x, const int y);
    ///
    /// scroll to x, y position
    ///
    void scrollTo(const int direction, const bool add);
    ///
    /// returns scroll speed
    ///
    void setScrollSpeed(const int speed);
    ///
    /// set scrolling speed
    ///
    inline int scrollSpeed() const { return speed_; }
    ///
    /// @todo
    ///
    void setContentRect(const int x, const int y, const int w, const int h);
    ///
    /// returns if scroll container is scrolling
    ///
    bool isScrolling() const;
    ///
    /// creates action, caller must take ownership
    ///
    IAction * createAction(const int direction);
    ///
    /// convert screen coordinate to scroll coordinate
    ///
    Point screenToScrollPos(const int x, const int y) const;
    ///
    /// returns scrolling direction
    ///
    int getScrollDirection() const { return direction_; }
protected:
    ///
    /// is called when widget position has changed
    ///
    virtual void doPostMove(const int dx, const int dy) override;
private:
    ///
    /// returns scroll container point based on desired scroll direction
    ///
    Point getDirectionPoint(const int direction);
    ///
    /// @todo
    ///
    virtual void doRender() override;
    ///
    /// @todo
    ///
    void jumpBy(const int dx, const int dy);
    ///
    /// @todo
    ///
    virtual void doUpdate(const size_t dt) override;
    ///
    /// @todo
    ///
    void calculateMaxOffset();
};
} // stren

#endif // STREN_SCROLL_CONTAINER_H