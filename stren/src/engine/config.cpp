#include "config.h"

#include "save_data.h"

namespace stren
{
Config::Config()
    : m_isFullscreen(false)
    , m_borderless(false)
    , m_vsync(false)
    , m_screenWidth(800)
    , m_screenHeight(600)
    , m_fpsLimit(60)
{
}

bool Config::initialize(const SaveData & data)
{
    m_vsync = data.isVSync();
    m_isFullscreen = data.isFullscreen();
    m_screenWidth = data.getScreenWidth();
    m_screenHeight = data.getScreenHeight();
    m_fpsLimit = data.getFpsLimit();
    m_borderless = data.isBorderless();
    m_title = data.getTitle();
    return true;
}

} // stren