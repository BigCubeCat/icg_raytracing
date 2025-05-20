#pragma once

#include <Eigen/Dense>

/*!
 * \brief Результат пересечения Ray и HittableIface
*/
template <typename T>
struct HitRecord {
    T t;
    Eigen::Vector3<T> m_point;
    Eigen::Vector3<T> m_normal;
};
