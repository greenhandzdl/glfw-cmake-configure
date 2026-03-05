/**
 * @file window.cpp
 * @brief Window management utilities implementation
 */

#include "window.h"
#include <iostream>

namespace window {

GLFWwindow* create(const char* title, int width, int height) {
    // Create window
    GLFWwindow* win = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!win) {
        std::cerr << "Error: Failed to create GLFW window" << std::endl;
        return nullptr;
    }

    std::cout << "Window created successfully" << std::endl;
    std::cout << "  Title: " << title << std::endl;
    std::cout << "  Size: " << width << "x" << height << std::endl;

    return win;
}

void destroy(GLFWwindow* window) {
    if (window) {
        glfwDestroyWindow(window);
    }
}

bool shouldClose(GLFWwindow* window) {
    return glfwWindowShouldClose(window);
}

void setShouldClose(GLFWwindow* window, int value) {
    if (value) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else {
        glfwSetWindowShouldClose(window, GLFW_FALSE);
    }
}

void swapBuffers(GLFWwindow* window) {
    glfwSwapBuffers(window);
}

void pollEvents() {
    glfwPollEvents();
}

void getFramebufferSize(GLFWwindow* window, int* width, int* height) {
    glfwGetFramebufferSize(window, width, height);
}

} // namespace window
