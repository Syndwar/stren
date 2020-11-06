#ifndef STREN_GAME_H
#define STREN_GAME_H

#include "engine/screen_selector.h"
#include "engine/camera.h"
#include "engine/keyboard.h"

namespace stren
{
class IAction;
class Event;

enum class EventType;

///
/// class Game
///
class Game
{
private:
    Mouse           m_mouse;             ///< @todo
    Keyboard        m_keyboard;          ///< @todo
    Camera          m_camera;            ///< @todo
    ScreenSelector  m_screenSelector;    ///< @todo
/*
    std::vector<Unit> m_units;
*/
public:
    ///
    /// Constructor
    ///
    Game();
    ///
    /// Destructor
    ///
    ~Game();
    ///
    /// @todo
    ///
    Screen * getCurrentScreen();
    ///
    /// @todo
    ///
    void update(const size_t dt);
    ///
    /// @todo
    ///
    void processEvent(const Event & event, bool & isEventCaptured);
    ///
    /// @todo
    ///
    void render();
    ///
    /// @todo
    ///
    void switchScreen(void * screen);
    ///
    /// @todo
    ///
    size_t addKeyboardAction(const EventType eventType, const std::string & key, IAction * action);
    ///
    /// @todo
    ///
    void removeKeyboardAction(const size_t key);
    ///
    /// @todo
    ///
    size_t addMouseAction(const EventType eventType, const Event::MouseButton, IAction * action);
    ///
    /// @todo
    ///
    void removeMouseAction(const size_t key);
    /*
    ///
    /// @todo
    ///
    void update(const size_t dt);
    ///
    /// @todo
    ///
    void createBoard();
    ///
    /// @todo
    ///
    void createTerrain();
    ///
    /// @todo
    ///
    void createObjects();
    ///
    /// @todo
    ///
    void createUnits();
    ///
    /// @todo
    ///
    void createItems();
    ///
    /// @todo
    ///
    void addUnit(const UnitStats & stats);
    */
};
} // stren

#endif // !STREN_GAME_H