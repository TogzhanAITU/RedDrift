#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Automatically adjust OpenGL viewport if the window changes size
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Process keyboard input (Press ESC to close)
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // 1. Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW\n";
        return -1;
    }

    // Configure OpenGL version (3.3 Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Get the primary monitor's resolution
    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    if (!mode) {
        std::cout << "Failed to get video mode\n";
        glfwTerminate();
        return -1;
    }

    // 3. Create a fullscreen window matching the screen's width, height, and refresh rate
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "RedDrift", primaryMonitor, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 4. Load GLAD (Note: gladLoadGLLoader is safer than gladLoadGL for context management)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    glViewport(0, 0, mode->width, mode->height);

    // 5. Main Render Loop
    while (!glfwWindowShouldClose(window)) {
        // Handle input (ESC to exit)
        processInput(window);

        // Clear screen with a background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}