#ifndef STREN_BATTLEFIELD_H
#define STREN_BATTLEFIELD_H

#include "widgets/scroll_container.h"

namespace stren
{
///
/// class Battlefield provides an ability to place units and objects and interact with them
///
class Battlefield : public ScrollContainer
{
public:
    ///
    /// Constructor
    ///
    Battlefield(const std::string & id = String::kEmpty);
    ///
    /// Destructor
    ///
    virtual ~Battlefield();
    ///
    /// process incoming system events, returns true if the event was processed, otherwise - returns false to let other widget to process it
    ///
    virtual void processEvent(const Event & event, bool & isEventCaptured) override;
};
} // stren
#endif // STREN_BATTLEFIELD_H
