add_library(linal STATIC point.hpp)
target_link_libraries(linal PRIVATE m)

target_include_directories(linal PUBLIC ${EIGEN3_INCLUDE_DIR})
