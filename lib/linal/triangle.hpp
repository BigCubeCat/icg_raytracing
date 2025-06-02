#pragma once

#include <limits>
#include "hit_record.hpp"
#include "hittable.hpp"
#include "ray.hpp"

/*!
 * \brief Треугольник
*/
template <typename T>
class HittableTriangle : public HittableIface<T> {
    Eigen::Vector3<T> m_v0, m_v1, m_v2;
    Eigen::Vector3<T> m_normal;

   public:
    HittableTriangle(const Eigen::Vector3<T>& a, const Eigen::Vector3<T>& b,
                     const Eigen::Vector3<T>& c)
        : m_v0(a), m_v1(b), m_v2(c) {
        m_normal = (m_v1 - m_v0).cross(m_v2 - m_v0);
        m_normal.normalize();
    }

    bool hit(const Ray<T>& ray, T t_min, T t_max,
             HitRecord<T>& rec) const override {
        const Eigen::Vector3<T> edge1 = m_v1 - m_v0;
        const Eigen::Vector3<T> edge2 = m_v2 - m_v0;
        const Eigen::Vector3<T> h = ray.m_direction.cross(edge2);
        const T a = edge1.dot(h);

        if (std::fabs(a) <= std::numeric_limits<T>::epsilon())
            return false;

        const T f = 1.0 / a;
        const Eigen::Vector3<T> s = ray.m_origin - m_v0;
        const T u = f * s.dot(h);

        if (u < 0.0 || u > 1.0)
            return false;

        const Eigen::Vector3<T> q = s.cross(edge1);
        const T v = f * ray.m_direction.dot(q);

        if (v < 0.0 || u + v > 1.0)
            return false;

        const T t = f * edge2.dot(q);

        if (t > t_min && t < t_max) {
            rec.t = t;
            rec.m_point = ray.m_origin + ray.m_direction * t;
            rec.m_normal = m_normal;
            return true;
        }
        return false;
    }
};
