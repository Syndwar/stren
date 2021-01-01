#include "game/game.h"

#include "engine/engine_handler.h"
#include "engine/logger.h"
#include "widgets/screen.h"

namespace stren
{
Game::Game()
{
    Logger("green") << "[Game] Initilize main camera";
    m_camera.moveTo(0, 0);
    m_camera.resize(EngineHandler::getScreenWidth(), EngineHandler::getScreenHeight());
}

Game::~Game()
{
    m_screenSelector.release();
}

void Game::update(const size_t dt)
{
    m_screenSelector.update();

    if (Screen * currentScreen = getCurrentScreen())
    {
        currentScreen->update(dt);
    }
}

Screen * Game::getCurrentScreen()
{
    return m_screenSelector.getCurrentScreen();
}

void Game::processEvent(const Event & event, bool & isEventCaptured)
{
    if (Screen * currentScreen = getCurrentScreen())
    {
        currentScreen->processEvent(event, isEventCaptured);
    }
}

void Game::render()
{
    m_camera.place();
    if (Screen * currentScreen = getCurrentScreen())
    {
        m_camera.render(currentScreen);
    }

    m_camera.restore();
}

void Game::switchScreen(Screen * screen)
{
    m_screenSelector.switchToScreen(screen);
}
} // stren