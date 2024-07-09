cmake_minimum_required(VERSION 3.28)
project(Cluedo C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-module)

set(SDL2_PATH "C:/Users/Mathi/Downloads/SDL2-devel-2.30.3-mingw/SDL2-2.30.3/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "C:/Users/Mathi/Downloads/SDL2_ttf-devel-2.22.0-mingw/SDL2_ttf-2.22.0/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

add_executable(Cluedo main.c
        characters.c
        characters.h
        game.c
        game.h
)

target_link_libraries(Cluedo ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})