#ifndef STREN_ENGINE_H
#define STREN_ENGINE_H

#include <vector>

#include "engine/app_window.h"
#include "memory_controller.h"
#include "engine/memory_controller.h"
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
    MemoryController        m_memoryController;  ///< @todo

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
    void switchScreen(Screen * screen);
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
    /// find widget in the memory controller
    ///
    size_t findInMemoryController(Widget * widget);
    ///
    /// store widget in the memory controller
    ///
    size_t storeInMemoryController(Widget * widget);
    ///
    /// get widget from the memory controller
    ///
    template<typename T>
    T getFromMemoryController(const size_t handler)
    {
        return m_memoryController.get<T>(handler);
    }
    ///
    /// check for unused resources and free them
    ///
    void collectGarbage();
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