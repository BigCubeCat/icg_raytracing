#pragma once

#include <eigen3/Eigen/Dense>
#include "hit_record.hpp"
#include "hittable.hpp"
#include "ray.hpp"

/*!
 * \brief Квадрат
*/
template <typename T>
class HittableQuad : public HittableIface<T> {
    Eigen::Vector3<T> m_v0, m_v1, m_v2, m_v3;
    Eigen::Vector3<T> m_normal;
    Eigen::Vector3<T> m_edge1, m_edge2, m_edge3, m_edge4;

   public:
    HittableQuad(const Eigen::Vector3<T>& a, const Eigen::Vector3<T>& b,
                 const Eigen::Vector3<T>& c, const Eigen::Vector3<T>& d)
        : m_v0(a), m_v1(b), m_v2(c), m_v3(d) {
        // Вычисляем нормаль плоскости
        Eigen::Vector3<T> diag1 = m_v1 - m_v0;
        Eigen::Vector3<T> diag2 = m_v3 - m_v0;
        m_normal = diag1.cross(diag2);
        m_normal.normalize();
        // Предварительно вычисляем векторы ребер
        m_edge1 = m_v1 - m_v0;
        m_edge2 = m_v2 - m_v1;
        m_edge3 = m_v3 - m_v2;
        m_edge4 = m_v0 - m_v3;
    }

    bool hit(const Ray<T>& ray, T t_min, T t_max,
             HitRecord<T>& rec) const override {
        // Проверка пересечения с плоскостью
        auto denom = m_normal.dot(ray.m_direction);
        if (fabs(denom) < 1e-8)
            return false;

        Eigen::Vector3<T> vec_to_plane = m_v0 - ray.m_origin;
        auto t = vec_to_plane.dot(m_normal) / denom;

        if (t < t_min || t > t_max)
            return false;

        auto point = ray.m_origin + (ray.m_direction * t);

        // Проверка принадлежности точки четырехугольнику
        if (!is_point_inside_quad(point))
            return false;

        rec.t = t;
        rec.m_point = point;
        rec.m_normal = m_normal;
        return true;
    }

   private:
    bool check_cross(const Eigen::Vector3<T>& p, const Eigen::Vector3<T>& v,
                     const Eigen::Vector3<T>& edge) const {
        return static_cast<bool>(edge.cross(p - v).dot(m_normal) >= 0);
    }

    bool is_point_inside_quad(const Eigen::Vector3<T>& p) const {
        return check_cross(p, m_v0, m_edge1) && check_cross(p, m_v1, m_edge2) &&
               check_cross(p, m_v2, m_edge3) && check_cross(p, m_v3, m_edge4);
    }
};
