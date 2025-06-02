// light.hpp
#pragma once
#include <Eigen/Dense>

struct PointLight {
    Eigen::Vector3f position;
    Eigen::Vector3f intensity;
    // intensity == RGB-интенсивность источника (например, (1,1,1) = белый чистый свет).
    // Можно хранить float power; своими коэффициентами скалировать intensity.
};
