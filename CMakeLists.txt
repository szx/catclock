cmake_minimum_required(VERSION 3.26)
project(catclock)

set(CMAKE_CXX_STANDARD 17)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

find_package(OpenAL REQUIRED MODULE)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

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
target_link_libraries(catclock PRIVATE sfml-graphics)
target_link_libraries(catclock PRIVATE "${OPENAL_LIBRARY}")
