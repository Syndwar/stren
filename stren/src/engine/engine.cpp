#include "engine.h"

#include <ctime>

#include "SDL.h"

#include "event.h"
#include "logger.h"
#include "lua_wrapper.h"
#include "lua_binding.h"

#include "renderer.h"
#include "console.h"
#include "widgets/screen.h"
#include "game/game.h"

namespace stren
{
const size_t Engine::kFramesAmount = 30;

Engine::Engine()
    : m_status(Status::Stopped)
    , m_fpsLimit(60)
    , m_frameTimeLimit(17)
    , m_lastFrameTime(0)
    , m_frameIndex(0)
    , m_game(nullptr)
{
    m_frameTimeHistory.resize(kFramesAmount);
    Logger("green") << "[Engine] Engine created";
}

Engine::~Engine()
{
    if (m_game)
    {
        delete m_game;
        m_game = nullptr;
    }
}

void Engine::process()
{
    // save frame start time
    const size_t dt = SDL_GetTicks() - m_lastFrameTime;
    m_lastFrameTime = SDL_GetTicks();

    processEvents();
    update(dt);
    render();
    postRender();
    wait();
}

void Engine::postRender()
{
    m_screenSelector.update();
}

bool Engine::init()
{
    bool isSuccess{ false };

    Logger("green") << "[Engine] Initialize Lua";
    lua::Stack stack;
    stack.loadScript("base/scripts/main.lua");
    lua::Function("main").call();

    Logger("green") << "[Engine] Deserialize save data";
    deserialize();

    Logger("green") << "[Engine] Create config";
    m_config.initialize(m_saveData);
    Logger("green") << "[Engine] Load config settings";
    loadConfig();

    Logger("green") << "[Engine] Initialize SDL";
    isSuccess = 0 == SDL_Init(SDL_INIT_EVERYTHING);
    if (!isSuccess) return false;

    const int screenWidth = m_config.getScreenWidth();
    const int screenHeight = m_config.getScreenHeight();
    Logger("green") << "[Engine] Create application window";
    AppWindowConfig appWindowConfig;
    appWindowConfig.title = m_config.getTitle();
    appWindowConfig.screenWidth = screenWidth;
    appWindowConfig.screenHeight = screenHeight;
    appWindowConfig.isFullscreen = m_config.isFullscreen();
    appWindowConfig.isBorderless = m_config.isBorderless();
    isSuccess = m_appWindow.initialize(appWindowConfig);
    if (!isSuccess) return false;

    isSuccess = createRenderer();
    if (!isSuccess) return false;

    m_fontsRepo.initialize();

    Logger("green") << "[Engine] Initialize texts repository";
    m_textsRepo.initialize();

    Logger("green") << "[Engine] Initialize sprites repository";
    m_spritesRepo.initialize();

    Logger("green") << "[Engine] Initialize textures repository";
    m_texturesRepo.initialize();

    Logger("green") << "[Engine] Initialize sounds system";
    m_soundSystem.initialize();

    Logger("green") << "[Engine] Initilize main camera";
    m_camera.moveTo(0, 0);
    m_camera.resize(screenWidth, screenHeight);
    
    Logger("green") << "[Engine] Initialize system tools";
    m_systemTools.initialize();

    Logger("green") << "[Engine] Everything initialized successfully, start main loop";
    m_status = Status::Running;

    return true;
}

void Engine::consoleLog(const std::string & message)
{
    m_systemTools.log(message);
}

void Engine::createGame()
{
    lua::bindWithVM();
    switchScreen(ScreenId::StartScreen);
    if (!m_game)
    {
        m_game = new Game();
    }
}

void Engine::switchScreen(const ScreenId id)
{
    m_screenSelector.switchToScreen(id);
}

Screen * Engine::getCurrentScreen()
{
    return m_screenSelector.getCurrentScreen();
}

const Point & Engine::getMousePos()
{
    return m_eventProcessor.getMousePos();
}

void Engine::goToScreen(Widget * screen)
{
}

void Engine::loadConfig()
{
    m_fpsLimit = m_config.getFpsLimit();
    if (m_fpsLimit > 0)
    {
        m_frameTimeLimit = 1000 / m_fpsLimit;
    }
}

void Engine::wait()
{
    const int frameTime = SDL_GetTicks() - m_lastFrameTime;
    if (m_fpsLimit > 0)
    {
        const int timeToWait = m_frameTimeLimit - frameTime;

        if (timeToWait > 0)
        {
            SDL_Delay(timeToWait);
        }
    }
    // save frame actual time
    m_frameTimeHistory[m_frameIndex] = frameTime;

    ++m_frameIndex;
    if (m_frameIndex >= kFramesAmount)
    {
        m_frameIndex = 0;
    }
}

size_t Engine::getFPS() const
{
    size_t frameSumm{ 0 };
    for (const size_t frameTime : m_frameTimeHistory)
    {
        frameSumm += (frameTime > 0) ? frameTime : 1;
    }
    if (frameSumm > 0)
    {
        return 1000 * kFramesAmount / frameSumm;
    }
    return 1;
}

void Engine::render()
{
    static const Colour colourData(Colour::Black);
    Renderer::setRenderColour(colourData);
    Renderer::clear();

    if (Screen * currentScreen = m_screenSelector.getCurrentScreen())
    {
        m_camera.render(currentScreen);
    }
    m_systemTools.render();

    Renderer::render();
}

void Engine::update(const size_t dt)
{
    if (m_game)
    {
        m_game->update(dt);
    }

    if (Screen * currentScreen = m_screenSelector.getCurrentScreen())
    {
        currentScreen->update(dt);
    }
    m_systemTools.update(dt);
}

void Engine::processEvents()
{
    while (true)
    {
        const Event & event = m_eventProcessor.getEvent();
        
        if (!event.isValid()) break;
        if (event.isUnknown()) continue;

        bool isEventCaptured(false); // is event captured by some widget

        switch (event.type)
        {
            case EventType::SysQuit:
            {
                stop();
            }
            break;

            default:
            break;
        }

        m_systemTools.processEvent(event, isEventCaptured);

        if (Screen * currentScreen = m_screenSelector.getCurrentScreen())
        {
            currentScreen->processEvent(event, isEventCaptured);
        }
    }
}

void Engine::clean()
{
    // Destroy all widgets before textures repo
    m_screenSelector.release();
    m_systemTools.release();
    // Destroy sprites repo before textures repo
    m_spritesRepo.release();
    m_texturesRepo.release();
    m_fontsRepo.release();
    m_textsRepo.release();
    m_soundSystem.release();
    Renderer::release();
    m_appWindow.release();

    Logger("green") << "[Engine] Quit SDL";
    SDL_Quit();

    Logger("green") << "[Engine] Destroy Lua VM";
    lua::Stack().destroy();
}

bool Engine::createRenderer()
{
    Logger("green") << "[Engine] Create SDL renderer";
    if (Renderer::initialize(m_appWindow, m_config.isVSync()))
    {
        Logger("green") << "[Engine] Set SDL render color";
        static const Colour colour_data(Colour::Black);
        Renderer::setRenderColour(colour_data);
        const int screenWidth = m_config.getScreenWidth();
        const int screenHeight = m_config.getScreenHeight();
        const Rect clippingRect(0, 0, screenWidth, screenHeight);
        Renderer::setClippingRect(clippingRect);
        return true;
    }

    return false;
}

const std::string & Engine::getTextByAlias(const std::string & alias)
{
    return m_textsRepo.getText(alias);
}

Sprite * Engine::getSprite(const std::string & spriteId)
{
    return m_spritesRepo.getSprite(spriteId);
}

ITexture * Engine::getTexture(const std::string & textureId)
{
    ITexture * texture = m_texturesRepo.getTexture(textureId);
    if (!texture)
    {
        texture = m_fontsRepo.getTexture(textureId);
    }
    return texture;
}

void Engine::serialize()
{
    m_saveData.serialize();
}

void Engine::deserialize()
{
    m_saveData.deserialize();
}
} // stren