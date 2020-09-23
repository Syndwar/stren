#ifndef STREN_GAME_H
#define STREN_GAME_H

#include <vector>

namespace stren
{

struct UnitStats;
class Unit;
///
/// class Game
///
class Game
{
private:
    std::vector<Unit> m_units;
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
};
} // stren

#endif // !STREN_GAME_H