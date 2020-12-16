#include "screen_selector.h"

#include "engine/engine_handler.h"
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
        if (m_currentScreen)
        {
            // close current screen
            m_currentScreen->close();
            // if current screen exits - remove it from parent
            m_currentScreen->setParent(nullptr);
        }
        // make next screen current and open it
        m_currentScreen = m_nextScreen;
        m_currentScreen->open();
        m_nextScreen = nullptr;
        EngineHandler::collectGarbage();
    }
}

void ScreenSelector::release()
{
    if (m_currentScreen)
    {
        m_currentScreen->setParent(nullptr);
        m_currentScreen = nullptr;
    }
    if (m_nextScreen)
    {
        m_nextScreen->setParent(nullptr);
        m_nextScreen = nullptr;
    }
}

void ScreenSelector::switchToScreen(Screen * screen)
{
    if (!screen) return;
    // do not create a new screen if next screen not yet switched to
    if (m_nextScreen) return;

    if (screen)
    {
        m_nextScreen = screen;
    }
}
} // stren

