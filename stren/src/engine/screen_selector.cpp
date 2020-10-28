#include "screen_selector.h"

#include "widgets/screen.h"
#include "lua/lua_wrapper.h"

namespace stren
{

ScreenSelector::ScreenSelector()
    : m_currentScreen(nullptr)
    , m_nextScreen(nullptr)
{
}

void ScreenSelector::update()
{
    if (m_nextScreen)
    {
        // close current screen
        if (m_currentScreen)
        {
            m_currentScreen->close();
        }
        // if current screen exits - delete it
        if (m_currentScreen)
        {
            delete m_currentScreen;
        }
        // make next screen current and open it
        m_currentScreen = m_nextScreen;
        m_currentScreen->open();
        m_nextScreen = nullptr;
        // collect lua garbage
        lua::Stack stack;
        stack.collectGarbage();
    }
}

void ScreenSelector::release()
{
    if (m_currentScreen)
    {
        delete m_currentScreen;
        m_currentScreen = nullptr;
    }
    if (m_nextScreen)
    {
        delete m_nextScreen;
        m_nextScreen = nullptr;
    }
}

void ScreenSelector::switchToScreen(void * screen)
{
    if (!screen) return;
    // do not create a new screen if next screen not yet switched to
    if (m_nextScreen) return;

    Screen * newScreen = (Screen *)screen;

    if (newScreen)
    {
        m_nextScreen = newScreen;
    }
}
} // stren

