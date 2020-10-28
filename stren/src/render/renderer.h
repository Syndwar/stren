#ifndef STREN_RENDERER_H
#define STREN_RENDERER_H

#include "common/rect.h"
#include "common/point.h"

struct SDL_Renderer;

namespace stren
{
class AppWindow;
class Colour;
///
/// class Renderer
///
class Renderer
{
private:
    static SDL_Renderer *   m_renderer;     ///< main game renderer
    static Rect             m_clippingRect; ///< only objects inside this area are rendered
    static Point            m_offset;       ///< rendering offset, applied to all the rendering target rects
    static int              m_alpha;        ///< @todo
public:
    ///
    /// Constructor
    ///
    Renderer();
    ///
    /// @todo
    ///
    static SDL_Renderer * instantiate() { return m_renderer; }
    ///
    /// @todo
    ///
    static bool initialize(AppWindow & appWindow, const bool vsync);
    ///
    /// @todo
    ///
    static void release();
    ///
    /// @todo
    ///
    static void setRenderColour(const Colour & colour);
    ///
    /// @todo
    ///
    static Colour getRenderColour();
    ///
    /// @todo
    ///
    static void setClippingRect(const Rect & rect);
    ///
    /// @todo
    ///
    static const Rect & getClippingRect() { return m_clippingRect; }
    ///
    /// @todo
    ///
    static const Point & getOffset() { return m_offset; }
    ///
    /// @todo
    ///
    static void setOffset(const int x, const int y) { m_offset.set(x, y); }
    ///
    /// @todo
    ///
    static void addOffset(const int x, const int y) { m_offset.moveBy(x, y); }
    ///
    /// @todo
    ///
    static int getAlpha() { return m_alpha; }
    ///
    /// @todo
    ///
    static void setAlpha(const int alpha) { m_alpha = alpha; }
    ///
    /// clear the renderer to the draw color
    ///
    static void clear();
    ///
    /// render on screen
    ///
    static void render();
};
} // stren

#endif // STREN_RENDERER_H
