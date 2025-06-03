qt_add_library(scene STATIC scene.cpp scene.hpp)

target_link_libraries(
  scene
  PUBLIC Qt6::Core
         Qt6::Widgets
         Qt6::Gui
         Qt6::Qml
         Qt6::Quick
         Qt6::QuickWidgets
         ${EIGEN3_INCLUDE_DIR})

target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
