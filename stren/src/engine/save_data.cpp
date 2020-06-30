#include "save_data.h"

#include "lua_wrapper.h"

namespace stren
{
SaveData::SaveData()
    : m_isVSync(false)
    , m_isBorderless(false)
    , m_isFullscreen(false)
    , m_screenWidth(1024)
    , m_screenHeight(768)
    , m_fpsLimit(60)
{
}

SaveData::~SaveData()
{
}

void SaveData::serialize()
{
    std::vector<lua::Value> results(1);
    lua::Function func("UserSave.getConfig");
    func.call(lua::Function::kEmptyParams, results);
    lua::Table tbl(results[0]);
    tbl.set("vsync", m_isVSync);
    tbl.set("borderless", m_isBorderless);
    tbl.set("fullscreen", m_isFullscreen);
    tbl.set("screenWidth", m_screenWidth);
    tbl.set("screenHeight", m_screenHeight);
    tbl.set("fpsLimit", m_fpsLimit);

    lua::Function save("UserSave.save");
    save.call();
}

void SaveData::deserialize()
{
    std::vector<lua::Value> results(1);
    lua::Function func("UserSave.getConfig");
    func.call(lua::Function::kEmptyParams, results);
    lua::Table tbl(results[0]);
    m_isVSync = tbl.get("vsync").getBool();
    m_isBorderless = tbl.get("borderless").getBool();
    m_isFullscreen = tbl.get("fullscreen").getBool();
    m_screenWidth = tbl.get("screenWidth").getInt();
    m_screenHeight = tbl.get("screenHeight").getInt();
    m_fpsLimit = tbl.get("fpsLimit").getInt();
    m_title = tbl.get("title").getString();
}
} // stren