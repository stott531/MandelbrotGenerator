/*
 * Created by Stephen Ott 8/28/2019
 */
#include "../incl/window.h"

Window::Window() : m_pixel_map(sf::Points, m_screen_height * m_screen_width)
{
    // setup a window for us
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
        this->PlotMandelbrotSet();

        this->clear();
        this->draw(this->m_pixel_map);
        this->display();
    }
}

void Window::PlotMandelbrotSet() {
    sf::Vertex cur_vertex;
    complex<double> point, c;
    int iter;

    #pragma omp parallel for collapse(2) private(iter, point, c, cur_vertex)
    for (int i = 0; i < m_screen_height; ++i)
    {
        for (int j = 0; j < m_screen_width; ++j)
        {
            point = {(double)j/m_screen_width*2.1 - 1.5, (double)i/m_screen_height*2.25 - 1.2};
            c = {0,0};
            iter = 0;
            for (; std::abs(c) < 2 && iter < MAX_ITERATIONS; ++iter) {
                c = c * c + point;
            }
            cur_vertex.position = {(float)j, (float)i};
            if (iter >= 25)
            {
                cur_vertex.color = sf::Color::Black;
            }
            else
            {
                cur_vertex.color = sf::Color((255*iter)/500, (255*iter)/300, (255*iter)/30);
            }
            this->m_pixel_map[(i * m_screen_width) + j] = cur_vertex;
        }
    }
}
