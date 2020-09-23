#ifndef STREN_MAP_EDITOR_ITEMS_PANEL_H
#define STREN_MAP_EDITOR_ITEMS_PANEL_H

#include "widgets/container.h"

namespace stren
{
class MapData;
///
/// class MapEditorItemsPanel
///
class MapEditorItemsPanel : public Container
{
private:
    MapData * m_mapData;   ///< @todo
public:
    ///
    /// Constructor
    ///
    MapEditorItemsPanel(const std::string & id, MapData * mapData);
    ///
    /// Destructor
    ///
    virtual ~MapEditorItemsPanel();
private:
    ///
    /// @todo
    ///
    void onMapItemClicked(Widget * sender);
};
} // stren
#endif // !STREN_MAP_EDITOR_ITEMS_PANEL_H
