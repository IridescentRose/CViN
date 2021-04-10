cmake_minimum_required(VERSION 3.17)
project(CViN C)
set(CMAKE_C_STANDARD 99)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(CViN main.c src/WindowContext.h src/WindowContext.c src/Sprite.h src/Sprite.c)
target_link_libraries(CViN ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

