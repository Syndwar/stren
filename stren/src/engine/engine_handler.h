#ifndef STREN_ENGINE_HANDLER_H
#define STREN_ENGINE_HANDLER_H

#include "engine/event.h"

struct lua_State;

namespace stren
{
class Engine;
class ITexture;
class Point;
class SoundSystem;
class Screen;
class Sprite;
class Widget;

enum class ScreenId;
///
/// class EngineHandler
///
class EngineHandler
{
private:
    static Engine * m_engine;    ///< engine itself
public:
    ///
    /// Create game engine if it is not created, returns true if engine was create successfully
    ///
    static bool create();
    ///
    /// Destroy game engine
    ///
    static void destroy();
    ///
    /// Try initialize engine, return true if succeeded
    ///
    static bool init();
    ///
    /// Stop the engine
    ///
    static void stop();
    ///
    /// Check if engine need restart
    ///
    static bool isRestarting();
    ///
    /// Check if engine is running
    ///
    static bool isRunning();
    ///
    /// Process engine functions while its running
    ///
    static void process();
    ///
    /// @todo
    ///
    static int getScreenWidth();
    ///
    /// @todo
    ///
    static int getScreenHeight();
    ///
    /// @todo
    ///
    static const std::string & getTextByAlias(const std::string & alias);
    ///
    /// @todo
    ///
    static size_t getFPS();
    ///
    /// @todo
    ///
    static void createGame();
    ///
    /// @todo
    ///
    static SoundSystem * getSoundSystem();
    ///
    /// @todo
    ///
    static Screen * getCurrentScreen();
    ///
    /// stop engine
    ///
    static void shutdown();
    ///
    /// restart engine
    ///
    static void restart();
    ///
    /// get mouse position
    ///
    static const Point & getMousePos();
    ///
    /// get sprite by id
    ///
    static Sprite * getSprite(const std::string & spriteId);
    ///
    /// get texture by id
    ///
    static ITexture * getTexture(const std::string & textureId);
    ///
    /// switch current screen with the new one defined by id
    ///
    static void switchScreen(Screen * screen);
    ///
    /// @todo
    ///
    static void deserialize();
    ///
    /// @todo
    ///
    static void serialize();
    ///
    /// @todo
    ///
    static void bind();
    ///
    /// store widget in the memory controller
    ///
    static size_t storeInMemoryController(Widget * widget);
    ///
    /// find widget in the memory controller
    ///
    static size_t findInMemoryController(Widget * widget);
    ///
    /// get widget from the memory controller
    ///
    template<typename T1, typename T2>
    static T1 getMemoryObj(const T2 & tbl)
    {
        const size_t handler = static_cast<size_t>(tbl.get("this").getInt());
        if (m_engine)
        {
            return m_engine->getFromMemoryController<T1>(handler);
        }
        return nullptr;
    }
    ///
    /// collects unreleased resources in the engine
    ///
    static void collectGarbage();
};

} // stren

#endif // STREN_ENGINE_HANDLER_H
