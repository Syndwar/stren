#ifndef STREN_MAP_EDITOR_SYSTEM_PANEL_H
#define STREN_MAP_EDITOR_SYSTEM_PANEL_H

#include "widgets/container.h"

namespace stren
{
///
/// class MapEditorSystemPanel
///
class MapEditorSystemPanel : public Container
{
private:
    bool m_isGridOn;    ///< @todo
public:
    ///
    /// Constructor
    ///
    MapEditorSystemPanel(const std::string & id);
    ///
    /// Destructor
    ///
    virtual ~MapEditorSystemPanel();
private:
    ///
    /// @todo
    ///
    void onBackBtnClick();
    ///
    /// @todo
    ///
    void onSaveBtnClick();
    ///
    /// @todo
    ///
    void onLoadBtnClick();
    ///
    /// @todo
    ///
    void onGridBtnClick(Widget * sender);
};
} // stren
#endif // !STREN_MAP_EDITOR_SYSTEM_PANEL_H
