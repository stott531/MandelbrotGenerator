//
// Created by stott on 8/28/19.
//

#include <iostream>
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

void Camera::HandleKeyboardInput(const sf::Event::KeyEvent &event) {
    switch (event.code)
    {
        case sf::Keyboard::Key::Q:
            m_zoom_factor -= 1 / (m_zoom_factor * 30);
            break;
        case sf::Keyboard::Key::E:
            m_zoom_factor += 1 / (m_zoom_factor * 30);
            break;
        case sf::Keyboard::Key::W:
            k_shift -= 1. / 50. / m_zoom_factor;
            break;
        case sf::Keyboard::Key::S:
            k_shift += 1. / 50. / m_zoom_factor;
            break;
        case sf::Keyboard::Key::A:
            h_shift += 1. / 50. / m_zoom_factor;
            break;
        case sf::Keyboard::Key::D:
            h_shift -= 1. / 50. / m_zoom_factor;
            break;
    }
    std::cout << "zoom: " << this->m_zoom_factor  << "\th_shift: " << this->h_shift << "\tk_shift: " << this->k_shift<< std::endl;

}

