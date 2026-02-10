cmake_minimum_required(VERSION 3.31.6)
project(Factory C)

set(CMAKE_C_STANDARD 17)

find_package(raylib CONFIG REQUIRED)

include_directories(PRIVATE include/)

file(GLOB_RECURSE MAIN_SOURCES src/*.c)
add_executable(Factory main.c ${MAIN_SOURCES})

file(GLOB_RECURSE TEST_SOURCES test/*.c)
add_executable(UnitTest ${TEST_SOURCES} ${MAIN_SOURCES} test/unitt/assert.c)

target_link_libraries(Factory raylib)
