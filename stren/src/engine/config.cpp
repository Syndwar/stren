#include "config.h"

#include "lua_wrapper.h"

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

bool Config::initialize()
{
    std::vector<lua::Value> results(1);
    lua::Function func("UserSave.getConfig");
    func.call(lua::Function::kEmptyParams, results);
    lua::Table tbl(results[0]);

    m_vsync = tbl.get("vsync").getBool();
    m_borderless = tbl.get("borderless").getBool();
    m_isFullscreen = tbl.get("fullscreen").getBool();
    m_screenWidth = tbl.get("screen_width").getInt();
    m_screenHeight = tbl.get("screen_height").getInt();
    m_fpsLimit = tbl.get("fps_limit").getInt();
    m_title = tbl.get("title").getString();
    return true;
}

} // stren