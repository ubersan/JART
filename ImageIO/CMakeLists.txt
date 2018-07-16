cmake_minimum_required(VERSION 3.5.0)
project(imageio)

file(GLOB SOURCE_FILES src/*.cpp)
include_directories(include)
include_directories(${PROJECT_ROOT_DIR}/RayTracer/include)

add_library(imageio SHARED ${SOURCE_FILES})
target_link_libraries(imageio raytracer)