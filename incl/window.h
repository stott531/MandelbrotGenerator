#pragma once

#include <cstddef>
#include <complex>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "camera.h"

class Camera;

using std::complex;
using std::size_t;

enum RunningMode {
    DefaultMode, // No shaders -> bad performance
    ShaderMode // Shaders -> good performance
};

class Window : public sf::RenderWindow {
    public:
        Window(const int &height, const int &width, RunningMode mode);
        void Think();
    protected:
        void PlotMandelbrotSetDefault();
        void PlotMandelbrotSetShaders();

    private:
        unsigned int m_screen_width, m_screen_height;
        sf::RenderTexture m_texture;
        std::unique_ptr<Camera> m_camera;
        sf::Shader m_shader;
        sf::VertexArray m_pixel_map;
        RunningMode m_mode;
        static constexpr int m_max_iterations = 1000;
};