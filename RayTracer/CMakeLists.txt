cmake_minimum_required(VERSION 3.5.1)
project(raytracer)

file(GLOB SOURCE_FILES src/*.cpp)

include_directories(include/RayTracer)

add_library(raytracer SHARED ${SOURCE_FILES})