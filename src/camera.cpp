//
// Created by stott on 8/28/19.
//

#include "../incl/camera.h"

Camera::Camera(const int &screen_height, const int &screen_width, Window *window) :
    m_center({(float)screen_width/2, (float)screen_height/2}), m_window(window)
{

}

void Camera::Zoom(const sf::Event::MouseWheelScrollEvent &event)
{
    this->m_zoom_factor -= event.delta / (m_zoom_factor * 20);
}

void Camera::Pan(const sf::Event::MouseMoveEvent &event)
{
    if (!m_is_panning) return;

    // Calculate the change in mouse position
    sf::Vector2i deltaMousePosition(event.x, event.y);
    deltaMousePosition -= m_last_cursor;

    // Shift the view using the delta
    h_shift += deltaMousePosition.x / 750. / m_zoom_factor;
    k_shift -= deltaMousePosition.y / 750. / m_zoom_factor;


    // Set the last mouse position to be the mouse position in this frame
    m_last_cursor = {event.x, event.y};


}

void Camera::TogglePanning(const sf::Event::MouseButtonEvent& event) {
    if (event.button == sf::Mouse::Right) m_is_panning = !m_is_panning;
    m_last_cursor = {event.x, event.y};
}
