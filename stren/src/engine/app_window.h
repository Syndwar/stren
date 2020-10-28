#ifndef STREN_APP_WINDOW_H
#define STREN_APP_WINDOW_H

#include <vector>
#include "common/string_ext.h"

struct SDL_Window;
struct SDL_Renderer;

namespace stren
{
///
/// class AppWindowConfig holds information about game window settings
///
class AppWindowConfig
{
public:
    bool isFullscreen;      ///< is fullscreen is toggled
    bool isBorderless;      ///< is borderless window mode is toggled
    int screenWidth;        ///< window screen width
    int screenHeight;       ///< window screen height
    std::string title;      ///< window title
    ///
    /// Constructor
    ///
    AppWindowConfig();
};
///
/// class AppWindow holds pointer to the SDL window, controls operations with game window
///
class AppWindow
{
private:
    SDL_Window *    m_window;            ///< sdl window
    int             m_windowParams;      ///< parameters for sdl window: fullscreen/window, show/hidden
    int             m_left;              ///< window position
    int             m_top;               ///< window position
    int             m_width;             ///< window width
    int             m_height;            ///< window height
public:
    ///
    /// Constructor
    ///
    AppWindow();
    ///
    /// Returns new renderer for the current window
    ///
    SDL_Renderer * createRenderer(const int renderDriver, const int flags);
    ///
    /// Initializes SDL window using config
    ///
    bool initialize(const AppWindowConfig & config);
    ///
    /// Destroys SDL window
    ///
    void release();
    ///
    /// Toggles fullscreen on/off
    ///
    void toggleFullscreen(const bool value);
    ///
    /// Returns if window is set to fullscreen
    ///
    bool isFullscreen() const;
private:
    ///
    /// Changes window size
    ///
    inline void setSize(const int width, const int height) { m_width = width, m_height = height; }
};
}

#endif // STREN_APP_WINDOW_H
