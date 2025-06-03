#pragma once

#include <qcolor.h>
#include <array>
#include <vector>

#include "../linal/hittable.hpp"

using point = std::array<float, 3>;

struct SceneConfig {
    // цвет фона
    QColor m_ambient_color;
    // координаты точек свечения
    std::vector<point> m_lights;
    //цвета
    std::vector<QColor> m_colors;
    std::vector<std::unique_ptr<HittableIface<float>>> m_objects;

    QColor m_background_color;
    float m_gamma;
    int m_depth;
    std::string m_quality;
    point m_camera_position;
    point m_view_point;
    point m_up_vector;
    float m_zn;
    float m_zf;
    float m_sw;
    float m_sh;
};
