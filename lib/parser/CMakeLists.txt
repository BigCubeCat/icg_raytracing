add_library(parser STATIC spline.hpp spline.cpp point.hpp)
target_link_libraries(paraser PRIVATE m)

target_compile_definitions(parser PRIVATE BOOST_SPIRIT_THREADSAFE)

target_include_directories(parser PUBLIC ${Boost_INCLUDE_DIRS})
