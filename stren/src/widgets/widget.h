#ifndef STREN_WIDGET_H
#define STREN_WIDGET_H

#include <memory>

#include "common/alignment.h"
#include "common/point.h"
#include "common/rect.h"
#include "engine/listener.h"
#include "widgets/mods/widget_transform_mod.h"

namespace stren
{
class Event;
class PrimitiveRect;

///
/// base Widget class for engine entities
///
class Widget : public Listener
{
protected:
    enum class ViewState
    {
        Opened = 0,
        Opening = 1,
        Closing = 2,
        Closed,
    };

    enum UpdateState
    {
        Update = 0x00000001,
        Align = 0x00000002,
    };
private:
    std::string                         m_id;                ///< widgets id
    Rect                                m_rect;              ///< objects rectangle
    Point                               m_alignmentOffset;   ///< @todo
    ViewState                           m_viewState;         ///< widget state; Default - State::Type::Open
    Widget *                            m_parent;            ///< pointer to the widget this widget is attached to; Default - nullptr
    size_t                              m_order;             ///< order of the widget in the container; Default - 0
    int                                 m_updateState;       ///< widget update state; Default - State::Type::Update
    int                                 m_alignment;         ///< @todo
    WidgetTransformMod                  m_transform;         ///< widget transformation module
    bool                                m_debugView;         ///< debug view that draws rectangles over widget position
    std::unique_ptr<PrimitiveRect>      m_debugRect;         ///< @todo
public:
    ///
    /// Constructor
    ///
    Widget(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Widget();
    ///
    /// get widget id
    ///
    const std::string & getId() const { return m_id; }
    ///
    /// get object to which widget is attached
    ///
    Widget * getParent() const { return m_parent; }
    ///
    /// set object to which widget is attached
    ///
    void setParent(Widget * parent) { m_parent = parent; }
    ///
    /// returns widget order
    ///
    size_t getOrder() const { return m_order; }
    ///
    /// change widget order
    ///
    void setOrder(const size_t order) { m_order = order; }
    ///
    /// get widget rectangle
    ///
    const Rect & getRect() const { return m_rect; }
    ///
    /// set widget rectangle
    ///
    void setRect(const int x, const int y, const int w, const int h);
    ///
    /// set widget rectangle
    ///
    void setRect(const Rect & rect);
    ///
    /// close/open widget
    ///
    virtual void view(const bool value);
    ///
    /// close/open widget instantly
    ///
    virtual void instantView(const bool value);
    ///
    /// hide widget
    ///
    virtual void close();
    ///
    /// show widget
    ///
    virtual void open();
    ///
    /// move widget to a new position
    ///
    virtual void moveTo(const int x, const int y);
    ///
    /// move widget to a new position using offset
    ///
    virtual void moveBy(const int dx, const int dy);
    ///
    /// show widget instantly
    ///
    virtual void instantOpen();
    ///
    /// hide widget instantly
    ///
    virtual void instantClose();
    ///
    /// update widget every frame
    ///
    virtual void update(const size_t dt);
    ///
    /// returns if widget is closed
    ///
    virtual bool isClosed() const;
    ///
    /// returns if widget is opened
    ///
    virtual bool isOpened() const;
    ///
    /// attach transform to the widget
    ///
    virtual void attachTransform(const EventType eventType, const Transform & transform);
    ///
    /// @todo
    ///
    virtual bool render();
    ///
    /// set alignment method
    ///
    virtual void setAlignment(const int alignment, const int dx = 0, const int dy = 0);
    ///
    /// set alignment method
    ///
    virtual void setAlignment(const std::string & alignment, const int dx = 0, const int dy = 0);
    ///
    /// return widget alignment
    ///
    virtual int getAlignment() const { return m_alignment; }
    ///
    /// process incoming system events, mark isEventCaptured true if the event was processed, otherwise - mark false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) {}
    ///
    /// enables drawing debug rectangles around the widgets
    ///
    virtual void setDebugView(const bool value) { m_debugView = value; }
    ///
    /// returns if debug view is enabled
    ///
    virtual bool isDebugView() const { return m_debugView; }
    ///
    /// @todo
    ///
    static void bind();
protected:
    ///
    /// @todo
    ///
    inline void setState(const ViewState state) { m_viewState = state; }
    ///
    /// @todo
    ///
    inline ViewState getState() const { return m_viewState; }
    ///
    /// @todo
    ///
    inline void addUpdateState(const int state) { m_updateState |= state; }
    ///
    /// @todo
    ///
    inline void removeUpdateState(const int state) { m_updateState &= ~state; }
    ///
    /// @todo
    ///
    inline bool hasUpdateState(const int state) { return 0 != (m_updateState & state); }
    ///
    /// is called when widget position has changed
    ///
    virtual void doPostMove(const int dx, const int dy) {}
    ///
    /// custom code that should be called in the child widget before the rendering
    ///
    virtual void doPreRender();
    ///
    /// custom code that should be called in the child widget after the rendering
    ///
    virtual void doPostRender();
    ///
    /// custom code that should be called in the child widget during the rendering
    ///
    virtual void doRender() {}
    ///
    /// custom code that should be called in the child widget during the update
    ///
    virtual void doUpdate(const size_t dt) {}
    ///
    /// custom code that should be called in the child widget during the opening
    ///
    virtual void doOpen() {}
    ///
    /// custom code that should be called in the child widget during the closing
    ///
    virtual void doClose() {}
private:
    ///
    /// align widget on the screen
    ///
    void align();
    ///
    /// @todo
    ///
    void doDebugRender();
    ///
    /// @todo
    ///
    void updateViewState();
    ///
    /// @todo
    ///
    bool isTransformCompleted(const EventType eventType) const;
    ///
    /// @todo
    ///
    void startTransform(const EventType eventType);
};
} // stren

#endif // STREN_WIDGET_H
