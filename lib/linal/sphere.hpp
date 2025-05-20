#pragma once

#include <Eigen/Dense>
#include "Eigen/src/Core/Matrix.h"
#include "hittable.hpp"

template <typename T>
class Sphere : public HittableIface<T> {
   private:
    Eigen::Vector3<T> m_center;
    T m_radius;

    void process_root(T root, const Ray<T>& ray, HitRecord<T>& rec) {
        rec.t = root;
        rec.point = ray.origin + ray.direction * rec.t;
        rec.normal = (rec.point - m_center) * (1.0 / m_radius);
    }

   public:
    explicit Sphere(const Eigen::Vector3<T>& center, T radius)
        : m_center(center), m_radius(radius) {}
    bool hit(const Ray<T>& ray, T t_min, T t_max,
             HitRecord<T>& rec) const override {
        Eigen::Vector3<T> oc = ray.origin - center;
        auto a = ray.direction.dot(ray.direction);
        auto b = 2.0 * oc.dot(ray.direction);
        auto c = oc.dot(oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;

        if (discriminant <= 0) {
            return false;
        }
        auto sqrtd = sqrt(discriminant);
        auto first_root = (-b - sqrtd) / (2.0 * a);
        if (first_root < t_max && first_root > t_min) {
            process_root(first_root, ray, rec);
            return true;
        }
        auto second_root = (-b + sqrtd) / (2.0 * a);
        if (second_root < t_max && second_root > t_min) {
            process_root(second_root, ray, rec);
            return true;
        }
        return false;
    }
};
