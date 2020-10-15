#ifndef STREN_TEXT_H
#define STREN_TEXT_H

#include "colour.h"
#include "clabel.h"
#include "widget.h"

struct SDL_Renderer;

namespace stren
{
///
/// class Label
///
class Label : public Widget
{
private:
    int             textAlignment_;    ///< @todo
    CLabel          label_;            ///< @todo
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
    virtual void doPostMove(const int dx, const int dy) override;
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
