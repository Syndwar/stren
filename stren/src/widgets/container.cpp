#include "container.h"

#include "engine/engine_handler.h"
#include "engine/logger.h"
#include "lua/lua_wrapper.h"

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
        if (!isEventCaptured)
        {
            switch (event.type)
            {
            case EventType::KeyDown:
            case EventType::KeyUp:
            {
                if (hasCallback(event.type))
                {
                    callBack(event.type, this, event.key);
                    isEventCaptured = true;
                }
            }
            break;
            }
        }

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

void Container::detach(Widget * widget)
{
    if (!widget) return;

    Widget * parent = widget->getParent();
    if (parent)
    {
        addUpdateState(UpdateState::Update);

        for (size_t i = 0, iEnd = m_attached.size(); i < iEnd; ++i)
        {
            if (m_attached[i] == widget)
            {
                m_attached[i] = nullptr;
                break;
            }
        }

        widget->setParent(nullptr);

        const std::string & id = widget->getId();
        if (!id.empty())
        {
            auto it = m_map.find(id);
            if (it != m_map.end())
            {
                m_map.erase(id);
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

void Container::removeDeadWidgets()
{
    auto it = m_attached.begin();
    while (it != m_attached.end())
    {
        if (nullptr == *it)
        {
            it = m_attached.erase(it);
        }
        else
        {
            ++it;
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

namespace lua_container
{

int create(lua_State * L)
{
    lua::Stack stack(0);
    const std::string id = stack.getSize() > 0 ? stack.get(1).getString() : String::kEmpty;
    Container * cnt = new Container(id);
    stack.clear();
    stack.push((void *)cnt);
    return stack.getSize();
}

int attach(lua_State * L)
{
    lua::Stack stack(2);
    Container * cnt = (Container *)stack.get(1).getUserData();
    if (cnt)
    {
        Widget * widget = (Widget *)stack.get(2).getUserData();
        cnt->attach(widget);
    }
    return 0;
}

int detach(lua_State * L)
{
    lua::Stack stack(2);
    Container * cnt = (Container *)stack.get(1).getUserData();
    if (cnt)
    {
        Widget * widget = (Widget *)stack.get(2).getUserData();
        cnt->detach(widget);
    }
    return 0;
}

int detachAll(lua_State * L)
{
    lua::Stack stack(1);
    Container * cnt = (Container *)stack.get(1).getUserData();
    if (cnt)
    {
        cnt->detachAll();
    }
    return 0;
}

int findWidget(lua_State * L)
{
    lua::Stack stack(2);
    Container * cnt = (Container *)stack.get(1).getUserData();
    const std::string id = stack.get(2).getString();
    if (cnt)
    {
        Widget * widget = cnt->findWidget<Widget>(id);
        stack.push((void *)widget);
    }
    else
    {
        stack.push();
    }
    return 1;
}

int getAttached(lua_State * L)
{
    lua::Stack stack(1);
    Widget * widget = (Widget *)stack.get(1).getUserData();
    Container * cnt = dynamic_cast<Container *>(widget);
    lua::Table tbl;
    tbl.create();
    if (cnt)
    {
        int i = 1;
        std::vector<Widget *> attached = cnt->debugGetAttached();
        for (Widget * w : attached)
        {
            if (w)
            {
                tbl.set(i, (void *)w);
                ++i;
            }
        }
    }
    stack.push(tbl);
    return 1;
}
} // lua_container

void Container::bind()
{
    lua::Stack stack;
    const luaL_reg functions[] =
    {
        { "new", lua_container::create },
        { "attach", lua_container::attach },
        { "detach", lua_container::detach },
        { "findWidget", lua_container::findWidget },
        { "getAttached", lua_container::getAttached },
        { "detachAll", lua_container::detachAll },
        { NULL, NULL }
    };
    stack.loadLibs("Container", functions);
}
} // stren