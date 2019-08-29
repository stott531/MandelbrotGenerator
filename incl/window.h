#pragma once

#include <cstddef>
#include <complex>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Shader.hpp>

#include "camera.h"

#define MAX_ITERATIONS 150

class Camera;

using std::complex;
using std::size_t;

class Window : public sf::RenderWindow {
    public:
        Window(const int &height, const int &width);
        void Think();
    protected:
        void PlotMandelbrotSetDefault();
        void PlotMandelbrotSetShaders();

    private:
        unsigned int m_screen_width, m_screen_height;
        sf::VertexArray m_pixel_map;
        std::unique_ptr<Camera> m_camera;
};