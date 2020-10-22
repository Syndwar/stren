#ifndef STREN_PROGRESSBAR_H
#define STREN_PROGRESSBAR_H

#include "widget.h"
#include "sprite.h"
#include "timer.h"
#include "camera.h"

namespace stren
{
///
/// class ProgressBar
///
class ProgressBar : public Widget
{
public:
    enum Type {
        Vertical,
        Horizontal
    };                                        ///< @todo
private:
    int          m_currentValue;              ///< @todo
    int          m_maxValue;                  ///< @todo
    int          m_fillSpeed;                 ///< @todo
    int          m_updateInterval;            ///< @todo
    int          m_targetValue;               ///< @todo
    Type         m_type;                      ///< @todo
    Sprite       m_sprite;                    ///< @todo

    std::string  m_spriteId;                  ///< @todo
    Point        m_center;                    ///< center of the texture
    Timer        m_timer;                     ///< @todo
    Camera       m_camera;                    ///< @todo
public:
    ///
    /// Constructor
    ///
    ProgressBar(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~ProgressBar();
    ///
    /// @todo
    ///
    inline void setType(Type type) { m_type = type; }
    ///
    /// @todo
    ///
    void setVertical(const bool value);
    ///
    /// @todo
    ///
    inline void setSprite(const std::string & spriteId) { m_spriteId = spriteId; }
    ///
    /// @todo
    ///
    inline void setMaxValue(const int value) { m_maxValue = value; }
    ///
    /// @todo
    ///
    void setCurrentValue(const int value);
    ///
    /// @todo
    ///
    void setFillSpeed(const int speed);
    ///
    /// @todo
    ///
    inline int getMaxValue() const { return m_maxValue; }
    ///
    /// @todo
    ///
    inline int getCurrentValue() const { return m_currentValue; }
    ///
    /// @todo
    ///
    void windTo(const int value);
    ///
    /// @todo
    ///
    bool isWinding() const;
    ///
    /// @todo
    ///
    static void bind();
private:
    ///
    /// @todo
    ///
    void loadSprite();
    ///
    /// rendering of the progressbar
    ///
    virtual void doRender() override;
    ///
    /// update progressbar
    ///
    virtual void doUpdate(const size_t dt) override;
};
}
#endif // STREN_PROGRESSBAR_H
