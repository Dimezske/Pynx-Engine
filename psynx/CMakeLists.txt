cmake_minimum_required(VERSION 3.16)
project(PysnxEngine)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
    test.cpp
    src/raygui_impl.cpp
)

include_directories(headers)

find_package(raylib REQUIRED)
if(NOT raylib_FOUND)
    message(FATAL_ERROR "Raylib not found")
endif()

add_executable(psynx ${SOURCE_FILES})

target_link_libraries(psynx PRIVATE raylib m pthread dl rt GL X11)
