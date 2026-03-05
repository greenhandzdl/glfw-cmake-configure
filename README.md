# GLFW + GLEW CMake Template

Cross-platform CMake template for modern OpenGL applications using GLFW and GLEW.

## Prerequisites

**macOS:**
```bash
brew install glfw glew cmake
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt-get install libglfw3-dev libglew-dev cmake build-essential
```

**Linux (Fedora/RHEL):**
```bash
sudo dnf install glfw-devel glew-devel cmake gcc-c++
```

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Or use the script:
```bash
./scripts/build.sh
```

## Run

```bash
./output/GLFW_Template
```

## Clean

```bash
cmake --build build --target clean-project
```

Removes `build/`, `output/`, and generated scripts.

## Controls

- **R** - Toggle rotation
- **SPACE** - Reset rotation  
- **ESC** - Exit

## Platform Notes

**macOS:** Uses Cocoa framework, OpenGL 4.1 Metal backend. Full GLEW support.

**Linux:** Uses X11, OpenGL 3.3+ Core Profile.

## CMake Options

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake -DBUILD_EXAMPLES=OFF ..
```

## Why GLFW?

Recommended for:
- Modern OpenGL (3.3+) development
- Advanced window/input handling
- Production applications
- Stable GLEW integration on macOS

## Related

- FreeGLUT template for traditional OpenGL
- GLFW: https://www.glfw.org/
- GLEW: http://glew.sourceforge.net/
