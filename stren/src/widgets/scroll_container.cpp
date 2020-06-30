#include "scroll_container.h"

#include "engine_handler.h"
#include "event.h"
#include "renderer.h"

namespace stren
{

///
/// class ScrollAction provides an ability to move objects inside it around the screen
///
class ScrollAction : public IAction
{
private:
    ScrollContainer * container_;     ///< scroll container who created the action
    int               direction_;     ///< scroll direction
public:
    ///
    /// Constructor
    ///
    ScrollAction(ScrollContainer * container, const int direction)
        : IAction()
        , container_(container)
        , direction_(direction)
    {
    }
    ///
    /// Destructor
    ///
    virtual ~ScrollAction() {}
    ///
    /// start action
    ///
    virtual void exec() override
    {
        if (container_)
        {
            container_->scrollTo(direction_, true);
        }
    }
    ///
    /// cancel action
    ///
    virtual void cancel() override
    {
        if (container_)
        {
            if (0 != (container_->getScrollDirection() & direction_))
            {
                container_->scrollTo(direction_, false);
            }
        }
    }
};

const std::map<ScrollContainer::ScrollDirection, std::string> ScrollContainer::kScrollDirections = {
    {ScrollDirection::None, "None"},
    {ScrollDirection::Left, "Left"},
    {ScrollDirection::Right, "Right"},
    {ScrollDirection::Up, "Up"},
    {ScrollDirection::Down, "Down"}
};

ScrollContainer::ScrollContainer(const std::string & id)
    : Container(id)
    , updateInterval_(100)
    , speed_(1)
    , wheelSpeed_(16)
    , direction_(ScrollDirection::None)
    , camera_(getRect())
{
}

ScrollContainer::~ScrollContainer()
{
}

void ScrollContainer::doPostMove(const int dx, const int dy)
{
    Container::doPostMove(dx, dy);

    calculateMaxOffset();
    
    const Rect & rect = getRect();
    camera_.moveTo(rect.getX(), rect.getY());
    camera_.resize(rect.getWidth(), rect.getHeight());
}

Point ScrollContainer::screenToScrollPos(const int x, const int y) const
{
    return Point(x + offset_.getX(), y + offset_.getY());
}

void ScrollContainer::setContentRect(const int x, const int y, const int w, const int h)
{
    contentRect_.set(x, y, w, h);
    calculateMaxOffset();
}

void ScrollContainer::calculateMaxOffset()
{
    const int contentWidth = contentRect_.getWidth();
    const int contentHeight = contentRect_.getHeight();
    const int rectWidth = getRect().getWidth();
    const int rectHeight = getRect().getHeight();
    maxOffset_.set(contentWidth < rectWidth ? 0 : contentWidth - rectWidth, 
                   contentHeight < rectHeight ? 0 : contentHeight - rectHeight);
}

void ScrollContainer::setScrollSpeed(const int speed)
{
    speed_ = speed;
    updateInterval_ = 1000 / speed;
}

void ScrollContainer::doRender()
{
    camera_.place();
    Container::doRender();
    camera_.restore();
}

void ScrollContainer::jumpTo(const int x, const int y)
{
    const int dx = x - offset_.getX();
    const int dy = y - offset_.getY();

    // check if scrolling is needed
    if (!dx && !dy) return;

    target_.set(x, y);

    jumpBy(dx, dy);
}

void ScrollContainer::jumpBy(const int dx, const int dy)
{
    int newX = offset_.getX() + dx;
    int newY = offset_.getY() + dy;

    if (newX < 0)
    {
        newX = 0;
    }
    else if (newX > maxOffset_.getX())
    {
        newX = maxOffset_.getX();
    }

    if (newY < 0)
    {
        newY = 0;
    }
    else if (newY > maxOffset_.getY())
    {
        newY = maxOffset_.getY();
    }

    offset_.set(newX, newY);
    camera_.setTarget(newX, newY);
}

void ScrollContainer::scrollTo(const int x, const int y)
{
    const int dx = x - offset_.getX();
    const int dy = y - offset_.getY();

    target_.set(x, y);

    // check if scrolling is needed
    if (!dx && !dy) return;

    timer_.restart(updateInterval_);
}

void ScrollContainer::scrollTo(const int direction, const bool add)
{
    if (add)
    {
        direction_ |= direction;
    }
    else
    {
        direction_ &= ~direction;
    }
    const Point point = getDirectionPoint(direction_);
    scrollTo(point.getX(), point.getY());
}

bool ScrollContainer::isScrolling() const
{
    return target_.getX() != offset_.getX();
}

void ScrollContainer::processEvent(const Event & event, bool & isEventCaptured)
{
    Event newEvent(event);
    newEvent.pos.moveBy(offset_.getX(), offset_.getY());

    if (!isEventCaptured)
    {
        const Point & mousePos = EngineHandler::getMousePos();
        if (getRect().hasCommon(mousePos))
        {
            switch (newEvent.type)
            {
                case EventType::MouseDown:
                {
                    if (hasCallback(EventType::MouseClicked))
                    {
                        callBack(EventType::MouseClicked, this);
                        isEventCaptured = true;
                    }
                }
                break;
                case EventType::MouseWheel:
                {
                    const int dx = event.wheel.getX() * wheelSpeed_;
                    const int dy = event.wheel.getY() * wheelSpeed_;
                    jumpTo(offset_.getX() - dx, offset_.getY() - dy);
                    isEventCaptured = true;
                }
                break;
            }
        }
    }
    Container::processEvent(newEvent, isEventCaptured);
}

void ScrollContainer::doUpdate(const size_t dt)
{
    timer_.update(dt);
    if (target_ != offset_)
    {
        if (timer_.isElapsed())
        {
            // check if timer elapsed earlier than update was called
            // and compensate it
            int incrementX = 1;
            int incrementY = 1;
            // compensation leads to screen tearing
            if (dt > updateInterval_)
            {
                incrementX = dt / updateInterval_;
                incrementY = incrementX;
            }

            int dx = target_.getX() - offset_.getX();
            int dy = target_.getY() - offset_.getY();

            const bool negativeX = dx < 0;
            const bool negativeY = dy < 0;

            if (negativeX)
            {
                dx = -dx;
            }

            if (negativeY)
            {
                dy = -dy;
            }

            // check if increment is lower than dx
            // otherwise - compensate it
            if (dx < incrementX)
            {
                incrementX = dx;
            }

            if (dy < incrementY)
            {
                incrementY = dy;
            }
            
            // select movement direction
            if (negativeX)
            {
                incrementX = -incrementX;
            }

            if (negativeY)
            {
                incrementY = -incrementY;
            }

            jumpBy(incrementX, incrementY);

            timer_.restart(updateInterval_);
        }
    }

    Container::doUpdate(dt);
}

IAction * ScrollContainer::createAction(const int direction)
{
    if (direction != ScrollDirection::None)
    {
        return new ScrollAction(this, direction);
    }
    return nullptr;
}

Point ScrollContainer::getDirectionPoint(const int direction)
{
    Point point(offset_);

    if (direction & ScrollDirection::Left)
    {
        if (direction & ScrollDirection::Up)
        {
            point.set(contentRect_.getX(), contentRect_.getY());
        }
        else if (direction & ScrollDirection::Down)
        {
            point.set(contentRect_.getX(), contentRect_.getBottom());
        }
        else
        {
            point.set(contentRect_.getX(), offset_.getY());
        }
    }
    else if (direction & ScrollDirection::Right)
    {
        if (direction & ScrollDirection::Up)
        {
            point.set(contentRect_.getRight(), contentRect_.getY());
        }
        else if (direction & ScrollDirection::Down)
        {
            point.set(contentRect_.getRight(), contentRect_.getBottom());
        }
        else
        {
            point.set(contentRect_.getRight(), offset_.getY());
        }
    }
    else if (direction & ScrollDirection::Right)
    {
    }
    else if (direction & ScrollDirection::Up)
    {
        point.set(offset_.getX(), contentRect_.getY());
    }
    else if (direction & ScrollDirection::Down)
    {
        point.set(offset_.getX(), contentRect_.getBottom());
    }
    return point;
}
} // stren