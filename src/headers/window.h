#ifndef GLFW_TEMPLATE_WINDOW_H
#define GLFW_TEMPLATE_WINDOW_H

/**
 * @file window.h
 * @brief Window management utilities
 */

#include "common.h"

namespace window {

/**
 * @brief Create a new GLFW window
 * @param title Window title
 * @param width Window width
 * @param height Window height
 * @return GLFW window pointer or nullptr on failure
 */
GLFWwindow* create(const char* title, int width, int height);

/**
 * @brief Destroy a GLFW window
 * @param window Window to destroy
 */
void destroy(GLFWwindow* window);

/**
 * @brief Check if window should close
 * @param window Window to check
 * @return true if window should close
 */
bool shouldClose(GLFWwindow* window);

/**
 * @brief Set window should close flag
 * @param window Window
 * @param value Close flag value
 */
void setShouldClose(GLFWwindow* window, int value);

/**
 * @brief Swap front and back buffers
 * @param window Window
 */
void swapBuffers(GLFWwindow* window);

/**
 * @brief Poll events
 */
void pollEvents();

/**
 * @brief Get framebuffer size
 * @param window Window
 * @param width Output width
 * @param height Output height
 */
void getFramebufferSize(GLFWwindow* window, int* width, int* height);

} // namespace window

#endif // GLFW_TEMPLATE_WINDOW_H
