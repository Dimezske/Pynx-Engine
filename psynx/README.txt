// Psynx Engine 0.01v-Alpha README File
// C++ + Raylib.h

how to compile
--------------
g++ -std=c++17 \
    test.cpp \
    src/raygui_impl.cpp \
    -Iheaders \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
    -o psynx



###NEWER
g++ -std=c++17 \
    test.cpp \
    src/camera_module.cpp \
    src/terrain_renderer.cpp \
    src/topology.cpp \
    src/raygui_impl.cpp \
    -Iheaders \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
    -o psynx



Change-LOG
----------
- Implimented Engine (includes Ecludian 3d Space)
- Camera movement
- Topology
- Camera settings control tab
- Image upload to land mass topology

- Neat file Structure for the projects reference
_________________ FILE STRUCTURE _______________

psynx/
├── CMakeLists.txt
├── headers/
│   ├── camera_ui.hpp
│   ├── terrain_renderer.hpp
│   └── topology.hpp
├── shaders/
│   ├── terrain.fs
│   └── terrain.vs
├── src/
│   ├── camera_ui.cpp
│   ├── terrain_renderer.cpp
│   ├── topology.cpp
│   └── raygui_impl.cpp
└── test.cpp



_________________ CMAKE ________________________

cmake_minimum_required(VERSION 3.10)
project(PysnxEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(headers)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Source files
set(SOURCES
    test.cpp
    src/topology.cpp
    src/terrain_renderer.cpp
    src/camera_ui.cpp
    src/raygui_impl.cpp
)

# Find raylib
find_package(raylib REQUIRED)  # You need raylib installed

# Add executable
add_executable(psynx ${SOURCES})

# Link libraries
target_link_libraries(psynx raylib m pthread dl GL rt X11)

___________________ CMAKE WITH SHADERS ____________________

cmake_minimum_required(VERSION 3.10)
project(PysnxEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(headers)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Source files
set(SOURCES
    test.cpp
    src/topology.cpp
    src/terrain_renderer.cpp
    src/camera_ui.cpp
    src/raygui_impl.cpp
)

# Find raylib
find_package(raylib REQUIRED)  # Make sure raylib is installed

# Add executable
add_executable(psynx ${SOURCES})

# Link libraries
target_link_libraries(psynx raylib m pthread dl GL rt X11)

# -------------------------------
# Copy shaders folder to build dir
# -------------------------------
add_custom_command(TARGET psynx POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:psynx>/shaders
    COMMENT "Copying shaders to build directory..."
)
--------
cd build
./psynx

mkdir -p build
cd build
cmake ..
make
./psynx


___________________+ BUILD +_______________________________

mkdir -p build
cd build
cmake ..
make

### RUN ####
./psynx
