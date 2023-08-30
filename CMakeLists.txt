cmake_minimum_required(VERSION 3.26)
project(homework3 C)

set(CMAKE_C_STANDARD 99)

add_executable(homework3 main.c
        BmpProcessor.c
        PixelProcessor.c
        PpmProcessor.c)
