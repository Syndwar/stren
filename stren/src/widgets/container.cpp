#include "container.h"

#include "engine_handler.h"
#include "logger.h"
#include "event_listener.h"
#include "lua_stack.h"
#include "lua_value.h"

namespace stren
{

Container::Container(const std::string & id)
    : Widget(id)
{
}

Container::~Container()
{
    detachAll();
}

void Container::doPostMove(const int dx, const int dy)
{
    moveByChildren(dx, dy);
}

void Container::processEvent(const Event & event, bool & isEventCaptured)
{
    if (isOpened())
    {
        bool result(false);
        for (auto it = m_attached.rbegin(); it != m_attached.rend(); ++it)
        {
            Widget * widget = *it;
            if (widget && !widget->isClosed())
            {
                widget->processEvent(event, isEventCaptured);
            }
        }
    }
}

void Container::doRender()
{
    for (Widget * widget : m_attached)
    {
        if (widget && !widget->isClosed())
        {
            widget->render();
        }
    }
}

void Container::attach(Widget * widget)
{
    if (!widget) return;

    Widget * parent = widget->getParent();
    if (!parent)
    {
        addUpdateState(UpdateState::Update);

        m_attached.push_back(widget);
        widget->setParent(this);

        const std::string & id = widget->getId();
        if (!id.empty())
        {
            auto it = m_map.find(id);
            if (it == m_map.end())
            {
                m_map[id] = widget;
            }
            else
            {
                std::string msg = "[Container] Duplicate widget: " + id;
                assertMessage(false, msg.c_str());
            }
        }
    }
}

void Container::detachAll()
{
    m_map.clear();
    for (Widget * widget : m_attached)
    {
        if (widget)
        {
            delete widget;
        }
    }
    m_attached.clear();
}

void Container::sortChildren()
{
    for (size_t i = 0, iEnd = m_attached.size(); i < iEnd; ++i)
    {
        size_t minIndex = i;
        size_t minimumOrder = m_attached[i]->getOrder();
        for (size_t j = i + 1, jEnd = m_attached.size(); j < jEnd; ++j)
        {
            const size_t currentOrder = m_attached[j]->getOrder();
            if (currentOrder < minimumOrder)
            {
                minimumOrder = currentOrder;
                minIndex = j;
            }
        }
        // swamp minimum with current item
        if (i != minIndex)
        {
            Widget * tmp = m_attached[i];
            m_attached[i] = m_attached[minIndex];
            m_attached[minIndex] = tmp;
        }
    }
}

void Container::moveByChildren(const int dx, const int dy)
{
    for (Widget * widget : m_attached)
    {
        if (widget)
        {
            widget->moveBy(dx, dy);
        }
    }
}

void Container::doUpdate(const size_t dt)
{
    if (hasUpdateState(UpdateState::Update))
    {
        sortChildren();
        removeUpdateState(UpdateState::Update);
    }

    for (auto it = m_attached.rbegin(); it != m_attached.rend(); ++it)
    {
        Widget * widget = *it;
        if (widget && !widget->isClosed())
        {
            widget->update(dt);
        }
    }
    Widget::doUpdate(dt);
}

void Container::setDebugView(const bool value)
{
    for (Widget * widget : m_attached)
    {
        if (widget)
        {
            widget->setDebugView(value);
        }
    }
    Widget::setDebugView(value);
}

int createContainer(lua_State * L)
{
    lua::Stack stack(1);
    const std::string id = stack.get(1).getString();
    Container * cnt = new Container(id);
    stack.clear();
    stack.push((void *)cnt);
    return stack.getSize();
}

int attachToContainer(lua_State * L)
{
    lua::Stack stack(2);
    Container * cnt = (Container *)stack.get(1).getUserData();
    if (cnt)
    {
        Widget * widget = (Widget *)stack.get(2).getUserData();
        cnt->attach(widget);
    }
    stack.clear();
    return 0;
}

void Container::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", createContainer },
        { "attach", attachToContainer },
        { NULL, NULL }
    };
    stack.loadLibs("Container", functions);
}
} // stren