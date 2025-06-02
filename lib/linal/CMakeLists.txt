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
target_link_libraries(linal PRIVATE m)
target_include_directories(linal PUBLIC ${EIGEN3_INCLUDE_DIR})
