#ifndef STREN_WIDGET_TRANSFORM_MOD_H
#define STREN_WIDGET_TRANSFORM_MOD_H

#include <map>
#include "engine/transform.h"
#include "engine/event.h"

namespace stren
{
///
/// class WidgetTransformMod - widget transformation module
///
class WidgetTransformMod
{
public:
    std::map<Event, Transform, Event::Compare> m_transforms;        ///< map of different transformations
    ///
    /// @todo
    ///
    void update(const size_t dt);
    ///
    /// @todo
    ///
    void preRender();
    ///
    /// @todo
    ///
    void postRender();
    ///
    /// @todo
    ///
    void start(const Event & event);
    ///
    /// @todo
    ///
    void setTransform(const Event & event, const Transform & transform);
    ///
    /// @todo
    ///
    bool isCompleted(const Event & event) const;
};
} // stren

#endif // STREN_WIDGET_TRANSFORM_MOD_H
