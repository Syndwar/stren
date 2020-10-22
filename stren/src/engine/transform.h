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
    int     m_value; ///< @todo
    size_t  m_time;  ///< @todo
public:
    ///
    /// Constructor
    ///
    TransformStep()
        : m_value(0)
        , m_time(0)
    {
    }
    ///
    /// Constructor
    ///
    TransformStep(const int value, const size_t time)
        : m_value(value)
        , m_time(time)
    {
    }
    ///
    /// @todo
    ///
    inline int getValue() const { return m_value; }
    ///
    /// @todo
    ///
    inline size_t getTime() const { return m_time; }
    ///
    /// @todo
    ///
    inline void set(const int value, const size_t time)
    {
        m_value = value;
        m_time = time;
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
    ///
    /// free transform resources
    ///
    void free();
    ///
    /// @todo
    ///
    static void bind();
};
} // stren

#endif // STREN_TRANSFORM_H
