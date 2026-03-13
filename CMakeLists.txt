cmake_minimum_required(VERSION 4.1)
project(cs C)

set(CMAKE_C_STANDARD 11)
add_executable(cs main.c
        main.c
        src/MainMemory.c
        include/MainMemory.h
        src/Ra.c
        include/Ra.h
        )
