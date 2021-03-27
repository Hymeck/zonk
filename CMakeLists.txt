cmake_minimum_required(VERSION 3.17)
project(zonk C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(zonk
        src/client.console/main.c)
