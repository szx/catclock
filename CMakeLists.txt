cmake_minimum_required(VERSION 3.26)
project(catclock)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-fpermissive)

add_executable(catclock main.cpp
        catback.h
        eyes.h
        libc.h
        draw.h
        fmt.h
        qlock.h
        lock.h
        draw.cpp
        libc.cpp
        event.cpp
        port.cpp)
