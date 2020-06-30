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
    };                                       ///< @todo
private:
    int          currentValue_;              ///< @todo
    int          maxValue_;                  ///< @todo
    int          fillSpeed_;                 ///< @todo
    int          updateInterval_;            ///< @todo
    int          targetValue_;               ///< @todo
    Type         type_;                      ///< @todo
    Sprite       sprite_;                    ///< @todo

    std::string  spriteId_;                  ///< @todo
    Point        center_;                    ///< center of the texture
    Timer        timer_;                     ///< @todo
    Camera       camera_;                    ///< @todo
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
    inline void setType(Type type) { type_ = type; }
    ///
    /// @todo
    ///
    void setVertical(const bool value);
    ///
    /// @todo
    ///
    inline void setSprite(const std::string & spriteId) { spriteId_ = spriteId; }
    ///
    /// @todo
    ///
    inline void setMaxValue(const int value) { maxValue_ = value; }
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
    inline int getMaxValue() const { return maxValue_; }
    ///
    /// @todo
    ///
    inline int getCurrentValue() const { return currentValue_; }
    ///
    /// @todo
    ///
    void windTo(const int value);
    ///
    /// @todo
    ///
    bool isWinding() const;
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
