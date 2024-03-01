cmake_minimum_required(VERSION 3.26)
project(phys-lab-1)
find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_executable(phys-lab-1 src/main.cpp
        src/window.h
        src/window.cpp
        src/testList.h
        src/testList.cpp
        src/utilityFuncs.hpp)
target_link_libraries(phys-lab-1 PUBLIC imgui imgui-glfw imgui-opengl3 OpenGL glfw)