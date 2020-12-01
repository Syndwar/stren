#ifndef STREN_MEMORY_CONTROLLER_H
#define STREN_MEMORY_CONTROLLER_H

#include <map>

namespace stren
{
class Widget;
///
/// class MemoryController
///
class MemoryController
{
private:
    std::map<size_t, Widget *> m_content;
public:
    ///
    /// Constructor
    ///
    MemoryController();
    ///
    /// Destructor
    ///
    ~MemoryController();
};
} // stren

#endif // !STREN_MEMORY_CONTROLLER_H
