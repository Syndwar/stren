#ifndef STREN_TIMER_H
#define STREN_TIMER_H

#include "widget.h"

namespace stren
{
///
/// class Timer
///
class Timer : public Widget
{
private:
    enum class WorkState
    {
        Stopped = 0,
        Running,
        Paused,
        Elapsed,
    };                                   ///< @todo

    size_t      m_time;                  ///< @todo
    size_t      m_workTime;              ///< @todo
    WorkState   m_workState;             ///< @todo

public:
    ///
    /// Constructor
    ///
    Timer(const std::string & id = String::kEmpty);
    ///
    /// Constructor
    ///
    Timer(const size_t ms);
    ///
    /// Destructor
    ///
    virtual ~Timer();
    ///
    /// start the timer
    ///
    void start();
    ///
    /// stop the timer
    ///
    void stop();
    ///
    /// restart the timer with new time
    ///
    void restart(const size_t ms);
    ///
    /// pause the timer
    ///
    void pause();
    ///
    /// resume the timer
    ///
    void resume();
    ///
    /// return time that was set as desired delay
    ///
    inline size_t time() const { return m_time; }
    ///
    /// is timer elapsed
    ///
    inline bool isElapsed() const { return WorkState::Elapsed == m_workState; }
    ///
    /// was timer stopped
    ///
    inline bool isStopped() const { return WorkState::Stopped == m_workState; }
    ///
    /// is timer paused
    ///
    inline bool isPaused() const { return WorkState::Paused == m_workState; }
    ///
    /// is timer running
    ///
    inline bool isRunning() const { return WorkState::Running == m_workState; }
    ///
    /// update timer every frame
    ///
    virtual void update(const size_t dt) override;
    ///
    /// close/open widget with transformation
    ///
    virtual void view(const bool value) override {}
    ///
    /// close/open widget instantly
    ///
    virtual void instantView(const bool value) override {}
    ///
    /// show widget with transformation
    ///
    virtual void open() override {}
    ///
    /// hide widget with transformation
    ///
    virtual void close() override {}
    ///
    /// show widget instantly
    ///
    virtual void instantOpen() override {}
    /// hide widget instantly
    ///
    virtual void instantClose() override {}
    ///
    /// render widget every frame
    ///
    virtual bool render() override { return false; }
    ///
    /// returns if widget is closed
    ///
    virtual bool isClosed() const override { return false; }
    ///
    /// returns if widget is opened
    ///
    virtual bool isOpened() const override { return true; }
    ///
    /// move widget to a new position
    ///
    virtual void moveTo(const int x, const int y) override {}
    ///
    /// move widget to a new position using offset
    ///
    virtual void moveBy(const int dx, const int dy) override {}
    ///
    /// set alignment method
    ///
    virtual void setAlignment(const int alignment, const int dx = 0, const int dy = 0) override {}
    ///
    /// set alignment method
    ///
    virtual void setAlignment(const std::string & alignment, const int dx = 0, const int dy = 0) override {}
    ///
    /// attach transform to the widget, takes ownership of the transform
    ///
    virtual void attachTransform(const EventType eventType, const Transform & transform) override {}
};
} // stren
#endif // STREN_TIMER_H
