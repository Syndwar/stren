#ifndef STREN_GAME_H
#define STREN_GAME_H

#include "engine/screen_selector.h"
#include "engine/camera.h"

namespace stren
{
class Event;

///
/// class Game
///
class Game
{
private:
    Camera                  m_camera;            ///< @todo
    ScreenSelector          m_screenSelector;    ///< @todo
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
    /*
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