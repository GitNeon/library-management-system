# CMake 编译指南

本项目使用 CMake 作为构建系统，以下介绍两种编译方式。

---

## 方式一：使用 VS Code CMake 插件（推荐）

### 前提条件

- 安装 VS Code
- 安装 **CMake** 插件（Microsoft 出品）
- 安装 Visual Studio，并选择 C++ 桌面开发工作负载

### 操作步骤

1. 在 VS Code 中打开项目文件夹
2. CMake 插件会自动检测 `CMakeLists.txt`，左侧插件会显示工具包
3. 如果未自动配置，按 `Ctrl+Shift+P`，输入 **CMake: Configure**
4. 编译时按 `Ctrl+Shift+P`，输入 **CMake: Build**，或直接按 `F7`

### 常用命令

| 命令 | 说明 |
|------|------|
| CMake: Configure | 配置项目，生成编译规则 |
| CMake: Build | 编译项目 |
| CMake: Delete Cache and Reconfigure | 清理缓存并重新配置 |

### 优点

- 自动设置编译器环境变量
- 无需手动敲命令
- 可视化操作，适合入门

---

## 方式二：手动编译

### 前提条件

- 安装 CMake（>= 3.10）
- 安装 Visual Studio（含 C++ 开发工具）
- **打开 x64 Native Tools Command Prompt**（或加载 MSVC 环境）

### 操作步骤

1. 打开 **x64 Native Tools Command Prompt for VS**（开始菜单 → Visual Studio 文件夹）
2. 进入项目目录并创建 build 目录：

```bash
cd /d F:\library-management-system
mkdir build
cd build
```

3. 配置项目（生成编译规则）：

```bash
cmake ..
```

4. 编译项目：

```bash
cmake --build .
```

### 编译产物

可执行文件 `main.exe`（Windows）或 `main`（Linux）会生成在 `build/` 目录。

### 如果使用 MinGW/GCC

```bash
# 删除旧配置
rmdir /s /q build

# 生成 MinGW Makefiles
cmake .. -G "MinGW Makefiles"

# 编译
mingw32-make
```

---

## 两种方式的区别

| 对比项 | VS Code 插件 | 手动编译 |
|--------|-------------|----------|
| 环境配置 | 自动完成 | 需手动加载 MSVC 环境 |
| 操作难度 | 简单 | 需要了解构建流程 |
| 灵活性 | 一般 | 高 |
| 适用场景 | 日常开发 | 特殊配置/自动化脚本 |

---

## 常见问题

### Q: `fatal error C1083: 无法打开包括文件: "iostream"`

**原因**：普通终端未加载 MSVC 环境变量。

**解决**：使用 **x64 Native Tools Command Prompt**，或通过 VS Code 插件编译。

### Q: `Error: not a CMake build directory`

**原因**：`build` 目录缺少 `CMakeCache.txt`。

**解决**：先运行 `cmake ..` 配置项目，再运行 `cmake --build .` 编译。

### Q: 编译报错但代码无语法错误

**解决**：删除 `build` 目录，清理缓存后重新配置编译。

```bash
rmdir /s /q build
mkdir build
cd build
cmake ..
cmake --build .
```

---

## 完整流程图

```
编写代码 → CMakeLists.txt → 配置 → 编译 → 可执行文件
                              ↑
                    cmake .. (生成规则)
                    
编译命令:
cmake --build .  (或 cmake --build build)
```
