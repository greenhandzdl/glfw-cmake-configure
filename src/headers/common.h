#ifndef GLFW_TEMPLATE_COMMON_H
#define GLFW_TEMPLATE_COMMON_H

/**
 * @file common.h
 * @brief Common definitions and platform-specific configurations for GLFW Template
 */

// Platform detection macros
#if defined(__APPLE__)
 #define GLFW_PLATFORM_MACOS 1
 #define GLFW_PLATFORM_LINUX 0
 // Suppress OpenGL deprecation warnings on macOS
 #ifndef GL_SILENCE_DEPRECATION
  #define GL_SILENCE_DEPRECATION
 #endif
#elif defined(__linux__)
 #define GLFW_PLATFORM_MACOS 0
 #define GLFW_PLATFORM_LINUX 1
#else
 #define GLFW_PLATFORM_MACOS 0
 #define GLFW_PLATFORM_LINUX 0
#endif

// Common macros
#define APP_NAME "GLFW Template with GLEW"
#define APP_VERSION "1.0.0"

// Window defaults
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "GLFW + GLEW Template Application"

// GLEW must be included before GLFW to avoid gl.h conflicts
// On macOS, keep original behavior
#if GLFW_PLATFORM_MACOS
 #include <GL/glew.h>
 #include <GLFW/glfw3.h>
#else
 // On Linux, GLEW must also come first since glfw3.h includes gl.h internally
 #include <GL/glew.h>
 #include <GLFW/glfw3.h>
#endif

#endif // GLFW_TEMPLATE_COMMON_H
