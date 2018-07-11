cmake_minimum_required(VERSION 3.5.1)
project(renderer)

file(GLOB SOURCE_FILES src/*.cpp)
include_directories(${PROJECT_ROOT_DIR}/RayTracer/include)

add_executable(renderer ${SOURCE_FILES})
target_link_libraries(renderer raytracer)