#ifndef STREN_CONFIG_H
#define STREN_CONFIG_H

#include <map>
#include "common/string_ext.h"

namespace stren
{
///
/// class Config
///
class Config 
{
private:
    bool   m_borderless;                   ///< if application window will be show without borders
    bool   m_vsync;                        ///< if vertical synchronization is enabled for the application
    bool   m_isFullscreen;                 ///< if application should be opened in full screen
    int    m_screenWidth;                  ///< application screen height
    int    m_screenHeight;                 ///< application screen width
    int    m_fpsLimit;                     ///< application fps limit, if 0 - unlimited fps
    std::string m_title;                   ///< application window title

public:
    ///
    /// Constructor
    ///
    Config();
    ///
    /// returns if fullscreen mode is enabled
    ///
    inline bool isFullscreen() const { return m_isFullscreen; }
    ///
    /// returns screen width
    ///
    inline int getScreenWidth() const { return m_screenWidth; }
    ///
    /// returns screen height
    ///
    inline int getScreenHeight() const { return m_screenHeight; }
    ///
    /// returns game fps limit
    ///
    inline int getFpsLimit() const { return m_fpsLimit; }
    ///
    /// returns if vertical synchronization is enabled
    ///
    inline bool isVSync() const { return m_vsync; }
    ///
    /// returns if borderless mode is enabled
    ///
    inline bool isBorderless() const { return m_borderless; }
    ///
    /// returns main window title
    ///
    inline const std::string & getTitle() const { return m_title; }
    ///
    /// initialize config module
    ///
    bool initialize();
};

} // stren

#endif // STREN_CONFIG_H