#include <windows.h>
#include "world_engine.h"
#include "window.h"  // Include Window to create an instance
#include <chrono>

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
    try {
        Window window(640, 480);  // Create a Window instance
        WorldEngine engine;
        engine.Initialize(window);
        auto lastTime = std::chrono::high_resolution_clock::now();

        while (true) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
            lastTime = currentTime;

            // Toggle edit mode with F1 (access window directly, not via engine)
            if (glfwGetKey(window.getNativeHandle(), GLFW_KEY_F1) == GLFW_PRESS) {
                engine.ToggleEditMode();
            }

            // Use deltaTime in updates
            engine.Update(deltaTime);

            if (!engine.Run(window)) break; // Exit if window closes, using window reference
        }
        return 0;
    } catch (const std::exception& e) {
        MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
        return 1;
    }
}