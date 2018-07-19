cmake_minimum_required(VERSION 3.12.0)
project(raytracer)

file(GLOB SOURCE_FILES src/*.cpp)
include_directories(include/RayTracer)

add_library(raytracer SHARED ${SOURCE_FILES})