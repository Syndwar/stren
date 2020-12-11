#include "camera.h"

#include "render/renderer.h"
#include "widgets/widget.h"

namespace stren
{
Camera::Camera()
{
}

Camera::Camera(const Rect & rect)
    : m_rect(rect)
{
}

Camera::Camera(const int x, const int y, const int w, const int h)
    : m_rect(x, y, w, h)
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
    m_clippingRect = Renderer::getClippingRect();
    Renderer::addOffset(m_target.getX(), m_target.getY());
    Renderer::setClippingRect(m_rect);
}

void Camera::restore()
{
    Renderer::addOffset(-m_target.getX(), -m_target.getY());
    Renderer::setClippingRect(m_clippingRect);
}

void Camera::moveTo(const int x, const int y)
{
    m_rect.moveTo(x, y);
}

void Camera::resize(const int w, const int h)
{
    m_rect.setSize(w, h);
}
} // stren