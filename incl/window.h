//
// Created by stott on 8/26/19.
//

#ifndef MANDELBROTGENERATOR_WINDOW_H
#define MANDELBROTGENERATOR_WINDOW_H

#include "camera.h"

class Window {
public:
    Window();
    ~Window();

protected:
    void InitCamera();

private:
    unsigned int m_screen_height = 800;
    unsigned int m_screen_width = 600;
    Camera m_camera;

};


#endif //MANDELBROTGENERATOR_WINDOW_H
