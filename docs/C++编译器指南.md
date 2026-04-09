# C++ 编译器指南

## 什么是编译器？

**编译器**是将源代码（如 `.cpp` 文件）翻译成机器码（如 `.exe` 文件）的程序。

```
源代码 (.cpp)  →  编译器  →  可执行文件 (.exe)
```

---

## C++ 编译器生态概览

```
┌─────────────────────────────────────────────────────────┐
│                     C++ 编译器                           │
├─────────────────────┬───────────────────────────────────┤
│      GCC 阵营        │              MSVC 阵营            │
│  (开源 / 跨平台)      │           (闭源 / Windows)         │
├─────────────────────┼───────────────────────────────────┤
│  • GCC              │  • MSVC (Microsoft Visual C++)    │
│  • G++              │  • Visual Studio (IDE)            │
│  • MinGW            │                                   │
│  • MinGW-w64        │                                   │
│  • Clang            │                                   │
│  • Cygwin           │                                   │
└─────────────────────┴───────────────────────────────────┘
```

---

## 1. GCC (GNU Compiler Collection)

### 简介

- **全称**：GNU Compiler Collection
- **性质**：开源、免费、跨平台
- **官网**：https://gcc.gnu.org/

### 说明

- 最初是 C 编译器（GNU C Compiler），后来支持 C++、Fortran、Go 等多种语言
- "Collection" 意味着它包含多个编译器：`gcc`（C）、`g++`（C++）、`gfortran` 等

### 常用命令

```bash
gcc source.c       # 编译 C 文件
g++ source.cpp     # 编译 C++ 文件
g++ a.cpp b.cpp -o program  # 编译多个文件
```

---

## 2. G++ (GCC C++ Compiler)

### 简介

- **全称**：GCC C++ Compiler
- **本质**：GCC 中专门用于编译 C++ 的前端

### 与 GCC 的区别

| 命令 | 适用语言 | 默认标准库 |
|------|---------|-----------|
| `gcc` | C | libc |
| `g++` | C++ | libstdc++ |

```bash
gcc main.cpp    # 可以编译 C++，但链接时可能缺库
g++ main.cpp    # 自动链接 C++ 标准库（推荐）
```

---

## 3. MinGW (Minimalist GNU for Windows)

### 简介

- **全称**：Minimalist GNU for Windows
- **性质**：将 GCC 移植到 Windows 的项目
- **官网**：http://www.mingw.org/

### 说明

- 让 Windows 用户能使用 GCC 工具链
- 生成纯 Windows 原生程序，不依赖额外运行时
- 是 Windows 下最流行的 GCC 移植版本

### 安装后获得的工具

```
mingw32-gcc.exe      # C 编译器
mingw32-g++.exe      # C++ 编译器
mingw32-make.exe     # make 工具
```

---

## 4. MinGW-w64

### 简介

- MinGW 的一个分支/升级版
- 支持 64 位 Windows
- **目前最推荐的 Windows GCC 方案**

### 为什么推荐 MinGW-w64？

| 版本 | 64位支持 | 维护状态 |
|------|---------|---------|
| MinGW | ❌ | 停止维护 |
| MinGW-w64 | ✅ | 活跃开发 |

> 注意：现在提到 MinGW，通常指的就是 MinGW-w64。

### 常用发行版

- **MinGW-w64 (llvm-mingw)**：基于 LLVM/Clang
- **MinGW-w64 (gcc-builds)**：传统 GCC 编译
- **MSYS2**：集成 MinGW-w64 + 包管理器，推荐！

---

## 5. Clang

### 简介

- **全称**：C Language Family Frontend for LLVM
- **性质**：开源、跨平台
- **官网**：https://clang.llvm.org/

### 说明

- 由 Apple 主导开发，作为 GCC 的替代品
- 代码质量高、编译速度快、错误提示更友好
- 兼容 GCC 大部分命令行选项

### 常用命令

```bash
clang source.cpp        # 编译 C++
clang++ source.cpp       # 编译 C++
clang source.c           # 编译 C
```

### Clang vs GCC

| 特性 | Clang | GCC |
|------|-------|-----|
| 编译速度 | 快 | 较慢 |
| 错误提示 | 清晰 | 一般 |
| 平台支持 | 全平台 | 全平台 |
| C++ 标准支持 | 好 | 好 |
| 许可 | Apache 2.0 | GPL |

