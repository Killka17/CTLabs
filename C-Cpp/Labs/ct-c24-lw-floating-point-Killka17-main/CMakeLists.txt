cmake_minimum_required(VERSION 3.20)
project(EVM C)

set(CMAKE_C_STANDARD 17)
set(SOURCES main.c src/FloatUtils.c src/Operations.c src/FloatIO.c)

add_executable(EVM ${SOURCES})
