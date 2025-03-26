cmake_minimum_required(VERSION 3.10)
project(CompanionEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define platform
if(WIN32)
    add_definitions(-DCE_PLATFORM_WINDOWS)
    add_definitions(-DCX_PLATFORM_WINDOWS)
endif()

# Include directories for MinGW-w64
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/CompanionX
    ${CMAKE_CURRENT_SOURCE_DIR}/CompanionX/src
    include/glad 
    include/imgui 
    include/glm
)

# Find GLFW in MinGW-w64
find_library(GLFW_LIBRARY NAMES glfw3 PATHS "C:/msys64/mingw64/lib")
if(NOT GLFW_LIBRARY)
    message(FATAL_ERROR "GLFW library not found in C:/msys64/mingw64/lib. Install it via MSYS2 (pacman -S mingw-w64-x86_64-glfw) or specify the path.")
endif()

# Ensure GLFW headers are found in MinGW-w64 include path
include_directories("C:/msys64/mingw64/include")

# Find Assimp in MinGW-w64
find_library(ASSIMP_LIBRARY NAMES assimp PATHS "C:/msys64/mingw64/lib")
if(NOT ASSIMP_LIBRARY)
    message(WARNING "Assimp library not found in C:/msys64/mingw64/lib. Install it via MSYS2 (pacman -S mingw-w64-x86_64-assimp) or specify the path for 3D model support.")
endif()

# Ensure Assimp headers are found in MinGW-w64 include path
include_directories("C:/msys64/mingw64/include/assimp")

# CompanionEngine Library
add_library(CompanionEngine STATIC
    CompanionX/src/CompanionX/Application.cpp
)

# Add include directories for the engine
target_include_directories(CompanionEngine 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/CompanionX
        ${CMAKE_CURRENT_SOURCE_DIR}/CompanionX/src
)

# Link libraries for CompanionEngine
target_link_libraries(CompanionEngine PRIVATE 
    ${GLFW_LIBRARY}
    opengl32
    ${ASSIMP_LIBRARY}
)

# Sandbox Application
add_executable(Sandbox
    Sandbox/src/SandboxApp.cpp
)

# Link Sandbox with CompanionEngine
target_link_libraries(Sandbox CompanionEngine)

# Add include directories for the Sandbox
target_include_directories(Sandbox
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/CompanionX
        ${CMAKE_CURRENT_SOURCE_DIR}/CompanionX/src
)

if(WIN32)
    # Only add -mwindows if we want to hide the console window
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
endif()

# Optional: Add compile options for MinGW
if(MINGW)
    target_compile_options(CompanionEngine PRIVATE -Wall -Wextra)
    target_compile_options(Sandbox PRIVATE -Wall -Wextra)
endif()

# Debugging: Print found paths
message(STATUS "GLFW_LIBRARY: ${GLFW_LIBRARY}")
message(STATUS "ASSIMP_LIBRARY: ${ASSIMP_LIBRARY}")
message(STATUS "Include directories: ${CMAKE_INCLUDE_PATH}")