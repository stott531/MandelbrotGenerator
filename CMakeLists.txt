cmake_minimum_required(VERSION 3.13)
project(MandelbrotGenerator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules")
set(CMAKE_CXX_FLAGS "-O3")

find_package(SFML 2 COMPONENTS
        system
        window
        graphics
        REQUIRED)

add_executable(MandelbrotGenerator
        incl/window.h
        incl/camera.h

        src/main.cpp

        src/window.cpp
        src/camera.cpp
        )

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(MandelbrotGenerator PUBLIC OpenMP::OpenMP_CXX)
endif()

if(SFML_FOUND)
    include_directories("/usr/include")
    target_link_libraries(MandelbrotGenerator PUBLIC
            sfml-graphics
            sfml-window
            sfml-system)
endif()
