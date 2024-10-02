cmake_minimum_required(VERSION 3.27)
project(lab2 C)

set(CMAKE_C_STANDARD 17)

include_directories("/usr/include/x86_64-linux-gnu/libswresample")
link_directories("/usr/lib/x86_64-linux-gnu")

include_directories("/usr/include/x86_64-linux-gnu/libavformat")
link_directories("/usr/lib/x86_64-linux-gnu")

include_directories("/usr/include/x86_64-linux-gnu/libavcodec")
link_directories("/usr/lib/x86_64-linux-gnu")


add_executable(lab2 main.c
        myFfmpeg.c
        myFftw.c)

target_link_libraries(lab2 avcodec avformat avutil fftw3 swresample)
