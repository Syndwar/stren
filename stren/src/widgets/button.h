#ifndef STREN_BUTTON_H
#define STREN_BUTTON_H

#include <map>

#include "common/colour.h"
#include "common/delegate.h"
#include "common/point.h"
#include "engine/event.h"
#include "widgets/widget.h"
#include "render/clabel.h"

namespace stren
{
class Sprite;
///
/// class Button
///
class Button : public Widget
{
private:

    enum class ViewState
    {
        Up = 0,
        Over,
        Pressed,
    };                                                              ///< @todo

    static const size_t kSpritesCount = 3;                          ///< @todo

    int                                 m_textAlignment;             ///< @todo
    int                                 m_flip;                      ///< @todo
    double                              m_angle;                     ///< @todo
    ViewState                           m_viewState;                 ///< @todo
    CLabel                              m_label;                     ///< @todo
    Point                               m_center;                    ///< @todo
    std::vector<Sprite>                 m_sprites;                   ///< @todo
    std::vector<std::string>            m_spriteIds;                 ///< @todo

public:
    ///
    /// Constructor:
    ///
    Button(const std::string & id = String::kEmpty);
    ///
    /// Destructor:
    ///
    ~Button();
    ///
    /// @todo
    ///
    inline void setAngle(const double angle) { m_angle = angle; }
    ///
    /// @todo
    ///
    inline double getAngle() const { return m_angle; }
    ///
    /// @todo
    ///
    void setFlip(const bool fliph, const bool flipv);
    ///
    /// @todo
    ///
    inline int getFlip() const { return m_flip; }
    ///
    /// @todo
    ///
    void setSprites(const std::string & upSpr, const std::string & downSpr, const std::string & overSpr, const std::string & disSpr = String::kEmpty);
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
    ///
    /// process incoming system events, mark isEventCaptured true if the event was processed, otherwise - mark false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
private:
    ///
    /// @todo
    ///
    inline void setFlip(const int flip) { m_flip = flip; }
    ///
    /// @todo
    ///
    virtual void doRender() override;
    ///
    /// @todo
    ///
    void loadSprites();
    ///
    /// @todo
    ///
    size_t getTextureIndex() const;
};
}// stren

#endif // STREN_BUTTON_H
