#include "primitive_figures.h"

#include "SDL.h"
#include "colour.h"
#include "renderer.h"

namespace stren
{
///
/// PriimitiveRect
///
PrimitiveRect::PrimitiveRect(const Rect & rect, const bool fill)
    : PrimitiveFigure()
    , fill_(fill)
    , rect_(rect)
{
}

PrimitiveRect::~PrimitiveRect()
{
}

void PrimitiveRect::render(const Colour & colour)
{
    if (SDL_Renderer * renderer = Renderer::instantiate())
    {
        const Rect & clippingRect = Renderer::getClippingRect();
        const Point & offset = Renderer::getOffset();
        // check if any rect is inside the clipping area
        const int x = rect_.getX() - offset.getX();
        const int y = rect_.getY() - offset.getY();
        const int w = rect_.getWidth();
        const int h = rect_.getHeight();
        if (clippingRect.hasCommon(x, y, w, h))
        {
            const Colour oldColour = Renderer::getRenderColour();
            Renderer::setRenderColour(colour);
            SDL_Rect rect = { x, y, w, h };
            if (fill_)
            {
                SDL_RenderFillRect(renderer, &rect);
            }
            else
            {
                SDL_RenderDrawRect(renderer, &rect);
            }
            Renderer::setRenderColour(oldColour);
        }
    }
}

void PrimitiveRect::moveTo(const int x, const int y)
{
    rect_.moveTo(x, y);
}

void PrimitiveRect::moveBy(const int dx, const int dy)
{
    rect_.moveBy(dx, dy);
}
///
/// PrimitiveRects
///
PrimitiveRects::PrimitiveRects(const std::vector<Rect> & rects, const bool fill)
    : PrimitiveFigure()
    , fill_(fill)
    , rects_(rects)
{
}

PrimitiveRects::~PrimitiveRects()
{
}

void PrimitiveRects::render(const Colour & colour)
{
    if (SDL_Renderer * renderer = Renderer::instantiate())
    {
        const Colour oldColour = Renderer::getRenderColour();
        Renderer::setRenderColour(colour);
        const Rect & clippingRect = Renderer::getClippingRect();
        const Point & offset = Renderer::getOffset();

        SDL_Rect sdlRect;
        for (const Rect & rect : rects_)
        {
            // check if any rect is inside the clipping area
            const int x = rect.getX() - offset.getX();
            const int y = rect.getY() - offset.getY();
            const int w = rect.getWidth();
            const int h = rect.getHeight();
            if (clippingRect.hasCommon(x, y, w, h))
            {
                sdlRect.x = x;
                sdlRect.y = y;
                sdlRect.w = w;
                sdlRect.h = h;

                if (fill_)
                {
                    SDL_RenderFillRect(renderer, &sdlRect);
                }
                else
                {
                    SDL_RenderDrawRect(renderer, &sdlRect);
                }
            }
        }
        Renderer::setRenderColour(oldColour);
    }
}

void PrimitiveRects::moveTo(const int x, const int y)
{
    for (Rect & rect : rects_)
    {
        rect.moveTo(x, y);
    }
}

void PrimitiveRects::moveBy(const int dx, const int dy)
{
    for (Rect & rect : rects_)
    {
        rect.moveBy(dx, dy);
    }
}
///
/// PrimitiveLines
///
PrimitiveLines::PrimitiveLines(const std::vector<Point> & points)
    : PrimitiveFigure()
    , points_(points)
    , sdlPoints_(nullptr)
{
    const size_t pointsCount = points.size();
    if (pointsCount)
    {
        sdlPoints_ = new SDL_Point[pointsCount];
    }
}

PrimitiveLines::~PrimitiveLines()
{
    if (sdlPoints_)
    {
        delete[] sdlPoints_;
    }
}

void PrimitiveLines::render(const Colour & colour)
{
    if (SDL_Renderer * renderer = Renderer::instantiate())
    {
        const Rect & clippingRect = Renderer::getClippingRect();
        const Point & offset = Renderer::getOffset();

        const size_t pointsCount = points_.size();
        if (pointsCount)
        {
            const Colour oldColour = Renderer::getRenderColour();
            Renderer::setRenderColour(colour);

            int i = 0;
            for (const Point & point : points_)
            {
                sdlPoints_[i].x = point.getX() - offset.getX();
                sdlPoints_[i].y = point.getY() - offset.getY();
                ++i;
            }

            SDL_RenderDrawLines(renderer, sdlPoints_, pointsCount);
            Renderer::setRenderColour(oldColour);
        }
    }
}

void PrimitiveLines::moveTo(const int x, const int y)
{
    if (points_.empty()) return;
    Point & firstPoint = points_[0];
    const int dx = x - firstPoint.getX();
    const int dy = y - firstPoint.getY();
    for (Point & point : points_)
    {
        point.moveBy(dx, dy);
    }
}

void PrimitiveLines::moveBy(const int dx, const int dy)
{
    if (points_.empty()) return;

    for (Point & point : points_)
    {
        point.moveBy(dx, dy);
    }
}
///
/// PrimitivePoint
///
PrimitivePoint::PrimitivePoint(const Point & point)
    : PrimitiveFigure()
    , point_(point)
{
}

PrimitivePoint::~PrimitivePoint()
{
}

void PrimitivePoint::render(const Colour & colour)
{
    if (SDL_Renderer * renderer = Renderer::instantiate())
    {
        const Rect & clippingRect = Renderer::getClippingRect();
        const Point & offset = Renderer::getOffset();
        // check if any point is inside clipping area
        const int x = point_.getX() - offset.getX();
        const int y = point_.getY() - offset.getY();
        if (clippingRect.hasCommon(x, y))
        {
            const Colour oldColour = Renderer::getRenderColour();
            Renderer::setRenderColour(colour);
            SDL_RenderDrawPoint(renderer, x, y);
            Renderer::setRenderColour(oldColour);
        }
    }
}

void PrimitivePoint::moveTo(const int x, const int y)
{
    point_.moveTo(x, y);
}

void PrimitivePoint::moveBy(const int dx, const int dy)
{
    point_.moveBy(dx, dy);
}
///
/// PrimitivePoints
///
PrimitivePoints::PrimitivePoints(const std::vector<Point> & points)
    : PrimitiveFigure()
    , points_(points)
{
}

PrimitivePoints::~PrimitivePoints()
{
}

void PrimitivePoints::render(const Colour & colour)
{
    if (SDL_Renderer * renderer = Renderer::instantiate())
    {
        const Rect & clippingRect = Renderer::getClippingRect();
        const Point & offset = Renderer::getOffset();
        for (const Point & point : points_)
        {
            // check if any point is inside clipping area
            const int x = point.getX() - offset.getX();
            const int y = point.getY() - offset.getY();
            if (clippingRect.hasCommon(x, y))
            {
                const Colour oldColour = Renderer::getRenderColour();
                Renderer::setRenderColour(colour);
                SDL_RenderDrawPoint(renderer, x, y);
                Renderer::setRenderColour(oldColour);
            }
        }
    }
}

void PrimitivePoints::moveTo(const int x, const int y)
{
    for (Point & point : points_)
    {
        point.moveTo(x, y);
    }
}

void PrimitivePoints::moveBy(const int dx, const int dy)
{
    for (Point & point : points_)
    {
        point.moveBy(dx, dy);
    }
}
///
/// PrimitiveCircle
///
PrimitiveCircle::PrimitiveCircle(const int x, const int y, const int radius)
    : PrimitiveFigure()
    , x_(x)
    , y_(y)
    , radius_(radius)
{
}

PrimitiveCircle::~PrimitiveCircle()
{
}

void PrimitiveCircle::render(const Colour & colour)
{
    if (SDL_Renderer * renderer = Renderer::instantiate())
    {
        const Rect & clippingRect = Renderer::getClippingRect();
        const Point & offset = Renderer::getOffset();
        const int diameter = radius_ * 2;
        if (clippingRect.isEmpty() || clippingRect.hasCommon(x_ - radius_ - offset.getX(), y_ - radius_ - offset.getY(), diameter, diameter))
        {
            const Colour oldColour = Renderer::getRenderColour();
            Renderer::setRenderColour(colour);

            int x = radius_ - 1;
            int y = 0;
            int tx = 1;
            int ty = 1;
            int error = tx - diameter;

            enum
            {
                nPoints = 8
            };

            SDL_Point points[nPoints];

            while (x >= y)
            {
                //  Each of the following renders an octant of the circle
                const int centerx = x_ - offset.getX();
                const int centery = y_ - offset.getY();
                points[0].x = centerx + x; points[0].y = centery - y;
                points[1].x = centerx + x; points[1].y = centery + y;
                points[2].x = centerx - x; points[2].y = centery - y;
                points[3].x = centerx - x; points[3].y = centery + y;
                points[4].x = centerx + y; points[4].y = centery - x;
                points[5].x = centerx + y; points[5].y = centery + x;
                points[6].x = centerx - y; points[6].y = centery - x;
                points[7].x = centerx - y; points[7].y = centery + x;
                SDL_RenderDrawPoints(renderer, points, nPoints);

                if (error <= 0)
                {
                    ++y;
                    error += ty;
                    ty += 2;
                }

                if (error > 0)
                {
                    --x;
                    tx += 2;
                    error += (tx - diameter);
                }
            }
            Renderer::setRenderColour(oldColour);
        }
    }
}

void PrimitiveCircle::moveTo(const int x, const int y)
{
    x_ = x;
    y_ = y;
}

void PrimitiveCircle::moveBy(const int dx, const int dy)
{
    x_ += dx;
    y_ += dy;
}

} // stren