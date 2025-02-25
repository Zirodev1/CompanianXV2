cmake_minimum_required(VERSION 3.10)
project(CompanionXv2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for MinGW-w64
include_directories(include/engine include/glad include/imgui include/glm)

# Find GLFW in MinGW-w64
find_library(GLFW_LIBRARY NAMES glfw3 PATHS "C:/msys64/mingw64/lib")
if(NOT GLFW_LIBRARY)
    message(FATAL_ERROR "GLFW library not found in C:/msys64/mingw64/lib. Install it via MSYS2 (pacman -S mingw-w64-x86_64-glfw) or specify the path.")
endif()

# Ensure GLFW headers are found in MinGW-w64 include path
include_directories("C:/msys64/mingw64/include")

# Find GLAD (source included in project, no library needed)
# Ensure glad.c is in src/

# Find ImGui (source included in project, no library needed)
# Ensure imgui source files are in src/imgui/

# Find GLM (header-only, no library needed)
# Ensure GLM headers are in include/glm/

# Find Assimp in MinGW-w64
find_library(ASSIMP_LIBRARY NAMES assimp PATHS "C:/msys64/mingw64/lib")
if(NOT ASSIMP_LIBRARY)
    message(WARNING "Assimp library not found in C:/msys64/mingw64/lib. Install it via MSYS2 (pacman -S mingw-w64-x86_64-assimp) or specify the path for 3D model support. Continuing without Assimp.")
endif()

# Ensure Assimp headers are found in MinGW-w64 include path
include_directories("C:/msys64/mingw64/include/assimp")

# Source files
add_executable(CompanionXv2
    src/main.cpp
    src/window.cpp
    src/world_engine.cpp
    src/renderer.cpp
    src/physics.cpp
    src/ai.cpp
    src/editor.cpp
    src/asset_manager.cpp
    src/object.cpp
    src/glad.c
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

# Link libraries for MinGW-w64
target_link_libraries(CompanionXv2 PRIVATE ${GLFW_LIBRARY} opengl32 ${ASSIMP_LIBRARY})

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()

# Optional: Add compile options for MinGW
if(MINGW)
    target_compile_options(CompanionXv2 PRIVATE -Wall -Wextra)
endif()

# Debugging: Print found paths
message(STATUS "GLFW_LIBRARY: ${GLFW_LIBRARY}")
message(STATUS "ASSIMP_LIBRARY: ${ASSIMP_LIBRARY}")
message(STATUS "Include directories: ${CMAKE_INCLUDE_PATH}")