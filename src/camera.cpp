//
// Created by stott on 8/28/19.
//

#include "../incl/camera.h"

Camera::Camera(const int &screen_height, const int &screen_width) :
    m_center({(float)screen_width/2, (float)screen_height/2})
{

}

void Camera::Zoom(const sf::Event::MouseWheelScrollEvent &event)
{
    this->m_zoom_factor -= event.delta / 10;
}

void Camera::Pan(const sf::Event::MouseMoveEvent &event)
{
    if (!m_is_panning) return;
}
