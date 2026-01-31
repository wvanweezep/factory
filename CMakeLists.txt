cmake_minimum_required(VERSION 4.0)
project(Factory C)

set(CMAKE_C_STANDARD 17)

find_package(raylib CONFIG REQUIRED)

include_directories(PRIVATE include/)

add_executable(Factory main.c
        src/camera.c
        src/tile.c
        src/chunk.c
)

target_link_libraries(Factory raylib)
