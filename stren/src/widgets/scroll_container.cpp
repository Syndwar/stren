#include "scroll_container.h"

#include "engine/engine.h"
#include "engine/engine_handler.h"
#include "engine/event.h"
#include "render/renderer.h"

#include "lua/lua_wrapper.h"

namespace stren
{

int strToScrollDirection(const std::string & actionId)
{
    if (actionId == "Up") return ScrollContainer::ScrollDirection::Up;
    if (actionId == "Down") return ScrollContainer::ScrollDirection::Down;
    if (actionId == "Left") return ScrollContainer::ScrollDirection::Left;
    if (actionId == "Right") return ScrollContainer::ScrollDirection::Right;
    return ScrollContainer::ScrollDirection::None;
}
ScrollContainer::ScrollContainer(const std::string & id)
    : Container(id)
    , m_updateInterval(100)
    , m_speed(1)
    , m_wheelSpeed(16)
    , m_direction(ScrollDirection::None)
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
    m_camera.moveTo(rect.getX(), rect.getY());
    m_camera.resize(rect.getWidth(), rect.getHeight());
}

void ScrollContainer::doPostResize(const int dw, const int dh)
{
    Container::doPostResize(dw, dh);

    const Rect & rect = getRect();
    m_camera.resize(rect.getWidth(), rect.getHeight());
}

Point ScrollContainer::screenToScrollPos(const int x, const int y) const
{
    return Point(x + m_offset.getX(), y + m_offset.getY());
}

void ScrollContainer::setContentRect(const int x, const int y, const int w, const int h)
{
    m_contentRect.set(x, y, w, h);
    calculateMaxOffset();
}

void ScrollContainer::calculateMaxOffset()
{
    const int contentWidth = m_contentRect.getWidth();
    const int contentHeight = m_contentRect.getHeight();
    const int rectWidth = getRect().getWidth();
    const int rectHeight = getRect().getHeight();
    m_maxOffset.set(contentWidth < rectWidth ? 0 : contentWidth - rectWidth, 
                   contentHeight < rectHeight ? 0 : contentHeight - rectHeight);
}

void ScrollContainer::setScrollSpeed(const int speed)
{
    m_speed = speed;
    m_updateInterval = 1000 / speed;
}

void ScrollContainer::doRender()
{
    m_camera.place();
    Container::doRender();
    m_camera.restore();
}

void ScrollContainer::jumpTo(const int x, const int y)
{
    const int dx = x - m_offset.getX();
    const int dy = y - m_offset.getY();

    // check if scrolling is needed
    if (!dx && !dy) return;

    m_target.set(x, y);

    jumpBy(dx, dy);
}

void ScrollContainer::jumpBy(const int dx, const int dy)
{
    int newX = m_offset.getX() + dx;
    int newY = m_offset.getY() + dy;

    if (newX < 0)
    {
        newX = 0;
    }
    else if (newX > m_maxOffset.getX())
    {
        newX = m_maxOffset.getX();
    }

    if (newY < 0)
    {
        newY = 0;
    }
    else if (newY > m_maxOffset.getY())
    {
        newY = m_maxOffset.getY();
    }

    m_offset.set(newX, newY);
    m_camera.setTarget(newX, newY);
}

void ScrollContainer::scrollTo(const int x, const int y)
{
    const int dx = x - m_offset.getX();
    const int dy = y - m_offset.getY();

    m_target.set(x, y);

    // check if scrolling is needed
    if (!dx && !dy) return;

    m_timer.restart(m_updateInterval);
}

void ScrollContainer::scrollTo(const int direction, const bool add)
{
    if (add)
    {
        m_direction |= direction;
    }
    else
    {
        m_direction &= ~direction;
    }
    const Point point = getDirectionPoint(m_direction);
    scrollTo(point.getX(), point.getY());
}

bool ScrollContainer::isScrolling() const
{
    return m_target.getX() != m_offset.getX();
}

void ScrollContainer::processEvent(const Event & event, bool & isEventCaptured)
{
    Event newEvent(event);
    newEvent.pos.moveBy(m_offset.getX(), m_offset.getY());

    if (!isEventCaptured)
    {
        switch (newEvent.type)
        {
            case EventType::MouseDown:
            case EventType::MouseWheel:
            {
                const Point & mousePos = EngineHandler::getMousePos();
                if (getRect().hasCommon(mousePos))
                {
                    switch (newEvent.type)
                    {
                    case EventType::MouseDown:
                    {
                        if (hasCallback(event))
                        {
                            callBack(event, this);
                            isEventCaptured = true;
                        }
                    }
                    break;
                    case EventType::MouseWheel:
                    {
                        const int dx = event.wheel.getX() * m_wheelSpeed;
                        const int dy = event.wheel.getY() * m_wheelSpeed;
                        jumpTo(m_offset.getX() - dx, m_offset.getY() - dy);
                        isEventCaptured = true;
                    }
                    break;
                    }
                }
            }
            break;
        }
    }
    Container::processEvent(newEvent, isEventCaptured);
}

void ScrollContainer::doUpdate(const size_t dt)
{
    m_timer.update(dt);
    if (m_target != m_offset)
    {
        if (m_timer.isElapsed())
        {
            // check if timer elapsed earlier than update was called
            // and compensate it
            int incrementX = 1;
            int incrementY = 1;
            // compensation leads to screen tearing
            if (dt > m_updateInterval)
            {
                incrementX = dt / m_updateInterval;
                incrementY = incrementX;
            }

            int dx = m_target.getX() - m_offset.getX();
            int dy = m_target.getY() - m_offset.getY();

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

            m_timer.restart(m_updateInterval);
        }
    }

    Container::doUpdate(dt);
}

