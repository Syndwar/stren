#include "engine.h"

#include <ctime>

#include "SDL.h"

#include "engine/event.h"
#include "engine/logger.h"
#include "game/game.h"
#include "render/renderer.h"
#include "widgets/screen.h"
#include "lua/lua_wrapper.h"
#include "lua/lua_binding.h"

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
}

bool Engine::init()
{
    initScripts();

    const bool isSuccess = initRenderer();
    if (isSuccess)
    {
        initFonts();
        initTexts();
        initSprites();
        initTextures();
        initSound();

        Logger("green") << "[Engine] Everything initialized successfully, start main loop";
        m_status = Status::Running;
    }

    return isSuccess;
}

bool Engine::initRenderer()
{
    Logger("green") << "[Engine] Initialize SDL";
    bool isSuccess = 0 == SDL_Init(SDL_INIT_EVERYTHING);
    if (isSuccess)
    {
        Logger("green") << "[Engine] Create application window";
        AppWindowConfig appWindowConfig;
        appWindowConfig.title = m_config.getTitle();
        appWindowConfig.screenWidth = m_config.getScreenWidth();
        appWindowConfig.screenHeight = m_config.getScreenHeight();
        appWindowConfig.isFullscreen = m_config.isFullscreen();
        appWindowConfig.isBorderless = m_config.isBorderless();
        isSuccess = m_appWindow.initialize(appWindowConfig);
        isSuccess = isSuccess && createRenderer();
    }
    return isSuccess;
}

void Engine::initFonts()
{
    m_fontsRepo.initialize();
}

void Engine::initTexts()
{
    Logger("green") << "[Engine] Initialize texts repository";
    m_textsRepo.initialize();
}

void Engine::initSprites()
{
    Logger("green") << "[Engine] Initialize sprites repository";
    m_spritesRepo.initialize();
}

void Engine::initTextures()
{
    Logger("green") << "[Engine] Initialize textures repository";
    m_texturesRepo.initialize();
}

void Engine::initSound()
{
    Logger("green") << "[Engine] Initialize sounds system";
    m_soundSystem.initialize();
}

void Engine::initScripts()
{
    lua::bindWithVM();

    Logger("green") << "[Engine] Initialize Lua";
    lua::Stack stack;
    stack.loadScript("base/scripts/main.lua");
    lua::Function("main").call();
}

void Engine::createGame()
{
    if (!m_game)
    {
        m_game = new Game();
    }
}

void Engine::switchScreen(void * screen)
{
    if (m_game)
    {
        m_game->switchScreen(screen);
    }
}

Screen * Engine::getCurrentScreen()
{
    if (m_game)
    {
        return m_game->getCurrentScreen();
    }
    return nullptr;
}

const Point & Engine::getMousePos()
{
    return m_eventProcessor.getMousePos();
}

void Engine::initConfig()
{
    Logger("green") << "[Engine] Create config";
    m_config.initialize();
    Logger("green") << "[Engine] Apply config settings";
    m_fpsLimit = m_config.getFpsLimit();
    if (m_fpsLimit > 0)
    {
        m_frameTimeLimit = 1000 / m_fpsLimit;
    }
}

void Engine::wait()
{
    int frameTime = SDL_GetTicks() - m_lastFrameTime;
    if (m_fpsLimit > 0)
    {
        const int timeToWait = m_frameTimeLimit - frameTime;

        if (timeToWait > 0)
        {
            SDL_Delay(timeToWait);
        }
    }
    // save frame actual time
    frameTime = SDL_GetTicks() - m_lastFrameTime;
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

    if (m_game)
    {
        m_game->render();
    }

    Renderer::render();
}

void Engine::update(const size_t dt)
{
    if (m_game)
    {
        m_game->update(dt);
    }
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

        if (m_game)
        {
            m_game->processEvent(event, isEventCaptured);
        }
    }
}

void Engine::clean()
{
    // Call lua function with game exit logic
    Logger("green") << "[Engine] Call Lua exit script";
    lua::Function("exit").call();

    // Destroy all widgets before textures repo
    if (m_game)
    {
        delete m_game;
        m_game = nullptr;
    }
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
}

void Engine::deserialize()
{
    Logger("green") << "[Engine] Deserialize save data";
    initConfig();
}
} // stren