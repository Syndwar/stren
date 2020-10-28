#include "widgets/mods/widget_transform_mod.h"

#include "engine/event.h"

namespace stren
{
void WidgetTransformMod::update(const size_t dt)
{
    if (m_transforms.empty()) return;

    for (auto & it : m_transforms)
    {
        it.second.update(dt);
    }
}

void WidgetTransformMod::preRender()
{
    if (m_transforms.empty()) return;

    for (auto & it : m_transforms)
    {
        it.second.apply();
    }
}

void WidgetTransformMod::postRender()
{
    if (m_transforms.empty()) return;

    for (auto & it : m_transforms)
    {
        it.second.restore();
    }
}

void WidgetTransformMod::start(const EventType eventType)
{
    auto it = m_transforms.find(eventType);
    if (it != m_transforms.end())
    {
        it->second.start();
    }
}

void WidgetTransformMod::setTransform(const EventType eventType, const Transform & transform)
{
    m_transforms[eventType] = transform;
}

bool WidgetTransformMod::isCompleted(const EventType eventType) const
{
    auto it = m_transforms.find(eventType);
    if (it != m_transforms.end())
    {
        return it->second.finished();
    }
    return true;
}
} // stren