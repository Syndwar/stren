#ifndef STREN_TEXT_H
#define STREN_TEXT_H

#include "common/colour.h"
#include "render/clabel.h"
#include "widgets/widget.h"

struct SDL_Renderer;

namespace stren
{
///
/// class Label
///
class Label : public Widget
{
private:
    bool            m_ignoreMouse;      ///< @todo
    int             m_textAlignment;    ///< @todo
    CLabel          m_label;            ///< @todo
public:
    ///
    /// Constructor
    ///
    Label(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Label();
    ///
    /// @todo
    ///
    void setColour(const Colour & colour);
    ///
    /// @todo
    ///
    void setFont(const std::string & fontId);
    ///
    /// @todo
    ///
    void setText(const std::string & text);
    ///
    /// @todo
    ///
    const std::string & getText() const;
    ///
    /// @todo
    ///
    void setTextAlignment(const int alignment);
    ///
    /// @todo
    ///
    void setTextAlignment(const std::string & alignment);
    ///
    /// @todo
    ///
    void setWrap(const bool value);
    ///
    /// @todo
    ///
    void ignoreMouse(const bool value) { m_ignoreMouse = value; }
    ///
    /// is called when widget position has changed
    ///
    virtual void doPostMove(const int dx, const int dy) override;
    ///
    /// is called when widget size has changed
    ///
    virtual void doPostResize(const int dw, const int dh) override;
    ///
    /// process incoming system events, mark isEventCaptured true if the event was processed, otherwise - mark false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
    ///
    /// @todo
    ///
    static void bind();
private:
    ///
    /// @todo
    ///
    virtual void doRender() override;
};
} // stren

#endif
