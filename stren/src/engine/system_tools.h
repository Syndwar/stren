#ifndef STREN_SYSTEM_TOOLS_H
#define STREN_SYSTEM_TOOLS_H

#include "string_ext.h"

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
    bool m_isReady;
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
    ///
    /// process incoming events
    ///
    void processEvent(const Event & event, bool & isEventCaptured);
};
} // stren

#endif // STREN_SYSTEM_TOOLS_H