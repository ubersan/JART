cmake_minimum_required(VERSION 3.12.0)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
project(raytracer_root)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR})

# Is currently needed for all projects, because the
# includes of the RayTracer headers, recursively
# also include the Eigen headers.
include_directories(${PROJECT_ROOT_DIR}/Eigen)

add_subdirectory(RayTracer)
add_subdirectory(Renderer)
add_subdirectory(GoogleTest)
add_subdirectory(Tests)