cmake_minimum_required(VERSION 3.16)

project(zero C)

set(CMAKE_C_STANDARD 99)

add_executable(zero
    src/main.c
    src/application.c
    src/main_menu.c
    raygui.c
    src/endless.c
    src/player.c
    src/enemy.c
    src/bullet.c
    src/gun.c
    src/array.c
    src/wave_manager.c
)

target_include_directories(zero PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    include
    raylib/include
)

target_link_libraries(zero PRIVATE
    /home/mirak/Documents/zero/raylib/lib/libraylib.a
    m
    X11
)