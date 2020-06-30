#ifndef STREN_CONTAINER_H
#define STREN_CONTAINER_H

#include <vector>

#include "widget.h"
#include "utils.h"

namespace stren
{
///
/// class Container
///
class Container : public Widget
{
private:
    std::vector<Widget *>            attached_; ///< @todo
    std::map<std::string, Widget *>  map_;      ///< @todo

public:
    ///
    /// Constructor
    ///
    Container(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Container();
    ///
    /// @todo
    ///
    template <typename _T>
    _T * findWidget(const std::string & id)
    {
        std::vector<std::string> values;
        tokenize(id.c_str(), values, ".");

        Widget * parent(nullptr);
        for (const std::string & value : values)
        {
            if (!parent)
            {
                auto it = map_.find(value);
                if (it != map_.end())
                {
                    if (it->second)
                    {
                        parent = it->second;
                    }
                }
            }
            else if (Container * container = dynamic_cast<Container *>(parent))
            {
                parent = container->findWidget<Widget>(value);
            }
            else
            {
                return nullptr;
            }
        }

        return dynamic_cast<_T *>(parent);
    }
    ///
    /// attach widget to some container, takes ownership
    ///
    virtual void attach(Widget * widget);
    ///
    /// detach widgets from the container
    ///
    void detachAll();
    ///
    /// @todo
    ///
    virtual void setDebugView(const bool value) override;
    ///
    /// process incoming system events, returns true if the event was processed, otherwise - returns false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
    ///
    /// returns attached widgets list
    ///
    const std::vector<Widget *> & debugGetAttached() { return attached_; }
protected:
    ///
    /// custom code that should be called in the child widget during the rendering
    ///
    virtual void doRender() override;
    ///
    /// custom code that should be called in the child widget during the update
    ///
    virtual void doUpdate(const size_t dt) override;
    ///
    /// is called when widget position has changed
    ///
    virtual void doPostMove(const int dx, const int dy) override;
private:
    ///
    /// @todo
    ///
    void moveByChildren(const int dx, const int dy);
    ///
    /// @todo
    ///
    void sortChildren();
};
} // stren
#endif // STREN_CONTAINER_H
