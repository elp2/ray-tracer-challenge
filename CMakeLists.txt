cmake_minimum_required(VERSION 3.7)
project(ray-tracer-challenge)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if (WIN32)
set(SDL2_DIR "C://Users/edwar/Documents/Dev/SDL2-2.0.10")
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library (primitives
    src/primitives/color.cc
    src/primitives/intersection.cc
    src/primitives/intersections.cc
    src/primitives/matrix.cc
    src/primitives/ray.cc
    src/primitives/transformation.cc
    src/primitives/tuple.cc)
target_include_directories(primitives PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library (display
    src/display/crc.cc
    src/display/canvas.cc
    src/display/png_writer.cc
    src/display/ppm_writer.cc)
target_link_libraries(display z)
target_include_directories(display PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library (lights
    src/lights/point_light.cc)
target_link_libraries(lights primitives)
target_include_directories(lights PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library (patterns
    src/patterns/blended_pattern.cc
    src/patterns/gradient_pattern.cc
    src/patterns/pattern.cc
    src/patterns/ring_pattern.cc
    src/patterns/perturbed_pattern.cc
    src/patterns/striped_pattern.cc
    src/patterns/three_d_pattern.cc)
target_link_libraries(patterns primitives)
target_include_directories(patterns PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library (shapes
    src/shapes/bounds.cc
    src/shapes/cone.cc
    src/shapes/constructive_solid_geometry.cc
    src/shapes/cube.cc
    src/shapes/cylinder.cc
    src/shapes/group.cc
    src/shapes/material.cc
    src/shapes/obj_parser.cc    
    src/shapes/plane.cc
    src/shapes/shape.cc
    src/shapes/smooth_triangle.cc
    src/shapes/sphere.cc
    src/shapes/triangle.cc)
target_link_libraries(shapes lights)
target_link_libraries(shapes patterns)
target_link_libraries(shapes primitives)
target_include_directories(shapes PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library (scene
    src/scene/camera.cc
    src/scene/prepared_computation.cc
    src/scene/view_transformation.cc
    src/scene/world.cc)
target_link_libraries(scene lights)
target_link_libraries(scene primitives)
target_link_libraries(scene shapes)
find_package (Threads)
target_link_libraries (scene Threads::Threads)
target_include_directories(scene PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_library (imgui
    imgui/examples/imgui_impl_opengl3.cpp
    imgui/examples/imgui_impl_sdl.cpp
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(imgui PUBLIC ${PROJECT_SOURCE_DIR}/imgui)
target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIR})
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=<SDL_opengl.h>  GL_GLEXT_PROTOTYPES=1)
target_link_libraries(imgui GL)
target_link_libraries(imgui ${SDL2_LIBRARIES})

add_library (gui
    src/gui/gui.cc)
target_include_directories(gui PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(gui imgui)
target_link_libraries(gui GL)
target_link_libraries(gui ${SDL2_LIBRARIES})

add_executable(rtc WIN32
    src/exe/main.cc)
target_link_libraries(rtc primitives display)

add_executable(particle WIN32
    src/exe/particle.cc)
target_link_libraries(particle primitives display)

add_executable(clock WIN32
    src/exe/clock.cc)
target_link_libraries(clock primitives display)

add_executable(sphere_shadow WIN32
    src/exe/sphere_shadow.cc)
target_link_libraries(sphere_shadow primitives display shapes)

add_executable(sphere_lit WIN32
    src/exe/sphere_lit.cc)
target_link_libraries(sphere_lit primitives display shapes lights)

add_executable(chapter7 WIN32
    src/exe/chapter7.cc)
target_link_libraries(chapter7 primitives display shapes lights scene)

add_executable(chapter8_shadows WIN32
    src/exe/chapter8_shadows.cc)
target_link_libraries(chapter8_shadows primitives display shapes lights scene)

add_executable(chapter9_plane WIN32
    src/exe/chapter9_plane.cc)
target_link_libraries(chapter9_plane primitives display shapes lights scene)

add_executable(chapter10_patterns WIN32
    src/exe/chapter10_patterns.cc)
target_link_libraries(chapter10_patterns patterns primitives display shapes lights scene)

add_executable(chapter11 WIN32
    src/exe/chapter11.cc)
target_link_libraries(chapter11 patterns primitives display shapes lights scene)

add_executable(chapter12 WIN32
    src/exe/chapter12.cc)
target_link_libraries(chapter12 patterns primitives display shapes lights scene)

add_executable(chapter13 WIN32
    src/exe/chapter13.cc)
target_link_libraries(chapter13 patterns primitives display shapes lights scene)

add_executable(chapter14 WIN32
    src/exe/chapter14.cc)
target_link_libraries(chapter14 patterns primitives display shapes lights scene)

add_executable(chapter15 WIN32
    src/exe/chapter15.cc)
target_link_libraries(chapter15 patterns primitives display shapes lights scene)

add_executable(chapter16 WIN32
    src/exe/chapter16.cc)
target_link_libraries(chapter16 patterns primitives display shapes lights scene)

add_executable(write_png WIN32
    src/exe/write_png.cc)
target_link_libraries(write_png patterns primitives display shapes lights scene)

add_executable(elptracer WIN32
    src/exe/elptracer.cc)
target_link_libraries(elptracer patterns primitives display shapes lights scene gui)

# Below is from googletest README.md.
# Download and unpack googletest at configure time.
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Tests
add_executable(tests
    src/display/canvas_test.cc
    src/display/crc_test.cc
    src/display/ppm_writer_test.cc
    src/lights/point_light_test.cc
    src/patterns/pattern_test.cc
    src/patterns/striped_pattern_test.cc
    src/primitives/color_test.cc
    src/primitives/intersection_test.cc
    src/primitives/matrix_test.cc
    src/primitives/ray_test.cc
    src/primitives/transformation_test.cc
    src/primitives/tuple_test.cc
    src/scene/camera_test.cc
    src/scene/prepared_computation_test.cc
    src/scene/view_transformation_test.cc
    src/scene/world_test.cc
    src/shapes/bounds_test.cc
    src/shapes/cone_test.cc
    src/shapes/constructive_solid_geometry_test.cc
    src/shapes/cube_test.cc
    src/shapes/cylinder_test.cc
    src/shapes/group_test.cc
    src/shapes/material_test.cc
    src/shapes/obj_parser_test.cc
    src/shapes/plane_test.cc
    src/shapes/shape_test.cc
    src/shapes/smooth_triangle_test.cc
    src/shapes/sphere_test.cc
    src/shapes/triangle_test.cc)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tests gtest_main)
target_link_libraries(tests gmock)
target_link_libraries(tests display)
target_link_libraries(tests lights)
target_link_libraries(tests primitives)
target_link_libraries(tests scene)
target_link_libraries(tests shapes)
add_test(NAME basic_tests COMMAND tests)