#include "widgets/mods/widget_transform_mod.h"

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

void WidgetTransformMod::start(const Event & event)
{
    auto it = m_transforms.find(event);
    if (it != m_transforms.end())
    {
        it->second.start();
    }
}

void WidgetTransformMod::setTransform(const Event & event, const Transform & transform)
{
    m_transforms[event] = transform;
}

bool WidgetTransformMod::isCompleted(const Event & event) const
{
    auto it = m_transforms.find(event);
    if (it != m_transforms.end())
    {
        return it->second.finished();
    }
    return true;
}
} // stren