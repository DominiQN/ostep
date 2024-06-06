cmake_minimum_required(VERSION 3.28)
project(ostep C)

set(CMAKE_C_STANDARD 90)

add_executable(ostep main.c
        my/cpu-api/q2.c)
