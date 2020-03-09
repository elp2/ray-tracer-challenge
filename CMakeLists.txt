cmake_minimum_required(VERSION 3.7)
project(ray-tracer-challenge)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_library (rtc_lib
    src/primitives/color.cc
    src/primitives/tuple.cc)
target_include_directories(rtc_lib PUBLIC ${PROJECT_SOURCE_DIR}/src)


add_executable(rtc WIN32
    src/main.cc)
target_link_libraries(rtc rtc_lib)


add_executable(particle WIN32
    src/particle.cc)
target_link_libraries(particle rtc_lib)


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
    src/primitives/color_test.cc
    src/primitives/tuple_test.cc)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tests gtest_main)
target_link_libraries(tests gmock)
target_link_libraries(tests rtc_lib)
add_test(NAME basic_tests COMMAND tests)