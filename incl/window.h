#pragma once

#include <cstddef>

#include <complex>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#define MAX_ITERATIONS 150

using std::complex;
using std::size_t;

class Window : public sf::RenderWindow {
    public:
        Window();
        void Think();
    protected:
        void PlotMandelbrotSet();

    private:
        constexpr static unsigned int m_screen_width = 1000,
                                      m_screen_height = 800;
        sf::VertexArray m_pixel_map;

};