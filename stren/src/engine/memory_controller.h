#ifndef STREN_MEMORY_CONTROLLER_H
#define STREN_MEMORY_CONTROLLER_H

#include <map>
#include <vector>

namespace stren
{
class Widget;
///
/// class MemoryController
///
class MemoryController
{
private:
    size_t                     m_counter; ///< @todo
    std::map<size_t, Widget *> m_content; ///< @todo
    std::vector<size_t> removeList;
public:
    ///
    /// Constructor
    ///
    MemoryController();
    ///
    /// Destructor
    ///
    ~MemoryController();
    ///
    /// Store widget and return the handle
    ///
    size_t store(Widget * widget);
    ///
    /// Get widget from storage using handle key
    ///
    template<typename T>
    T get(const size_t handle)
    {
        auto it = m_content.find(handle);
        if (it != m_content.end())
        {
            return dynamic_cast<T>(it->second);
        }
        return nullptr;
    }
    ///
    /// Check if some widgets are dead and delete them
    ///
    void collectGarbage();
    ///
    /// Delete all widgets from storage
    ///
    void release();
};
} // stren

#endif // !STREN_MEMORY_CONTROLLER_H
