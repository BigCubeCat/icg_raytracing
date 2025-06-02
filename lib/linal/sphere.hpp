#pragma once

#include <eigen3/Eigen/Dense>
#include "hittable.hpp"

template <typename T>
class HittableSphere : public HittableIface<T> {
   private:
    Eigen::Vector3<T> m_center;
    T m_radius;

    void process_root(T root, const Ray<T>& ray, HitRecord<T>& rec) const {
        rec.t = root;
        rec.m_point = ray.m_origin + ray.m_direction * rec.t;
        rec.m_normal = (rec.m_point - m_center) * (1.0 / m_radius);
    }

   public:
    explicit HittableSphere(const Eigen::Vector3<T>& center, T radius)
        : m_center(center), m_radius(radius) {}
    bool hit(const Ray<T>& ray, T t_min, T t_max,
             HitRecord<T>& rec) const override {
        Eigen::Vector3<T> oc = ray.m_origin - m_center;
        T a = ray.m_direction.dot(ray.m_direction);
        T b = 2.0 * oc.dot(ray.m_direction);
        T c = oc.dot(oc) - (m_radius * m_radius);
        T discriminant = (b * b) - (4 * a * c);

        if (discriminant <= 0) {
            return false;
        }
        T sqrtd = sqrt(discriminant);
        T first_root = (-b - sqrtd) / (2.0 * a);
        if (first_root < t_max && first_root > t_min) {
            this->process_root(first_root, ray, rec);
            return true;
        }
        auto second_root = (-b + sqrtd) / (2.0 * a);
        if (second_root < t_max && second_root > t_min) {
            this->process_root(second_root, ray, rec);
            return true;
        }
        return false;
    }
};
