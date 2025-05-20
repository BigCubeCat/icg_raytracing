#pragma once

#include <Eigen/Dense>
#include "Eigen/src/Core/Matrix.h"

/*!
 * \brief тип луча
*/
template <typename T>
struct Ray {
    Eigen::Vector3<T> m_origin;
    Eigen::Vector3<T> m_direction;
    explicit Ray(const Eigen::Vector3<T>& origin, const Eigen::Vector3<T>& dir)
        : m_origin(origin), m_direction(dir.normalized()) {}
};
