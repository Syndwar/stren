#include "app_window.h"

#include "SDL.h"

#include "logger.h"
#include "event.h"

namespace stren
{

AppWindowConfig::AppWindowConfig()
    : isFullscreen(false)
    , screenWidth(800)
    , screenHeight(600)
    , isBorderless(false)
{
}

AppWindow::AppWindow()
    : m_windowParams(SDL_WINDOW_SHOWN)
    , m_left(SDL_WINDOWPOS_CENTERED)
    , m_top(SDL_WINDOWPOS_CENTERED)
    , m_width(800)
    , m_height(600)
    , m_window(nullptr)
{
}

SDL_Renderer * AppWindow::createRenderer(const int renderDriver, const int flags)
{
    return SDL_CreateRenderer(m_window, renderDriver, flags);
}

bool AppWindow::initialize(const AppWindowConfig & config)
{
    if (!m_window)
    {
        setSize(config.screenWidth, config.screenHeight);
        m_windowParams = SDL_WINDOW_SHOWN;
        if (config.isFullscreen)
        {
            m_windowParams |= SDL_WINDOW_FULLSCREEN;
        }
        if (config.isBorderless)
        {
            m_windowParams |= SDL_WINDOW_BORDERLESS;
        }
        Logger("green") << "[Engine] Create SDL window";
        m_window = SDL_CreateWindow(config.title.c_str(), m_left, m_top, m_width, m_height, m_windowParams);
    }

    return nullptr != m_window;
}

void AppWindow::release()
{
    Logger("green") << "[Engine] Destroy SDL window";
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}

void AppWindow::toggleFullscreen(const bool value)
{
    Logger("green") << "[Engine] Set full screen: " << std::to_string(value);
    if (m_window)
    {
        m_windowParams = value ? SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_SHOWN;
        SDL_SetWindowFullscreen(m_window, m_windowParams);
    }
}

bool AppWindow::isFullscreen() const
{
    return 0 != (SDL_WINDOW_FULLSCREEN_DESKTOP & m_windowParams);
}

} // stren