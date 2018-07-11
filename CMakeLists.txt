cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_C_COMPILER /usr/bin/clang-6.0)
set(CMAKE_CXX_COMPILER /usr/bin/clang++-6.0)
project(raytracer_root)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)
set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# Is currently needed for all projects, because the
# includes of the RayTracer headers, recursively
# also include the Eigen headers into the Renderer executable.
# This can be improved by providing an Eigen-less interface between
# the Renderer and the RayTracer library.
include_directories(${PROJECT_ROOT_DIR}/Eigen)

add_subdirectory(RayTracer)
add_subdirectory(Renderer)