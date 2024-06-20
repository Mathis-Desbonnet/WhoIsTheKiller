cmake_minimum_required(VERSION 3.28)
project(Cluedo C)

set(CMAKE_C_STANDARD 11)

add_executable(Cluedo main.c
        characters.c
        characters.h
        game.c
        game.h
)
