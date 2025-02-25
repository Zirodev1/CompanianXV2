# CompanionX AI World Engine

## Overview
CompanionX is a lightweight, OpenGL-based engine designed to create and manage a 3D world for an AI character (e.g., a maid character) to live and interact in, inspired by game engines like Unity or Unreal. It provides a persistent 3D rendering environment, physics for character movement, AI for wandering behavior, and a customizable editor interface for design and asset management. The goal is to develop a tool for AI simulation, education, or game development, with plans for monetization through licensing or premium features.

## Current Features
### 1. **3D Rendering**
   - Uses OpenGL with GLFW (window management), GLAD (OpenGL loader), and GLM (math library) for rendering a 3D world.
   - Displays a flat green terrain (10x10 grid) and a red cube (AI character) that wanders randomly using simple physics and AI logic.
   - Supports loading 3D models (e.g., maid character) via Assimp for enhanced visuals.

### 2. **Physics System**
   - Implements basic physics for the AI character, including gravity and ground collision, allowing it to wander across the terrain.
   - Uses `GLM` for vector and matrix math to manage object positions and velocities.

### 3. **AI System**
   - Includes a simple AI system for random wandering behavior, pausing when in edit mode.
   - Integrates with the physics system to update the AI character’s position over time.

### 4. **Editor Interface**
   - Features a Unity-like editor using ImGui, toggleable via F1 (edit mode on/off).
   - When in edit mode:
     - Pauses the AI and physics, showing only the editor UI.
     - Displays an **Object List** with all world objects (terrain, AI character, assets) for selection.
     - Provides an **Inspector** for editing object properties (position, rotation, scale, color).
     - Includes a **Content Management** panel for adding and dragging assets into the world.

### 5. **Build System**
   - Uses CMake with MinGW (via MSYS2) for cross-platform compatibility.
   - Integrates GLFW, GLAD, GLM, ImGui, and optionally Assimp for 3D model support.

## Planned Features
To enhance CompanionX for monetization and usability, we plan to implement:

### 1. **Advanced Physics**
   - Add collision detection and response for objects in the world (e.g., AI character interacting with terrain or assets).
   - Implement dynamic physics for added assets (e.g., movable objects, environmental interactions).

### 2. **Enhanced AI Behaviors**
   - Expand AI capabilities beyond wandering, such as pathfinding, obstacle avoidance, or goal-oriented behavior.
   - Add scripting support (e.g., Lua or custom scripts) for user-defined AI actions.

### 3. **Asset Management Improvements**
   - Support for importing various 3D model formats (FBX, OBJ, etc.) with textures and animations via Assimp or other libraries.
   - Drag-and-drop functionality for adding assets directly from the content panel to the world.
   - Asset preview and categorization for better organization.

### 4. **Lighting and Textures**
   - Add basic lighting (e.g., directional, point lights) to enhance the 3D world’s visuals.
   - Implement texture support for objects, including the terrain and AI character (e.g., maid model textures).

### 5. **User Interaction**
   - Add camera controls (e.g., WASD for movement, mouse for rotation) for navigating the world in both run and edit modes.
   - Enable direct manipulation of objects in edit mode (e.g., drag to move, rotate, or scale).

### 6. **Save/Load Functionality**
   - Implement file I/O to save and load world states, including object positions, properties, and AI behaviors.
   - Support for exporting/importing worlds for sharing or distribution.

### 7. **UI Enhancements**
   - Expand the ImGui editor with advanced features like a hierarchy view, scene management, and performance metrics.
   - Add settings menus for graphics options, physics parameters, and AI configuration.

### 8. **Monetization Features**
   - Offer premium asset packs (e.g., 3D models, AI behaviors) as in-app purchases or add-ons.
   - Provide a licensing model for developers or educators, with optional subscription plans for updates and support.
   - Include a demo mode with limited features and a paid upgrade to unlock full functionality.

## Dependencies
- **GLFW**: For window management and OpenGL context creation (included in `include/glfw/` or linked via MSYS2).
- **GLAD**: For OpenGL function loading (included as `glad.c` in `src/` and `glad.h` in `include/glad/`).
- **GLM**: For vector and matrix math (header-only, included in `include/glm/`).
- **ImGui**: For the editor UI (included in `include/imgui/` and `src/imgui/`).
- **Assimp**: Optional for 3D model loading (linked via MSYS2 or included in `CMakeLists.txt`).
- **MinGW**: Compiler and build system via MSYS2 for Windows development.
- **CMake**: Build configuration tool for cross-platform compatibility.

## Building and Running
### Prerequisites
- Install MinGW-w64 and MSYS2 on Windows.
- Install dependencies via MSYS2:
  ```bash
  pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-glfw mingw-w64-x86_64-assimp

    Ensure GLFW, GLAD, GLM, ImGui, and Assimp are correctly placed in the include/ and src/ directories as described.

Build Instructions

    Navigate to the project root (Z:/dev/ai/CompanionX/).
    Create a build directory:
    bash

mkdir build
cd build

Generate build files with CMake:
bash

cmake ..

Build the project:
bash

mingw32-make

Run the application:
bash

    ./CompanionX

Contributing
This project is open for contributions. If you’d like to add features, improve performance, or fix bugs, please fork the repository, make changes, and submit pull requests. Contact the project maintainer for collaboration details.
Licensing
CompanionX is licensed under the MIT License (see LICENSE file). You are free to use, modify, and distribute this software for commercial purposes, provided you include the MIT license in your distribution.
Contact
For questions, support, or business inquiries, contact [Your Name/Email] or visit [Your Website, if applicable].


---

### Notes on the Documentation
- **Current Features**: Reflects the working OpenGL engine, physics, AI, and editor UI as implemented in our previous steps.
- **Planned Features**: Outlines enhancements to make CompanionX a robust, monetizable tool, focusing on usability, features, and market appeal.
- **Dependencies and Build Instructions**: Provides clear steps for setting up and building the project, ensuring users can get started quickly.
- **Licensing and Contact**: Includes placeholder information for you to customize based on your needs (e.g., your name, email, or website for monetization).

---

### Next Steps
- **Update Your Project**:
  - Ensure `CMakeLists.txt` matches the one above, adjusting paths if necessary.
  - Place the `README.md` in your project root (`Z:/dev/ai/CompanionX/`).
  - Build and test the project to confirm GLFW and GLM are working correctly with MinGW.
- **Monetization**:
  - Use the `README.md` to market CompanionX to potential customers (e.g., developers, educators) or investors.
  - Add premium features (e.g., asset packs, advanced AI) as outlined in the planned features to justify a paid model.
- **Support**:
  - If you encounter build errors or need help refining features, share details (MinGW version, error logs), and I’ll assist immediately.
  - We can prioritize implementing high-value features (e.g., asset loading, save/load) to accelerate monetization.
