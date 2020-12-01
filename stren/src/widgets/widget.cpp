#include "widget.h"

#include "common/colour.h"
#include "engine/engine_handler.h"
#include "engine/event.h"
#include "engine/transform.h"
#include "lua/lua_wrapper.h"
#include "render/primitive_figures.h"
#include "render/renderer.h"

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
            if (m_debugRect)
            {
                if (m_debugRect->getRect() != rect)
                {
                    m_debugRect.reset();
                }
            }

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

namespace lua_widget
{

int getId(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        const std::string & id = widget->getId();
        stack.push(id);
    }
    else
    {
        stack.push();
    }
    return 1;
}

int setRect(lua_State *L)
{
    lua::Stack stack(5);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        widget->setRect(stack.get(2).getInt(), stack.get(3).getInt(), stack.get(4).getInt(), stack.get(5).getInt());
    }
    return 0;
}

int setOrder(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        const int order = stack.get(2).getInt();
        widget->setOrder(order);
    }
    return 0;
}

int open(lua_State *L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        widget->open();
    }
    return 0;
}

int close(lua_State *L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        widget->close();
    }
    return 0;
}

int view(lua_State *L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        const bool isOpen = stack.get(2).getBool();
        widget->view(isOpen);
    }
    return 0;
}

int instantView(lua_State *L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        const bool isOpen = stack.get(2).getBool();
        widget->instantView(isOpen);
    }
    return 0;
}

int setAlignment(lua_State * L)
{
    lua::Stack stack(2);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        const std::string textAlign = stack.get(2).getString();
        const int dx = stack.get(3).getInt();
        const int dy = stack.get(4).getInt();
        widget->setAlignment(textAlign, dx, dy);
    }
    return 0;
}

int getParent(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    stack.clear();
    if (widget)
    {
        Widget * parent = widget->getParent();
        stack.push((void *)parent);
    }
    else
    {
        stack.push();
    }
    return 1;
}

int isOpened(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    stack.clear();
    bool isOpened(false);
    if (widget)
    {
        isOpened = widget->isOpened();
    }
    stack.push(isOpened);
    return 1;
}

int moveTo(lua_State * L)
{
    lua::Stack stack(3);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        const int x = stack.get(2).getInt();
        const int y = stack.get(3).getInt();
        widget->moveTo(x, y);
    }
    return 0;
}

int moveBy(lua_State * L)
{
    lua::Stack stack(3);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        const int x = stack.get(2).getInt();
        const int y = stack.get(3).getInt();
        widget->moveBy(x, y);
    }
    return 0;
}

int attachTransform(lua_State * L)
{
    lua::Stack stack(3);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        const std::string eventType = stack.get(2).getString();
        Transform ** transform = (Transform **)stack.get(3).getUserData();
        if (transform && *transform)
        {
            widget->attachTransform(Event::strToType(eventType), **transform);
        }
    }
    return 0;
}

int addCallback(lua_State * L)
{
    lua::Stack stack(3);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        const std::string eventTypeStr = stack.get(2).getString();
        const std::string callback = stack.get(3).getString();
        widget->addCallback(eventTypeStr, callback);
    }
    return 0;
}

int switchDebugView(lua_State * L)
{
    lua::Stack stack(1);
    lua::Table tbl(stack.get(1));
    Widget * widget = (Widget *)tbl.get("this").getUserData();
    if (widget)
    {
        widget->setDebugView(!widget->isDebugView());
    }
    return 0;
}
} // lua_widget

void Widget::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "getId", lua_widget::getId },
        { "setRect", lua_widget::setRect },
        { "setAlignment", lua_widget::setAlignment },
        { "setOrder", lua_widget::setOrder },
        { "open", lua_widget::open },
        { "close", lua_widget::close },
        { "view", lua_widget::view },
        { "instantView", lua_widget::instantView },
        { "getParent", lua_widget::getParent },
        { "isOpened", lua_widget::isOpened },
        { "moveTo", lua_widget::moveTo },
        { "moveBy", lua_widget::moveBy },
        { "attachTransform", lua_widget::attachTransform },
        { "addCallback", lua_widget::addCallback },
        { "switchDebugView", lua_widget::switchDebugView },
        { NULL, NULL }
    };
    stack.loadLibs("Widget", functions);
}

} // stren