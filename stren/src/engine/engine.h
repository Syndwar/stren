#ifndef STREN_ENGINE_H
#define STREN_ENGINE_H

#include <vector>

#include "engine/app_window.h"
#include "common/colour.h"
#include "common/string_ext.h"
#include "engine/config.h"
#include "engine/event_processor.h"
#include "media/sound_system.h"
#include "repo/fonts_repository.h"
#include "repo/sprites_repository.h"
#include "repo/texts_repository.h"
#include "repo/textures_repository.h"

struct SDL_Window;

namespace stren
{
class SystemTools;
class Screen;
class Widget;
class Game;

// class Engine
class Engine
{
private:
    static const size_t     kFramesAmount;      ///< @todo

    enum class Status
    {
        Stopped = 0,
        Running,
        Restart,
    };

    Status                  m_status;            ///< @todo
    size_t                  m_fpsLimit;          ///< @todo
    size_t                  m_frameTimeLimit;    ///< @todo
    size_t                  m_lastFrameTime;     ///< @todo
    size_t                  m_frameIndex;        ///< @todo

    std::vector<size_t>     m_frameTimeHistory;  ///< @todo

    AppWindow               m_appWindow;         ///< @todo
    Config                  m_config;            ///< @todo
    SpritesRepository       m_spritesRepo;       ///< @todo
    TextsRepository         m_textsRepo;         ///< @todo
    TexturesRepository      m_texturesRepo;      ///< @todo
    FontsRepository         m_fontsRepo;         ///< @todo
    SoundSystem             m_soundSystem;       ///< @todo
    EventProcessor          m_eventProcessor;    ///< @todo
    Game *                  m_game;              ///< @todo

public:
    ///
    /// Constructor
    ///
    Engine();
    ///
    /// Destructor
    ///
    ~Engine();
    ///
    /// @todo
    ///
    inline bool isRunning() const { return m_status == Status::Running; }
    ///
    /// @todo
    ///
    inline bool isRestarting() const { return m_status == Status::Restart; }
    ///
    /// @todo
    ///
    inline void stop() { m_status = Status::Stopped; }
    ///
    /// @todo
    ///
    inline void restart() { m_status = Status::Restart; }
    ///
    /// @todo
    ///
    void clean();
    ///
    /// @todo
    ///
    bool init();
    ///
    /// @todo
    ///
    void process();
    ///
    /// @todo
    ///
    size_t getFPS() const;
    ///
    /// @todo
    ///
    inline int getScreenWidth() const { return m_config.getScreenWidth(); }
    ///
    /// @todo
    ///
    inline int getScreenHeight() const { return m_config.getScreenHeight(); }
    ///
    /// @todo
    ///
    const std::string & getTextByAlias(const std::string & alias);
    ///
    /// @todo
    ///
    SoundSystem * getSoundsSystem() { return &m_soundSystem; }
    ///
    /// @todo
    ///
    void createGame();
    ///
    /// switch current screen with the new one defined by id
    ///
    void switchScreen(void * screen);
    ///
    /// @todo
    ///
    Screen * getCurrentScreen();
    ///
    /// get mouse position
    ///
    const Point & getMousePos();
    ///
    /// @todo
    ///
    Sprite * getSprite(const std::string & spriteId);
    ///
    /// @todo
    ///
    ITexture * getTexture(const std::string & textureId);
    ///
    /// @todo
    ///
    void deserialize();
    ///
    /// @todo
    ///
    void serialize();
    ///
    /// @todo
    ///
    void addUpdateObserver(void * widget);
    ///
    /// @todo
    ///
    void addRenderObserver(void * widget);
    ///
    /// @todo
    ///
    void addEventObserver(void * widget);
    ///
    /// @todo
    ///
    void removeUpdateObserver(void * widget);
    ///
    /// @todo
    ///
    void removeRenderObserver(void * widget);
    ///
    /// @todo
    ///
    void removeEventObserver(void * widget);
private:
    ///
    /// @todo
    ///
    void initScripts();
    ///
    /// @todo
    ///
    void initConfig();
    ///
    /// @todo
    ///
    bool initRenderer();
    ///
    /// @todo
    ///
    void initFonts();
    ///
    /// @todo
    ///
    void initTexts();
    ///
    /// @todo
    ///
    void initSprites();
    ///
    /// @todo
    ///
    void initTextures();
    ///
    /// @todo
    ///
    void initSound();
    ///
    /// @todo
    ///
    void processEvents();
    ///
    /// @todo
    ///
    void render();
    ///
    /// do something after rendering
    ///
    void postRender();
    ///
    /// make engine wait until fps limit is reached
    ///
    void wait();
    ///
    /// @todo
    ///
    void update(const size_t dt);
    ///
    /// @todo
    ///
    bool createRenderer();
};

} // stren
#endif // !STREN_ENGINE_H