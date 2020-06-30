#ifndef STREN_TEST_OBSERVER_H
#define STREN_TEST_OBSERVER_H

#include "event_listener.h"
#include "observer.h"
#include "event.h"

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
            A()
                : Observer(nullptr)
            {
            }

            virtual ~A() {}

            virtual bool notify(const Event & event) override { return true; }
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

            B(EventListener * listener = nullptr)
                : Observer(listener, { EventType::SysQuit })
            {
            }

            virtual ~B() {}

            virtual bool notify(const Event & event) override
            {
                ++i;
                return true;
            }
        };

        {
            B b1;
        }

        {
            B b2(&listener);
            listener.notify(event);
            stren::assertMessage(0 == b2.i, "Error");
            event.type = EventType::SysQuit;
            listener.notify(event);
            stren::assertMessage(1 == b2.i, "Error");
        }
    }
};

} // test

#endif // STREN_TEST_OBSERVER_H
