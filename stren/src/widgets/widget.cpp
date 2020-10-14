#include "widget.h"

#include "colour.h"
#include "engine_handler.h"
#include "event.h"
#include "lua_wrapper.h"
#include "primitive_figures.h"
#include "renderer.h"
#include "transform.h"

namespace stren
{

Widget::Widget(const std::string & id)
    : Listener()
    , m_id(id)
    , m_parent(nullptr)
    , m_order(0)
    , m_alignment(0)
    , m_debugView(false)
    , m_viewState(ViewState::Opened)
    , m_updateState(UpdateState::Update)
{
}

Widget::~Widget()
{
    callBack(EventType::WidgetDelete, this);
    EngineHandler::consoleLog(m_id);
}

void Widget::moveTo(const int x, const int y)
{
    const int dx = x - m_rect.getX();
    const int dy = y - m_rect.getY();
    m_rect.moveTo(x, y);
    doPostMove(dx, dy);
}

void Widget::moveBy(const int dx, const int dy)
{
    m_rect.moveBy(dx, dy);
    doPostMove(dx, dy);
}

void Widget::update(const size_t dt)
{
    m_transform.update(dt);

    updateViewState();

    if (isClosed()) return;

    if (hasUpdateState(UpdateState::Align))
    {
        align();
        removeUpdateState(UpdateState::Align);
    }

    doUpdate(dt);
}

void Widget::setRect(const int x, const int y, const int w, const int h)
{
    int width = w;
    if (-1 == width)
    {
        width = EngineHandler::getScreenWidth();
    }

    int height = h;
    if (-1 == height)
    {
        height = EngineHandler::getScreenHeight();
    }
    const int dx = x - m_rect.getX();
    const int dy = y - m_rect.getY();
    m_rect.set(x, y, width, height);
    doPostMove(dx, dy);
}

void Widget::setRect(const Rect & rect)
{
    int width = rect.getWidth();
    if (-1 == width)
    {
        width = EngineHandler::getScreenWidth();
    }

    int height = rect.getHeight();
    if (-1 == height)
    {
        height = EngineHandler::getScreenHeight();
    }
    setRect(rect.getX(), rect.getY(), width, height);
}

void Widget::view(const bool value)
{
    if (value)
    {
        open();
    }
    else
    {
        close();
    }
}

void Widget::instantView(const bool value)
{
    if (value)
    {
        instantOpen();
    }
    else
    {
        instantClose();
    }
}

void Widget::open()
{
    if (ViewState::Closed == getState())
    {
        setState(ViewState::Opening);
        startTransform(EventType::WidgetOpening);
    }
}

void Widget::close()
{
    if (ViewState::Opened == getState())
    {
        setState(ViewState::Closing);
        startTransform(EventType::WidgetClosing);
    }
}

void Widget::instantOpen()
{
    setState(ViewState::Opened);
    callBack(EventType::WidgetOpened, this);
    doOpen();
}

void Widget::instantClose()
{
    setState(ViewState::Closed);
    callBack(EventType::WidgetClosed, this);
    doClose();
}

void Widget::updateViewState()
{
    if (ViewState::Opening == m_viewState)
    {
        if (isTransformCompleted(EventType::WidgetOpening))
        {
            instantOpen();
        }
    }
    else if (ViewState::Closing == m_viewState)
    {
        if (isTransformCompleted(EventType::WidgetClosing))
        {
            instantClose();
        }
    }
}

void Widget::startTransform(const EventType eventType)
{
    m_transform.start(eventType);
}


bool Widget::isTransformCompleted(const EventType eventType) const
{
    return m_transform.isCompleted(eventType);
}

bool Widget::render()
{
    if (!isClosed())
    {
        doPreRender();
        doRender();
        doPostRender();
        doDebugRender();

        return true;
    }
    return false;
}

void Widget::doPreRender()
{
    m_transform.preRender();
}

void Widget::doPostRender()
{
    m_transform.postRender();
}

void Widget::doDebugRender()
{
    if (m_debugView)
    {
        const Rect & rect = getRect();
        if (!rect.isEmpty())
        {
            static const Colour colour(Colour::Type::Green);
            if (!m_debugRect)
            {
                m_debugRect = std::make_unique<PrimitiveRect>(rect, false);
            }
            if (m_debugRect)
            {
                m_debugRect->render(colour);
            }
        }
    }
}

bool Widget::isClosed() const
{
    return ViewState::Closed == m_viewState;
}

bool Widget::isOpened() const
{
    return ViewState::Opened == m_viewState;
}

void Widget::setAlignment(const int alignment, const int dx, const int dy)
{
    if (m_alignment != alignment)
    {
        m_alignment = alignment;
        m_alignmentOffset.moveTo(dx, dy);
        addUpdateState(UpdateState::Align);
    }
}

void Widget::setAlignment(const std::string & alignment, const int dx, const int dy)
{
    const int value = Alignment::stringToAlignment(alignment);
    setAlignment(value, dx, dy);
}

void Widget::align()
{
    const int screenWidth = EngineHandler::getScreenWidth();
    const int screenHeight = EngineHandler::getScreenHeight();
    const Rect screenRect(0, 0, screenWidth, screenHeight);
    const Rect oldRect = m_rect;
    screenRect.align(m_rect, m_alignment);
    m_rect.moveBy(m_alignmentOffset.getX(), m_alignmentOffset.getY());
    doPostMove(m_rect.getX() - oldRect.getX(), m_rect.getY() - oldRect.getY());
}

void Widget::attachTransform(const EventType eventType, const Transform & transform)
{
    m_transform.setTransform(eventType, transform);
}

int setWidgetRect(lua_State *L)
{
    lua::Stack stack(5);
    Widget * widget = (Widget *)stack.get(1).getUserData();
    if (widget)
    {
        widget->setRect(stack.get(2).getInt(), stack.get(3).getInt(), stack.get(4).getInt(), stack.get(5).getInt());
    }
    return 0;
}

int openWidget(lua_State *L)
{
    lua::Stack stack(1);
    Widget * widget = (Widget *)stack.get(1).getUserData();
    if (widget)
    {
        widget->open();
    }
    return 0;
}

int closeWidget(lua_State *L)
{
    lua::Stack stack(1);
    Widget * widget = (Widget *)stack.get(1).getUserData();
    if (widget)
    {
        widget->close();
    }
    return 0;
}

int setWidgetAlignment(lua_State * L)
{
    lua::Stack stack(2);
    Widget * widget = (Widget *)stack.get(1).getUserData();
    if (widget)
    {
        const std::string textAlign = stack.get(2).getString();
        const int dx = stack.get(3).getInt();
        const int dy = stack.get(4).getInt();
        widget->setAlignment(textAlign, dx, dy);
    }
    stack.clear();
    return 0;
}

void Widget::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "setRect", setWidgetRect },
        { "setAlignment", setWidgetAlignment },
        { "open", openWidget },
        { "close", closeWidget },
        { NULL, NULL }
    };
    stack.loadLibs("Widget", functions);
}

} // stren