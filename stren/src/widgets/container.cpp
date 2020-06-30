#include "container.h"

#include "engine_handler.h"
#include "logger.h"
#include "event_listener.h"

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
        for (auto it = attached_.rbegin(); it != attached_.rend(); ++it)
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
    for (Widget * widget : attached_)
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

        attached_.push_back(widget);
        widget->setParent(this);

        const std::string & id = widget->getId();
        if (!id.empty())
        {
            auto it = map_.find(id);
            if (it == map_.end())
            {
                map_[id] = widget;
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
    map_.clear();
    for (Widget * widget : attached_)
    {
        if (widget)
        {
            delete widget;
        }
    }
    attached_.clear();
}

void Container::sortChildren()
{
    for (size_t i = 0, iEnd = attached_.size(); i < iEnd; ++i)
    {
        size_t minIndex = i;
        size_t minimumOrder = attached_[i]->getOrder();
        for (size_t j = i + 1, jEnd = attached_.size(); j < jEnd; ++j)
        {
            const size_t currentOrder = attached_[j]->getOrder();
            if (currentOrder < minimumOrder)
            {
                minimumOrder = currentOrder;
                minIndex = j;
            }
        }
        // swamp minimum with current item
        if (i != minIndex)
        {
            Widget * tmp = attached_[i];
            attached_[i] = attached_[minIndex];
            attached_[minIndex] = tmp;
        }
    }
}

void Container::moveByChildren(const int dx, const int dy)
{
    for (Widget * widget : attached_)
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

    for (auto it = attached_.rbegin(); it != attached_.rend(); ++it)
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
    for (Widget * widget : attached_)
    {
        if (widget)
        {
            widget->setDebugView(value);
        }
    }
    Widget::setDebugView(value);
}


} // stren