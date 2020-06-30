#ifndef STREN_MAP_EDITOR_SCREEN_H
#define STREN_MAP_EDITOR_SCREEN_H

#include "widgets/screen.h"

namespace stren
{
class MapData;
class Primitive;
///
/// class MapEditorScreen
class MapEditorScreen : public Screen
{
private:
    MapData *           mapData_;           ///< @todo
    std::string         selectedItemId_;    ///< @todo
    Primitive *         grid_;              ///< @todo
public:
    ///
    /// Constructor
    ///
    MapEditorScreen();
    ///
    /// Destructor
    ///
    ~MapEditorScreen();
    ///
    /// @todo
    ///
    void selectItem(const std::string & id);
    ///
    /// @todo
    ///
    void enableGrid(const bool value);
private:
    ///
    /// @todo
    ///
    void onBattleFieldClicked();
private:
    ///
    /// @todo
    ///
    void createGrid(std::vector<Point> & points);
};
} // stren
#endif // STREN_MAP_EDITOR_SCREEN_H
