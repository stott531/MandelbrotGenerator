//
// Created by stott on 8/28/19.
//

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

class Camera {

    public:
        Camera(const int& screen_height, const int& screen_width);
        void Zoom(const sf::Event::MouseWheelScrollEvent& event);
        void Pan(const sf::Event::MouseMoveEvent& event);
        float GetZoom() { return this->m_zoom_factor; }
        void StartPanning() { this->m_is_panning = true; }
        void StopPanning() { this->m_is_panning = false; }


    private:
        sf::Vector2f m_center;
        float m_zoom_factor = 2.;
        bool m_is_panning = false;
        sf::Vector2i m_last_cursor;
};

