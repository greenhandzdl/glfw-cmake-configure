#ifndef GLFW_TEMPLATE_GL_UTILS_H
#define GLFW_TEMPLATE_GL_UTILS_H

/**
 * @file gl_utils.h
 * @brief OpenGL utility functions
 */

#include "common.h"

namespace glutils {

/**
 * @brief Initialize OpenGL state
 */
void initGL();

/**
 * @brief Print OpenGL information
 */
void printGLInfo();

/**
 * @brief Get OpenGL version string
 * @return OpenGL version string
 */
const char* getGLVersion();

/**
 * @brief Get GLSL version string
 * @return GLSL version string
 */
const char* getGLSLVersion();

/**
 * @brief Get renderer string
 * @return Renderer string
 */
const char* getRenderer();

/**
 * @brief Get vendor string
 * @return Vendor string
 */
const char* getVendor();

} // namespace glutils

#endif // GLFW_TEMPLATE_GL_UTILS_H
