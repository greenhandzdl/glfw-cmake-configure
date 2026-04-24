/**
 * @file gl_utils.cpp
 * @brief OpenGL utility functions implementation
 */

#include "gl_utils.h"
#include <iostream>

namespace glutils {

void initGL() {
    // Set clear color to dark gray
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void printGLInfo() {
    std::cout << "=====================================" << std::endl;
    std::cout << "  OpenGL Information" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "  Vendor:          " << getVendor() << std::endl;
    std::cout << "  Renderer:        " << getRenderer() << std::endl;
    std::cout << "  OpenGL Version:  " << getGLVersion() << std::endl;
    std::cout << "  GLSL Version:    " << getGLSLVersion() << std::endl;
    std::cout << "=====================================" << std::endl;
}

const char* getGLVersion() {
    return reinterpret_cast<const char*>(glGetString(GL_VERSION));
}

const char* getGLSLVersion() {
    return reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
}

const char* getRenderer() {
    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
}

const char* getVendor() {
    return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
}

} // namespace glutils
