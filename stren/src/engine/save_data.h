#ifndef STREN_SAVE_DATA_H
#define STREN_SAVE_DATA_H

#include "string_ext.h"

namespace stren
{
class SaveData
{
private:
    bool         m_isVSync;          ///< @todo
    bool         m_isBorderless;     ///< @todo
    bool         m_isFullscreen;     ///< @todo
    int          m_screenWidth;      ///< @todo
    int          m_screenHeight;     ///< @todo
    int          m_fpsLimit;         ///< @todo
    std::string  m_title;            ///< @todo
public:
    ///
    /// Constructor
    ///
    SaveData();
    ///
    /// Destructor
    ///
    ~SaveData();
    ///
    /// save user data to file
    ///
    void serialize();
    ///
    /// load user data from file
    ///
    void deserialize();
    ///
    /// @todo
    ///
    bool isVSync() const { return m_isVSync; }
    ///
    /// @todo
    ///
    void setVSync(const bool value) { m_isVSync = value; }
    ///
    /// @todo
    ///
    bool isBorderless() const { return m_isBorderless; }
    ///
    /// @todo
    ///
    void setBorderless(const bool value) { m_isBorderless = value; }
    ///
    /// @todo
    ///
    bool isFullscreen() const { return m_isFullscreen; }
    ///
    /// @todo
    ///
    void setFullscreen(const bool value) { m_isFullscreen = value; }
    ///
    /// @todo
    ///
    void setResolution(const int width, const int height) { m_screenWidth = width, m_screenHeight = height; }
    ///
    /// @todo
    ///
    int getScreenWidth() const { return m_screenWidth; }
    ///
    /// @todo
    ///
    int getScreenHeight() const { return m_screenHeight; }
    ///
    /// @todo
    ///
    int getFpsLimit() const { return m_fpsLimit; }
    ///
    /// @todo
    ///
    const std::string & getTitle() const { return m_title; }
};
} // stren

#endif // STREN_SAVE_DATA_H
