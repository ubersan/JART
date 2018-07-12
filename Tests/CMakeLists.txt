cmake_minimum_required(VERSION 3.5.0)
project(tests)

include_directories(${gtest_SOURCE_DIR}/include)

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(renderer_test ${SOURCE_FILES})
target_link_libraries(renderer_test gtest_main)
add_test(NAME test_runner COMMAND test)