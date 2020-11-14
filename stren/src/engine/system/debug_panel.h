#ifndef STREN_DEBUG_PANEL_H
#define STREN_DEBUG_PANEL_H

#include "widgets/dialog.h"

namespace stren
{
///
/// class DebugPanel
///
class DebugPanel : public Dialog
{
public:
    ///
    /// Constructor
    ///
    DebugPanel(const std::string & id);
protected:
    ///
    /// update content
    ///
    virtual void doUpdate(const size_t dt) override;
private:
    ///
    /// update lbl with fps counter
    ///
    void updateFps(const std::string & text);
    ///
    /// update lbl with mouse position
    ///
    void updateMousePos(const int x, const int y);
};
} // stren
#endif // STREN_DEBUG_PANEL_H
