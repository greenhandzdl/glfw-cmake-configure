# GLFW + GLAD CMake 模板

跨平台的现代 OpenGL CMake 模板，使用 GLFW 创建窗口、GLAD 加载 OpenGL 函数。

## 依赖

GLAD 已内嵌在项目中（`third_party/glad/`），无需额外安装。

**macOS：**
```bash
brew install glfw cmake
```

**Linux (Ubuntu/Debian)：**
```bash
sudo apt-get install libglfw3-dev cmake build-essential
```

**Linux (Fedora/RHEL)：**
```bash
sudo dnf install glfw-devel cmake gcc-c++
```

## 构建 & 运行

```bash
mkdir build && cd build
cmake ..
cmake --build .
./output/GLFW_Template
```

## 操作

- **R** — 开关旋转
- **空格** — 重置旋转
- **ESC** — 退出

## 清理

```bash
cmake --build build --target clean-project
```

删除 `build/`、`output/` 及生成的脚本。

## 平台说明

- **macOS**：Cocoa 框架，OpenGL 4.1 Metal 后端
- **Linux**：X11，OpenGL 3.3+ Core Profile
