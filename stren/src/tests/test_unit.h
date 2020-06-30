#ifndef STREN_TEST_UNIT_H
#define STREN_TEST_UNIT_H

#include "test_lua.h"
#include "test_observer.h"
#include "test_color.h"
#include "test_widgets.h"

namespace test
{

void run()
{
    LuaVirtualMachine   m_luaTest;
    StrenObserver       m_oberserTest;
    StrenColour         m_colourTest;
    Widgets             m_widgetsTest;
}

} // test

#endif // STREN_TEST_UNIT_H
