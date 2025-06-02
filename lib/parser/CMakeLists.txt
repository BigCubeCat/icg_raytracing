add_library(parser STATIC objects.hpp object_parser.hpp object_parser.cpp
                          parser.hpp parser.cpp)
target_link_libraries(parser PUBLIC m linal Eigen3::Eigen)

target_compile_definitions(parser PRIVATE BOOST_SPIRIT_THREADSAFE)

target_include_directories(parser PUBLIC ${Boost_INCLUDE_DIRS}
                                         ${EIGEN3_INCLUDE_DIR})
