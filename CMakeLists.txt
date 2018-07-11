cmake_minimum_required(VERSION 3.5.1)

project(raytracer_root)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall)

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

add_subdirectory(RayTracer)
add_subdirectory(Renderer)