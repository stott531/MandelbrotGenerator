/*
 * Created by Stephen Ott 8/28/2019
 */
#include "../incl/window.h"

#include <SFML/System/Time.hpp>
#include <iostream>

Window::Window(const int &height, const int &width, RunningMode mode) : m_camera(std::make_unique<Camera>(height, width, this)),
                                                                        m_screen_width(width),
                                                                        m_screen_height(height),
                                                                        m_mode(mode)
{
    // setup a window for us
    this->create(sf::VideoMode(m_screen_width, m_screen_height), "Mandelbrot Set");
    if (!m_shader.loadFromFile("../src/mandelbrot_shader.frag", sf::Shader::Fragment))
    {
        /*shader.setUniform("height", (float) m_screen_height);
        shader.setUniform("height", (float) m_screen_width);
        shader.setUniform("zoom_factor", (float) m_camera->GetZoom());
        shader.setUniform("max_iterations", 50);*/
        std::cout << "Could not open shader";
        exit(1);
    }
    this->m_texture.create(m_screen_width, m_screen_height);
}

void Window::Think()
{

    while (this->isOpen())
    {
        sf::Event event{};
        sf::Clock clock;
        float lastTime = 0;

        //get all input since the last iteration of the loop
        while (this->pollEvent(event))
        {
            //decide what to do with it
            switch (event.type) {
                // close the window if the close button was pressed
                case sf::Event::Closed:
                    this->close();
                    break;
                case sf::Event::MouseWheelScrolled:
                    this->m_camera->Zoom(event.mouseWheelScroll);
                case sf::Event::MouseButtonPressed:
                    this->m_camera->TogglePanning(event.mouseButton);
                case sf::Event::MouseMoved:
                    this->m_camera->Pan(event.mouseMove);
                default:
                    break;
            }
        }

        // clear the display, draw the image, show the image
        this->clear();

        if (this->m_mode == DefaultMode) PlotMandelbrotSetDefault();
        else PlotMandelbrotSetShaders();

        float currentTime = clock.getElapsedTime().asSeconds();
        float fps = 1.f / (currentTime);
        clock.restart();
        this->display();
    }
}

void Window::PlotMandelbrotSetDefault() {
    // initialize variables outside loops to save memory
    sf::Vertex cur_vertex;
    complex<float> point, c;
    int i , j, iter;

    // call to openMP to distribute computations
    #pragma omp parallel for num_threads(20) collapse(2) private(iter, point, c, cur_vertex)

    // for each row
    for (i = 0; i < m_screen_height; ++i)
    {
        // for each pixel in the row
        for (j = 0; j < m_screen_width; ++j)
        {
            // use rvalue references to initialize values
            point = {static_cast<float>((float)j/m_screen_width*this->m_camera->GetZoom() - m_camera->h_shift),
                     static_cast<float>((float)i/m_screen_height*this->m_camera->GetZoom() - m_camera->k_shift)};
            c = {0,0};
            iter = 0;

            // iterate while c is smaller than 2
            // if abs(c) > 2, the sequence diverges
            // make use of property |a+bi| == sqrt(a^2+b^2)
            for (; c.real() * c.real() + c.imag() * c.imag() < 4 && iter < MAX_ITERATIONS; ++iter)
            {
                c = c * c + point;
            }
            cur_vertex.position = {(float)j, (float)i};

            // this controls the precision of the drawing
            if (iter >= MAX_ITERATIONS)
            {
                cur_vertex.color = sf::Color::Black;
            }
            else
            {
                // calculates the color gradiant
                cur_vertex.color = sf::Color((255*iter)/30, (255*iter)/300, (255*iter)/300);
            }
            // emplaces the vertex into the pixel map
            this->m_pixel_map[(i * m_screen_width) + j] = cur_vertex;
        }
    }
    this->draw(this->m_pixel_map);
}

void Window::PlotMandelbrotSetShaders() {
    sf::Sprite sprite(this->m_texture.getTexture());
    this->m_shader.setUniform("height", (float)this->m_screen_height);
    this->m_shader.setUniform("width", (float)this->m_screen_width);
    this->m_shader.setUniform("zoom_factor", this->m_camera->GetZoom());
    this->m_shader.setUniform("max_iterations", MAX_ITERATIONS);
    this->m_shader.setUniform("texture", this->m_texture.getTexture());
    this->m_shader.setUniform("h_shift", this->m_camera->h_shift);
    this->m_shader.setUniform("k_shift", this->m_camera->k_shift);

    this->draw(sprite, &m_shader);
}
