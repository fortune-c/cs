cmake_minimum_required(VERSION 3.16)
project(cs C)

set(CMAKE_C_STANDARD 11)
include_directories(includes)
add_executable(cs
        main.c
        src/MainMemory.c
        src/Ra.c
        src/Cache.c
        src/MemorySystem.c
)
