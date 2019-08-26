//
// Created by stott on 8/26/19.
//

#ifndef MANDELBROTGENERATOR_CAMERA_H
#define MANDELBROTGENERATOR_CAMERA_H


class Camera {
  public:
    Camera();
    ~Camera();

    void Pan();

  private:
    double m_zoom_factor = 1;
    bool m_is_panning;
};


#endif //MANDELBROTGENERATOR_CAMERA_H
