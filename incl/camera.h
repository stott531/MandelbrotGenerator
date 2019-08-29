//
// Created by stott on 8/28/19.
//

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "window.h"

class Window;

class Camera {

    public:
        Camera(const int &screen_height, const int &screen_width, Window *window);
        void Zoom(const sf::Event::MouseWheelScrollEvent& event);
        void Pan(const sf::Event::MouseMoveEvent& event);
        float GetZoom() { return this->m_zoom_factor; }
        void TogglePanning(const sf::Event::MouseButtonEvent& event);
        float h_shift = 1.5, k_shift = 0.5;

    private:
        sf::Vector2f m_center;
        float m_zoom_factor = 2.;

        bool m_is_panning = false;
        sf::Vector2i m_last_cursor;
        Window* m_window;

};