---

## 6. MSVC (Microsoft Visual C++)

### 简介

- **全称**：Microsoft Visual C++ Compiler
- **性质**：微软官方编译器，闭源
- **配套 IDE**：Visual Studio

### 说明

- Windows 平台原生编译器
- 生成的 `.exe` 通常依赖 **Visual C++ Redistributable**
- MSVC 在某些 C++ 标准特性上与 GCC/Clang 有差异

### 常用命令

```bash
cl.exe source.cpp       # 编译 C++（需要 Developer Command Prompt）
```

### MSVC 的工具集

```
cl.exe      # 编译器
link.exe    # 链接器
lib.exe     # 库管理工具
```

---

## 7. Visual Studio

### 简介

- **性质**：完整的 IDE（集成开发环境）
- **包含**：MSVC 编译器 + 编辑器 + 调试器 + 其他工具

### VS 版本与 MSVC 工具集版本对应

| Visual Studio | MSVC 版本 |
|--------------|-----------|
| VS 2022 | MSVC 14.3x |
| VS 2019 | MSVC 14.2x |
| VS 2017 | MSVC 14.1x |

---

## 8. 其他相关工具

### Make / Makefile

- **Make**：自动化构建工具，读取 Makefile 中的规则来编译
- **Makefile**：定义编译规则的文件

```bash
make              # 执行 Makefile 中的规则
mingw32-make     # Windows 下 MinGW 版本的 make
```

### CMake

- **不是编译器**，是"构建系统生成器"
- 作用：根据 `CMakeLists.txt` 生成特定平台的 Makefile 或项目文件
- 支持生成：Makefile、Ninja、Visual Studio 项目、Xcode 项目等

```
CMakeLists.txt  →  CMake  →  Makefile / Ninja / VS Project
                                    ↓
                              make / ninja / devenv
                                    ↓
                              可执行文件
```

### Ninja

- 比 Make 更快的构建工具
- 常与 CMake 配合使用
- Google Chrome、Android 项目都在用

```bash
cmake -G Ninja ..
ninja
```

---

## 快速选择指南

### 按操作系统

| 操作系统 | 推荐编译器 |
|---------|-----------|
| Linux | GCC / Clang |
| macOS | Clang (默认) / GCC |
| Windows | MSVC / MinGW-w64 / Clang |

### 按场景

| 场景 | 推荐 |
|------|------|
| 学习 C++ | 任意都行，VS Code + MinGW-w64 简单易用 |
| Windows 桌面开发 | MSVC（Visual Studio） |
| 跨平台项目 | GCC 或 Clang |
| 追求编译速度 | Clang + Ninja |
| 开源项目 | GCC（最广泛兼容） |

---

## 命令行工具速查表

| 命令 | 编译器 | 平台 | 说明 |
|------|--------|------|------|
| `gcc` | GCC | 跨平台 | 编译 C |
| `g++` | GCC | 跨平台 | 编译 C++ |
| `clang` | Clang | 跨平台 | 编译 C/C++ |
| `cl.exe` | MSVC | Windows | 编译 C/C++ |
| `mingw32-gcc` | MinGW | Windows | 编译 C |
| `mingw32-g++` | MinGW | Windows | 编译 C++ |
| `make` | - | 跨平台 | 执行构建 |
| `cmake` | - | 跨平台 | 生成构建系统 |
| `ninja` | - | 跨平台 | 快速构建 |

---

## 图解编译流程

```
        源代码
          │
          ▼
    ┌──────────┐
    │  预处理器  │  (#include 展开、#define 替换)
    └────┬─────┘
          │
          ▼
    ┌──────────┐
    │  编译器    │  (转换为汇编代码)
    │ gcc/g++   │
    │ clang     │
    │ cl.exe    │
    └────┬─────┘
          │
          ▼
    ┌──────────┐
    │  汇编器    │  (转换为目标文件 .o/.obj)
    └────┬─────┘
          │
          ▼
    ┌──────────┐
    │  链接器    │  (合并目标文件 + 库 → 可执行文件)
    │  ld/link  │
    └──────────┘
          │
          ▼
      可执行文件
```
