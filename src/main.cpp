/**
 * @file main.cpp
 * @brief GLFW + GLAD Template Application
 *
 * A modern OpenGL template using GLAD for OpenGL extension loading.
 * Demonstrates:
 * - GLAD initialization
 * - Modern OpenGL (3.3 Core Profile)
 * - Vertex and Fragment shaders
 * - VAO/VBO for geometry
 * - Cross-platform build (macOS/Linux)
 */

#include "common.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

// ============================================================================
// Shader Sources
// ============================================================================
const char* VERTEX_SHADER_SOURCE = R"(
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float uTime;
uniform float uRotation;

void main()
{
    // Rotation matrix
    float c = cos(uRotation);
    float s = sin(uRotation);

    vec3 rotatedPos = aPos;
    rotatedPos.x = aPos.x * c - aPos.z * s;
    rotatedPos.z = aPos.x * s + aPos.z * c;

    gl_Position = vec4(rotatedPos, 1.0);
    ourColor = aColor;
}
)";

const char* FRAGMENT_SHADER_SOURCE = R"(
#version 330 core

in vec3 ourColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
)";

// ============================================================================
// Global Variables
// ============================================================================
static float g_rotation = 0.0f;
static bool g_is_rotating = true;
static float g_time = 0.0f;

// Shader program and VAO
static unsigned int shaderProgram = 0;
static unsigned int VAO = 0;
static unsigned int VBO = 0;

// Auto-close for testing (set to true for automated testing)
static bool g_auto_close = false;
static float g_auto_close_timer = 2.0f; // Close after 2 seconds if auto-close enabled

// ============================================================================
// Shader Compilation
// ============================================================================
unsigned int compileShader(const char* source, GLenum type) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader compilation failed: " << infoLog << std::endl;
        return 0;
    }
    return shader;
}

unsigned int createShaderProgram() {
    unsigned int vertexShader = compileShader(VERTEX_SHADER_SOURCE, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(FRAGMENT_SHADER_SOURCE, GL_FRAGMENT_SHADER);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

// ============================================================================
// Initialize VAO and VBO
// ============================================================================
void initGeometry() {
    // Cube vertices with colors (x, y, z, r, g, b)
    float vertices[] = {
        // Front face (red)
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        // Back face (green)
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        // Top face (blue)
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        // Bottom face (yellow)
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
        // Right face (cyan)
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
        // Left face (magenta)
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {
        0,  1,  2,  2,  3,  0,   // Front
        4,  5,  6,  6,  7,  4,   // Back
        8,  9,  10, 10, 11, 8,   // Top
        12, 13, 14, 14, 15, 12,  // Bottom
        16, 17, 18, 18, 19, 16,  // Right
        20, 21, 22, 22, 23, 20   // Left
    };

    unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

// ============================================================================
// Print Information
// ============================================================================
void printInfo() {
    std::cout << "=====================================" << std::endl;
    std::cout << " GLFW + GLAD Template Application" << std::endl;
    std::cout << " Version: " << APP_VERSION << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << " Controls:" << std::endl;
    std::cout << " R - Toggle rotation" << std::endl;
    std::cout << " SPACE - Reset rotation" << std::endl;
    std::cout << " ESC - Exit" << std::endl;
    std::cout << "=====================================" << std::endl;
}

void printGLInfo() {
    std::cout << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << std::endl;
}

// ============================================================================
// Main Entry Point
// ============================================================================
int main(int argc, char** argv) {
    // Check for auto-close flag for testing
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--auto-close") {
            g_auto_close = true;
            std::cout << "Auto-close mode enabled for testing" << std::endl;
        }
    }

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Error: Failed to initialize GLFW" << std::endl;
        return 1;
    }

    printInfo();

    // Set OpenGL version for modern GL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#if GLFW_PLATFORM_MACOS
    std::cout << "Platform: macOS" << std::endl;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#elif GLFW_PLATFORM_LINUX
    std::cout << "Platform: Linux" << std::endl;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    // Create window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        std::cerr << "Error: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Error: Failed to initialize GLAD" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    std::cout << "GLAD initialized successfully!" << std::endl;

    // Print OpenGL info
    printGLInfo();

    // Create shader program
    shaderProgram = createShaderProgram();
    if (shaderProgram == 0) {
        std::cerr << "Error: Failed to create shader program" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }
    std::cout << "Shader program created successfully!" << std::endl;

    // Initialize geometry
    initGeometry();
    std::cout << "Geometry initialized!" << std::endl;
    std::cout << std::endl;

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Get uniform locations
    GLint timeLoc = glGetUniformLocation(shaderProgram, "uTime");
    GLint rotationLoc = glGetUniformLocation(shaderProgram, "uRotation");

    // Keyboard callback
    glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {
        (void)w;
        (void)scancode;
        (void)mods;

        if (action != GLFW_PRESS) return;

        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(w, GLFW_TRUE);
                break;
            case GLFW_KEY_R:
                g_is_rotating = !g_is_rotating;
                std::cout << "Rotation: " << (g_is_rotating ? "ON" : "OFF") << std::endl;
                break;
            case GLFW_KEY_SPACE:
                g_rotation = 0.0f;
                g_time = 0.0f;
                std::cout << "Rotation reset" << std::endl;
                break;
        }
    });

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Update time
        g_time += 0.016f; // ~60 FPS
        if (g_is_rotating) {
            g_rotation += 0.017f; // ~1 degree per frame
        }

        // Auto-close timer for testing
        if (g_auto_close) {
            g_auto_close_timer -= 0.016f;
            if (g_auto_close_timer <= 0.0f) {
                std::cout << "Auto-close timer expired, exiting..." << std::endl;
                break;
            }
        }

        // Clear buffers
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use shader program
        glUseProgram(shaderProgram);
        glUniform1f(timeLoc, g_time);
        glUniform1f(rotationLoc, g_rotation);

        // Draw
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "Exiting..." << std::endl;

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
