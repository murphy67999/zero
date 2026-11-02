cmake_minimum_required(VERSION 3.16)

project(zero C)

set(CMAKE_C_STANDARD 99)

add_executable(zero
    src/main.c
    src/game.c
    src/player.c
)

target_include_directories(zero PRIVATE
    include
    raylib/include
)

target_link_libraries(zero PRIVATE
    /home/mirak/Documents/zero/raylib/lib/libraylib.a
    m
    X11
)