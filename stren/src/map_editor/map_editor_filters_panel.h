#ifndef STREN_MAP_EDITOR_FILTER_PANEL_H
#define STREN_MAP_EDITOR_FILTER_PANEL_H

#include "widgets/container.h"

namespace stren
{
///
/// class MapEditorFiltersPanel
///
class MapEditorFiltersPanel : public Container
{
public:
    ///
    /// Constructor
    ///
    MapEditorFiltersPanel(const std::string & id);
    ///
    /// Destructor
    ///
    virtual ~MapEditorFiltersPanel();
private:
    ///
    /// @todo
    ///
    void onFilterBtnClick(Widget * sender);
};
} // stren
#endif // !STREN_MAP_EDITOR_FILTER_PANEL_H
