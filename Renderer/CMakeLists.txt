cmake_minimum_required(VERSION 3.12.0)
project(renderer)

file(GLOB SOURCE_FILES src/*.cpp)
include_directories(include)
include_directories(${PROJECT_ROOT_DIR}/RayTracer/include)

add_executable(renderer ${SOURCE_FILES})
target_link_libraries(renderer raytracer)