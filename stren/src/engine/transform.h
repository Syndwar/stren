#ifndef STREN_TRANSFORM_H
#define STREN_TRANSFORM_H

#include <vector>
namespace stren
{
///
/// class TransformStep
///
class TransformStep
{
private:
    int     value_; ///< @todo
    size_t  time_;  ///< @todo
public:
    ///
    /// Constructor
    ///
    TransformStep()
        : value_(0)
        , time_(0)
    {
    }
    ///
    /// Constructor
    ///
    TransformStep(const int value, const size_t time)
        : value_(value)
        , time_(time)
    {
    }
    ///
    /// @todo
    ///
    inline int getValue() const { return value_; }
    ///
    /// @todo
    ///
    inline size_t getTime() const { return time_; }
    ///
    /// @todo
    ///
    inline void set(const int value, const size_t time)
    {
        value_ = value;
        time_ = time;
    }
};
///
/// class Transform
///
class Transform
{
private:

    enum class State
    {
        Idle = 0,
        Started,
        Finished,
    };                                              ///< @todo

    State                      m_state;             ///< @todo
    size_t                     m_index;             ///< @todo
    size_t                     m_time;              ///< @todo
    int                        m_preTransformAlpha; ///< @todo
    bool                       m_isDirty;           ///< @todo
    std::vector<TransformStep> m_values;            ///< @todo
public:
    ///
    /// Constructor
    ///
    Transform();
    ///
    /// @todo
    ///
    inline bool finished() const { return m_state == State::Finished;}
    ///
    /// @todo
    ///
    inline bool started() const { return m_state == State::Started; }
    ///
    /// @todo
    ///
    void apply();
    ///
    /// @todo
    ///
    void restore();
    ///
    /// @todo
    ///
    void update(const size_t dt);
    ///
    /// add transformation step that will apply specific transform type from start to end value in given time in ms duration
    ///
    void add(const int start, const int end, const size_t time);
    ///
    /// calculate transformations points
    ///
    void calculate();
    ///
    /// start transformation
    ///
    void start();
    ///
    /// stop transformation
    ///
    void stop();
};
} // stren

#endif // STREN_TRANSFORM_H
