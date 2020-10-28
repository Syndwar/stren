#include "camera.h"

#include "render/renderer.h"
#include "widgets/widget.h"

namespace stren
{
Camera::Camera()
{
}

Camera::Camera(const Rect & rect)
    : rect_(rect)
{
}

Camera::Camera(const int x, const int y, const int w, const int h)
    : rect_(x, y, w, h)
{
}

Camera::~Camera()
{
}

void Camera::render(Widget * widget)
{
    if (widget)
    {
        place();
        widget->render();
        restore();
    }
}

void Camera::place()
{
    clippingRect_ = Renderer::getClippingRect();
    Renderer::addOffset(target_.getX(), target_.getY());
    Renderer::setClippingRect(rect_);
}

void Camera::restore()
{
    Renderer::addOffset(-target_.getX(), -target_.getY());
    Renderer::setClippingRect(clippingRect_);
}

void Camera::moveTo(const int x, const int y)
{
    rect_.moveTo(x, y);
}

void Camera::resize(const int w, const int h)
{
    rect_.setSize(w, h);
}
} // stren