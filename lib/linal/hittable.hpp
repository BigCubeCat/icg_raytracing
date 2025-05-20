#pragma once

/*!
 * \brief Интерфейс объекта, обнаружеваемого лучем
*/
#include "hit_record.hpp"
#include "ray.hpp"
template <typename T>
class HittableIface {
   public:
    virtual bool hit(const Ray<T>& ray, T t_min, T t_max,
                     HitRecord<T>& record) const = 0;
};
