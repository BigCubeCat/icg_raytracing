// shading.hpp
#pragma once
#include <eigen3/Eigen/Dense>
#include "hit_record.hpp"
#include "light.hpp"
#include "ray.hpp"

/// Возвращает цвет (RGB) в точке пересечения, используя Phong-модель.
/// - hit_rec содержит point, normal, albedo и shininess.
/// - ray_in — падающий луч.
/// - light — единичный точечный источник света.
/// - ambient_coeff — коэффициент «окружающего» (ambient) света в сцене (напр. 0.1).
template <typename T>
Eigen::Vector3<T> phong_shade(const HitRecord<T>& hit_rec, const Ray<T>& ray_in,
                              const PointLight& light, T ambient_coeff = 0.1F) {
    // 1) Ambient (многократный по умолчанию)
    Eigen::Vector3<T> ambient =
        ambient_coeff * hit_rec.albedo.cwiseProduct(light.intensity);

    // 2) Diffuse
    Eigen::Vector3<T> light_dir =
        (light.position - hit_rec.m_point).normalized();
    float diff = std::max(hit_rec.m_normal.dot(light_dir), 0.0F);
    Eigen::Vector3<T> diffuse =
        diff * hit_rec.albedo.cwiseProduct(light.intensity);

    // 3) Specular
    Eigen::Vector3<T> view_dir = (-ray_in.m_direction).normalized();
    Eigen::Vector3<T> reflect_dir =
        ((2.0F * hit_rec.m_normal.dot(light_dir) * hit_rec.m_normal) -
         light_dir)
            .normalized();
    auto spec =
        std::pow(std::max(view_dir.dot(reflect_dir), 0.0F), hit_rec.shininess);
    // Пусть для простоты укажем белый спекуляр: цвет = intensity
    Eigen::Vector3<T> specular = spec * light.intensity;

    return ambient + diffuse + specular;
}
