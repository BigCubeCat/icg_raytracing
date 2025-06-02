#pragma once

#include <Eigen/Dense>
#include "ray.hpp"

template <typename T>
class Camera {
   public:
    Camera(const Eigen::Vector3<T>& position, const Eigen::Vector3<T>& lookat,
           const Eigen::Vector3<T>& up, T fov_degrees, T aspect_ratio)
        : origin(position),
          lookat(lookat),
          world_up(up.normalized()),
          vfov(fov_degrees),
          aspect_ratio(aspect_ratio) {
        build_camera();
    }

    /*! Вычисляет луч по нормализованным координатам экрана (u, v),
     где u∈[0,1] — горизонтальная координата (слева направо),
     v∈[0,1] — вертикальная (снизу вверх).
    */
    Ray<T> get_ray(T u, T v) const {
        // s и t ∈ [0,1]. s=0 => слева, s=1 => справа. t=0 => снизу, t=1 => сверху.
        Eigen::Vector3f dir =
            lower_left_corner + (u * horizontal) + (v * vertical) - origin;
        return Ray<float>(origin, dir);
    }

    /*!
  * Перестроить камеру, если изменился lookat, up или fov/aspect
  */
    void updateOrientation(const Eigen::Vector3<T>& lookat,
                           const Eigen::Vector3<T>& up, T fov_degrees,
                           T aspect_ratio) {
        this->lookat = lookat;
        world_up = up.normalized();
        vfov = fov_degrees;
        this->aspect_ratio = aspect_ratio;
        build_camera();
    }

    /// Переместить камеру в новую позицию
    void setPosition(const Eigen::Vector3<T>& pos) {
        origin = pos;
        build_camera();
    }

    /// Получить/задать скорость перемещения для реакций на клавиши
    void setMoveSpeed(T s) { move_speed = s; }

    T getMoveSpeed() const { return move_speed; }

    Eigen::Vector3<T> position() const { return origin; }
    Eigen::Vector3<T> front() const {
        return -w;
    }  // направленный вглубь камеры

   private:
    // Параметры камеры
    Eigen::Vector3<T> origin;    // позиция
    Eigen::Vector3<T> lookat;    // точка, на которую смотрим
    Eigen::Vector3<T> world_up;  // вектор “up” в мире (обычно (0,1,0))
    T vfov;                      // полное вертикальное поле зрения в градусах
    T aspect_ratio;              // width / height

    // Внутренние вычисленные величины
    Eigen::Vector3<T> u, v, w;  // ортонормированный базис камеры
    T viewport_height;
    T viewport_width;
    Eigen::Vector3<T> horizontal;
    Eigen::Vector3<T> vertical;
    Eigen::Vector3<T> lower_left_corner;

    // дополнительный параметр: скорость движения (в мировых единицах на клик/шаг)
    T move_speed = 1.0F;

    void build_camera() {
        // 1. Вычисляем новые базисы w, u, v
        // w = нормализованный вектор от origin к lookat, только отрицательный (т.к. вперед = -w)
        w = (origin - lookat).normalized();
        // u = вправо (правило правой руки): u = normalize(up × w)
        u = (world_up.cross(w)).normalized();
        // v = w × u (это уже «верх» в пространстве камеры)
        v = w.cross(u);

        float theta = vfov * M_PI / 180.0F;
        float half_height = std::tan(theta / 2.0F);
        float half_width = aspect_ratio * half_height;

        viewport_height = 2.0F * half_height;
        viewport_width = 2.0F * half_width;

        // Горизонтальный и вертикальный размеры «плоскости проекции»
        horizontal = half_width * 2.0F * u;
        vertical = half_height * 2.0F * v;

        // Нижний левый угол в мировых координатах:
        lower_left_corner = origin - half_width * u - half_height * v - w;
    }
};
