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
    ///
    /// process incoming system events, mark isEventCaptured true if the event was processed, otherwise - mark false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
};
} // stren

#endif // STREN_SYSTEM_TOOLS_H