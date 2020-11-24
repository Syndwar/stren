#ifndef STREN_TEXT_EDIT_H
#define STREN_TEXT_EDIT_H

#include "widgets/widget.h"
#include "render/clabel.h"

namespace stren
{
///
/// class TextEdit
///
class TextEdit : public Widget
{
private:
    int                 m_textAlignment;    ///< @todo
    bool                m_isInputMode;      ///< @todo
    CLabel              m_label;            ///< @todo
public:
    ///
    /// Constructor
    ///
    TextEdit(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~TextEdit();
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
    void enableInputMode();
    ///
    /// @todo
    ///
    void cancelInputMode();
    ///
    /// @todo
    ///
    bool isInputMode() const;
    ///
    /// @todo
    ///
    virtual void doPostMove(const int dx, const int dy) override;
    ///
    /// @todo
    ///
    static void bind();
    ///
    /// process incoming system events, mark isEventCaptured true if the event was processed, otherwise - mark false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
private:
    ///
    /// @todo
    ///
    virtual void doRender() override;
};
}
#endif // STREN_TEXT_EDIT_H
