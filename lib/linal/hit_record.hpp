#pragma once

#include <Eigen/Dense>
#include "ray.hpp"

/*!
 * \brief Результат пересечения Ray и HittableIface
*/
template <typename T>
struct HitRecord {
    T t;
    Eigen::Vector3<T> m_point;
    Eigen::Vector3<T> m_normal;

    bool
        front_face;  // чтобы знать, с какой стороны треугольник «смотрит» на луч

    // Простейшие функции для ориентации нормали по направлению луча:
    void set_face_normal(const Ray<T>& r,
                         const Eigen::Vector3<T>& outward_normal) {
        front_face = (r.m_direction.dot(outward_normal) < 0);
        m_normal = front_face ? outward_normal : -outward_normal;
    }

    // Предположим, что у каждого объекта (или материала) можно взять цвет/коэффициенты.
    Eigen::Vector3<T> albedo = {1, 1, 1};  // просто цвет объекта (диффузный)
    float shininess = 32.0F;               // коэффициент блеска (для Phong)
};
