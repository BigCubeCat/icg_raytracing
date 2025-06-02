add_library(
  linal STATIC
  camera.hpp
  hit_record.hpp
  hittable.hpp
  light.hpp
  quad.hpp
  shading.hpp
  ray.hpp
  sphere.hpp
  triangle.hpp)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
target_link_libraries(linal PRIVATE m Eigen3::Eigen)
target_include_directories(linal PUBLIC ${EIGEN3_INCLUDE_DIR})
