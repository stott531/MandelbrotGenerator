/*
 * Created by Stephen Ott 8/28/2019
 */
#include "../incl/window.h"

Window::Window() : m_pixel_map(sf::Points, m_screen_height * m_screen_width)
{
    this->create(sf::VideoMode(m_screen_width, m_screen_height), "Mandelbrot Set");
}

void Window::Think()
{
    while (this->isOpen())
    {
        sf::Event event;
        //get all input since the last iteration of the loop
        while (this->pollEvent(event))
        {
            //decide what to do with it
            switch (event.type) {
                // close the window if the close button was pressed
                case sf::Event::Closed:
                    this->close();
                    break;
                default:
                    break;
            }
        }
        this->CalculateMandelbrotSet();

        this->clear();
        this->draw(this->m_pixel_map);
        this->display();
    }
}

void Window::CalculateMandelbrotSet() {
    for (int i = 0; i < m_screen_height; ++i)
    {
        for (int j = 0; j < m_screen_width; ++j)
        {
            complex<double> point((double)j/m_screen_width - 1.5, (double)i/m_screen_height - 0.5);
            complex<double> c(0,0);
            int iter = 0;
            for (; std::abs(c) < 2 && iter < ITERATIONS; ++iter) {
                c = c * c + point;
            }
            sf::Vertex cur_vertex(sf::Vector2f(j, i));

            iter < 30 ? cur_vertex.color = sf::Color::Red : cur_vertex.color = sf::Color::Black;

            this->m_pixel_map[(i * m_screen_width) + j] = cur_vertex;
        }
    }
}
