#ifndef STREN_SYSTEM_TOOLS_H
#define STREN_SYSTEM_TOOLS_H

#include "common/string_ext.h"
#include "widgets/container.h"

namespace stren
{
class Event;
///
/// class SystemTools
///
class SystemTools : public Container
{
private:
    size_t m_actionKey; ///< @todo
    bool   m_isReady;   ///< @todo
public:
    ///
    /// Constructor
    ///
    SystemTools();
    ///
    /// Destructor
    ///
    virtual ~SystemTools();
    ///
    /// initialize module
    ///
    void initialize();
    ///
    /// free resources
    ///
    void release();
    ///
    /// log to console
    ///
    void log(const std::string & message);
};
} // stren

#endif // STREN_SYSTEM_TOOLS_H