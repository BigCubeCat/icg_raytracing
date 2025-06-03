cmake_minimum_required(VERSION 3.19)
project(icg_raytracing LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Настройки Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.88 REQUIRED)
if(Boost_FOUND)
  message(STATUS "Boost version: ${Boost_VERSION}")
  message(STATUS "Boost includes: ${Boost_INCLUDE_DIRS}")
  message(STATUS "Boost libraries: ${Boost_LIBRARY_DIRS}")
else()
  message(FATAL_ERROR "Boost not found!")
endif()

find_package(Eigen3 REQUIRED)
find_package(
  Qt6 6.5 REQUIRED
  COMPONENTS Core
             Widgets
             Gui
             Qml
             Quick
             QuickWidgets
             QuickControls2
             WebEngineWidgets)
find_package(OpenMP)
if(OPENMP_FOUND)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

message(STATUS "Using Qt version: ${Qt6_VERSION}")

qt6_add_resources(RESOURCES resources.qrc)

qt_standard_project_setup()

qt_add_executable(icg_raytracing WIN32 MACOSX_BUNDLE src/main.cpp ${RESOURCES})

target_link_libraries(
  icg_raytracing
  PRIVATE Qt6::Core
          Qt6::Widgets
          Qt6::Gui
          Qt6::Qml
          Qt6::Quick
          Qt6::QuickWidgets
          Qt6::QuickControls2
          model
          mainwindow)

target_include_directories(icg_raytracing PRIVATE ${Boost_INCLUDE_DIRS})

target_compile_definitions(icg_raytracing PRIVATE BOOST_SPIRIT_THREADSAFE)

include(GNUInstallDirs)

install(
  TARGETS icg_raytracing
  BUNDLE DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_generate_deploy_app_script(TARGET icg_raytracing OUTPUT_SCRIPT deploy_script
                              NO_UNSUPPORTED_PLATFORM_ERROR)
install(SCRIPT ${deploy_script})
add_subdirectory(lib/editor)
add_subdirectory(lib/model)
add_subdirectory(lib/mainwindow)
add_subdirectory(lib/canvas)
add_subdirectory(lib/canvaspanel)
add_subdirectory(lib/linal)
add_subdirectory(lib/parser)
add_subdirectory(lib/scene)
