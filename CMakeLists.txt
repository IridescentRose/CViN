cmake_minimum_required(VERSION 3.17)
project(CViN C)

find_package(SDL2 REQUIRED)
include_directories(CViN ${SDL2_INCLUDE_DIRS})


set(CMAKE_C_STANDARD 99)

add_executable(CViN main.c src/WindowContext.h src/WindowContext.c)
target_link_libraries(CViN ${SDL2_LIBRARIES})