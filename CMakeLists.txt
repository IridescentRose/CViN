cmake_minimum_required(VERSION 3.17)
project(CViN C)
set(CMAKE_C_STANDARD 99)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})

add_executable(CViN main.c src/WindowContext.h src/WindowContext.c src/Sprite.h src/Sprite.c src/AudioClip.h src/AudioClip.c)
target_link_libraries(CViN ${SDL2MIXER_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2MIXER_LIBRARY} SDL2_mixer)

