#include "screen_selector.h"

#include "lua_stack.h"

#include "screens/start_screen.h"
#include "screens/main_screen.h"
#include "screens/options_screen.h"
#include "screens/map_editor_screen.h"
#include "screens/test_screen.h"
#include "screens/test_font_screen.h"
#include "screens/test_sound_screen.h"
#include "screens/test_primitive_screen.h"
#include "screens/test_fader_screen.h"
#include "screens/test_scroll_screen.h"
#include "screens/test_widgets_screen.h"
#include "screens/test_atlas_screen.h"
#include "screens/test_battle_field_screen.h"
#include "widgets/screen.h"

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
        m_nextScreen->close();
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

void ScreenSelector::switchToScreen(const ScreenId & id)
{
    // do not create a new screen if next screen not yet switched to
    if (m_nextScreen) return;

    Screen * newScreen(nullptr);

    switch (id)
    {
    case ScreenId::StartScreen:
    {
        newScreen = new StartScreen();
    }
    break;
    case ScreenId::MainScreen:
    {
        newScreen = new MainScreen();
    }
    break;
    case ScreenId::OptionsScreen:
    {
        newScreen = new OptionsScreen();
    }
    break;
    case ScreenId::MapEditorScreen:
    {
        newScreen = new MapEditorScreen();
    }
    break;
    case ScreenId::TestScreen:
    {
        newScreen = new TestScreen();
    }
    break;
    case ScreenId::TestFontScreen:
    {
        newScreen = new TestFontScreen();
    }
    break;
    case ScreenId::TestSoundScreen:
    {
        newScreen = new TestSoundScreen();
    }
    break;
    case ScreenId::TestAtlasScreen:
    {
        newScreen = new TestAtlasScreen();
    }
    break;
    case ScreenId::TestFaderScreen:
    {
        newScreen = new TestFaderScreen();
    }
    break;
    case ScreenId::TestPrimitiveScreen:
    {
        newScreen = new TestPrimitiveScreen();
    }
    break;
    case ScreenId::TestScrollScreen:
    {
        newScreen = new TestScrollScreen();
    }
    break;
    case ScreenId::TestWidgetsScreen:
    {
        newScreen = new TestWidgetsScreen();
    }
    break;
    case ScreenId::TestBattlefieldScreen:
    {
        newScreen = new TestBattleFieldScreen();
    }
    break;
    }

    if (newScreen)
    {
        m_nextScreen = newScreen;
    }
}
} // stren

