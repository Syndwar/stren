#ifndef STREN_WIDGET_TRANSFORM_MOD_H
#define STREN_WIDGET_TRANSFORM_MOD_H

#include <map>
#include "engine/transform.h"

namespace stren
{
enum EventType;

///
/// class WidgetTransformMod - widget transformation module
///
class WidgetTransformMod
{
public:
    std::map<EventType, Transform> m_transforms;        ///< map of different transformations
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
    void start(const EventType eventType);
    ///
    /// @todo
    ///
    void setTransform(const EventType eventType, const Transform & transform);
    ///
    /// @todo
    ///
    bool isCompleted(const EventType eventType) const;
};
} // stren

#endif // STREN_WIDGET_TRANSFORM_MOD_H
