#ifndef STREN_TEST_OBSERVER_H
#define STREN_TEST_OBSERVER_H

#include "engine/event_listener.h"
#include "engine/observer.h"
#include "engine/event.h"

using namespace stren;

namespace test
{
///
/// class StrenObserver
///
class StrenObserver
{
public:
    ///
    /// Constructor
    ///
    StrenObserver()
    {
        Event event;
        EventListener listener;
        ///
        /// class A
        ///
        class A : public Observer
        {
        public:
            A() : Observer()
            {
            }

            virtual ~A() {}

            virtual void notify(const Event & event, bool & isEventCaptured) override {}
        };

        {
            A a;
        }
        ///
        /// class B
        ///
        class B : public Observer
        {
        public:
            int i = 0;

            B() : Observer({ EventType::SysQuit })
            {
            }

            virtual ~B() {}

            virtual void notify(const Event & event, bool & isEventCaptured) override
            {
                ++i;
            }
        };

        {
            B b1;
        }

        {
            bool isEventCaptured(false);
            B b2;
            listener.add(&b2);
            listener.notify(event, isEventCaptured);
            stren::assertMessage(0 == b2.i, "Error");
            event.type = EventType::SysQuit;
            listener.notify(event, isEventCaptured);
            stren::assertMessage(1 == b2.i, "Error");
            listener.remove(&b2);
        }
    }
};

} // test

#endif // STREN_TEST_OBSERVER_H
