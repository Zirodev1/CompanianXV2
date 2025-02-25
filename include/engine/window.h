#ifndef WINDOW_H
#define WINDOW_H

#include "../glad/glad.h"   // Include GLAD after GLFW to load OpenGL functions
#include <GLFW/glfw3.h>  // Keep GLFW for window management, but let GLAD handle OpenGL

class Window {
public:
    Window(int width = 640, int height = 480);
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    ~Window();

    bool ProcessMessages();
    GLFWwindow* getNativeHandle() const;  // Ensure correct return type

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
};

#endif