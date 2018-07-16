cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_C_COMPILER /usr/bin/clang-6.0)
set(CMAKE_CXX_COMPILER /usr/bin/clang++-6.0)
project(raytracer_root)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

# Is currently needed for all projects, because the
# includes of the RayTracer headers, recursively
# also include the Eigen headers.
include_directories(${PROJECT_ROOT_DIR}/Eigen)

add_subdirectory(RayTracer)
add_subdirectory(ImageIO)
add_subdirectory(Renderer)
add_subdirectory(GoogleTest)
add_subdirectory(Tests)