Point ScrollContainer::getDirectionPoint(const int direction)
{
    Point point(m_offset);

    if (direction & ScrollDirection::Left)
    {
        if (direction & ScrollDirection::Up)
        {
            point.set(m_contentRect.getX(), m_contentRect.getY());
        }
        else if (direction & ScrollDirection::Down)
        {
            point.set(m_contentRect.getX(), m_contentRect.getBottom());
        }
        else
        {
            point.set(m_contentRect.getX(), m_offset.getY());
        }
    }
    else if (direction & ScrollDirection::Right)
    {
        if (direction & ScrollDirection::Up)
        {
            point.set(m_contentRect.getRight(), m_contentRect.getY());
        }
        else if (direction & ScrollDirection::Down)
        {
            point.set(m_contentRect.getRight(), m_contentRect.getBottom());
        }
        else
        {
            point.set(m_contentRect.getRight(), m_offset.getY());
        }
    }
    else if (direction & ScrollDirection::Right)
    {
    }
    else if (direction & ScrollDirection::Up)
    {
        point.set(m_offset.getX(), m_contentRect.getY());
    }
    else if (direction & ScrollDirection::Down)
    {
        point.set(m_offset.getX(), m_contentRect.getBottom());
    }
    return point;
}

namespace lua_scroll_container
{
int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    const size_t handler = EngineHandler::storeInMemoryController(new ScrollContainer(id));
    stack.push(handler);
    return 1;
}

int setScrollSpeed(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    ScrollContainer * cnt = EngineHandler::getMemoryObj<ScrollContainer *>(tbl);
    if (cnt)
    {
        const int speed = stack.get(2).getInt();
        cnt->setScrollSpeed(speed);
    }
    stack.clear();
    return 0;
}

int jumpTo(lua_State * L)
{
    lua::Stack stack(3);
    lua::Table tbl(stack.get(1));
    ScrollContainer * cnt = EngineHandler::getMemoryObj<ScrollContainer *>(tbl);
    if (cnt)
    {
        const int x = stack.get(2).getInt();
        const int y = stack.get(3).getInt();
        cnt->jumpTo(x, y);
    }
    return 0;
}

int scrollTo(lua_State * L)
{
    lua::Stack stack(3);
    lua::Table tbl(stack.get(1));
    ScrollContainer * cnt = EngineHandler::getMemoryObj<ScrollContainer *>(tbl);
    if (cnt)
    {
        const int x = stack.get(2).getInt();
        const int y = stack.get(3).getInt();
        cnt->scrollTo(x, y);
    }
    return 0;
}

int isScrolling(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    ScrollContainer * cnt = EngineHandler::getMemoryObj<ScrollContainer *>(tbl);
    bool isScrolling(false);
    if (cnt)
    {
        isScrolling = cnt->isScrolling();
    }
    stack.push(isScrolling);
    return 1;
}

int setContentRect(lua_State * L)
{
    lua::Stack stack(5);
    lua::Table tbl(stack.get(1));
    ScrollContainer * cnt = EngineHandler::getMemoryObj<ScrollContainer *>(tbl);
    if (cnt)
    {
        const int x = stack.get(2).getInt();
        const int y = stack.get(3).getInt();
        const int w = stack.get(4).getInt();
        const int h = stack.get(5).getInt();
        cnt->setContentRect(x, y, w, h);
    }
    return 0;
}

int enableScroll(lua_State * L)
{
    lua::Stack stack(3);
    lua::Table tbl(stack.get(1));
    ScrollContainer * cnt = EngineHandler::getMemoryObj<ScrollContainer *>(tbl);
    const int direction = strToScrollDirection(stack.get(2).getString());
    const bool value = stack.get(3).getBool();
    if (cnt)
    {
        if (value)
        {
            cnt->scrollTo(direction, value);

        }
        else if (0 != (cnt->getScrollDirection() & direction))
        {
            cnt->scrollTo(direction, value);
        }
    }
    return 0;
}

int screenToScrollPos(lua_State * L)
{
    lua::Stack stack(3);
    lua::Table tbl(stack.get(1));
    ScrollContainer * cnt = EngineHandler::getMemoryObj<ScrollContainer *>(tbl);
    int x = stack.get(2).getInt();
    int y = stack.get(3).getInt();
    if (cnt)
    {
        const Point pos = cnt->screenToScrollPos(x, y);
        x = pos.getX();
        y = pos.getY();
    }
    stack.push(x);
    stack.push(y);
    return 2;
}

} // lua_scroll_container

void ScrollContainer::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_scroll_container::create },
        { "setScrollSpeed", lua_scroll_container::setScrollSpeed },
        { "setContentRect", lua_scroll_container::setContentRect },
        { "enableScroll", lua_scroll_container::enableScroll },
        { "jumpTo", lua_scroll_container::jumpTo },
        { "scrollTo", lua_scroll_container::scrollTo },
        { "isScrolling", lua_scroll_container::isScrolling },
        { "screenToScrollPos", lua_scroll_container::screenToScrollPos },
        { NULL, NULL }
    };
    stack.loadLibs("ScrollContainer", functions);
}
} // stren