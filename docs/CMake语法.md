# 编写 CMakeLists.txt 必须掌握的核心语法
CMake 是跨平台的构建工具，**CMakeLists.txt** 是它的配置文件，核心是**命令 + 变量 + 作用域**，不需要复杂编程基础，掌握以下**基础必备语法**就能写绝大多数项目的配置。

---

## 一、最基础的 3 个语法（必须会）
### 1. 命令格式（核心语法）
```cmake
命令名(参数1 参数2 ...)
```
- 命令**不区分大小写**（`project` / `PROJECT` 都可以），但**小写是行业标准**
- 参数之间用**空格**分隔，不用逗号
- 字符串带空格时用**双引号**包裹：`"Hello World"`

示例：
```cmake
# 正确
project(MyProject)
add_executable(app main.cpp)

# 错误（不能用逗号）
add_executable(app, main.cpp)
```

### 2. 变量定义与使用
```cmake
# 定义变量
set(变量名 值)

# 使用变量：${变量名}
message("变量值：${MY_VAR}")
```

示例：
```cmake
# 定义源文件变量
set(SRC_FILES main.cpp test.cpp utils.cpp)

# 使用变量
add_executable(app ${SRC_FILES})
```

### 3. 注释
```cmake
# 单行注释（最常用）

#[[
多行注释
可以写很多内容
]]
```

---

## 二、项目必备核心命令（80% 场景都用它）
这是写 CMakeLists.txt **必背**的命令，没有它们项目跑不起来：

### 1. `cmake_minimum_required`
指定最低 CMake 版本，必须写在**第一行**
```cmake
cmake_minimum_required(VERSION 3.10)
```

### 2. `project`
定义项目名称、支持的语言（默认 C/C++）
```cmake
project(MyProject C CXX)  # CXX = C++
```

### 3. `add_executable`
生成**可执行文件**（最常用）
```cmake
add_executable(可执行文件名 源文件1 源文件2 ...)
# 示例
add_executable(demo main.cpp)
```

### 4. `add_library`
生成**静态库/动态库**
```cmake
# 生成静态库 .a / .lib
add_library(utils STATIC utils.cpp)

# 生成动态库 .so / .dll
add_library(utils SHARED utils.cpp)
```

### 5. `target_link_libraries`
给可执行文件**链接库**
```cmake
target_link_libraries(目标 库1 库2 ...)
# 示例：demo 链接 utils 库
target_link_libraries(demo utils)
```

### 6. `include_directories`
添加**头文件搜索路径**（等价于 GCC 的 `-I`）
```cmake
include_directories(./include)
```

### 7. `aux_source_directory`
自动收集目录下的所有源文件（懒人必备）
```cmake
# 收集 src 目录下所有 .c/.cpp 文件，存入 SRC 变量
aux_source_directory(src SRC)
add_executable(demo ${SRC})
```

---

## 三、常用控制语法（条件、循环）
### 1. `if-else` 条件判断
```cmake
if(条件)
    # 执行语句
elseif(条件)
    # 执行语句
else()
    # 执行语句
endif()
```

常用判断：
```cmake
if(EXISTS "main.cpp")      # 文件是否存在
if(WIN32)                  # Windows 系统
if(UNIX)                   # Linux/macOS 系统
if(${VAR} EQUAL 10)        # 数值相等
if(DEFINED VAR)            # 变量是否定义
```

### 2. `foreach` 循环
```cmake
# 遍历列表
foreach(file ${SRC_FILES})
    message("源文件：${file}")
endforeach()
```

---

## 四、路径与输出控制语法
### 1. 常用内置路径变量
```cmake
${PROJECT_SOURCE_DIR}   # 项目根目录
${CMAKE_CURRENT_SOURCE_DIR} # 当前 CMakeLists.txt 所在目录
${CMAKE_BINARY_DIR}     # 构建输出目录
```

### 2. 设置输出路径
```cmake
# 设置可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# 设置库文件输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
```

---

## 五、C/C++ 编译配置语法
### 1. 设置 C++ 标准
```cmake
set(CMAKE_CXX_STANDARD 11)    # C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 强制要求
```

### 2. 添加编译选项
```cmake
# GCC/Clang
add_compile_options(-Wall -Wextra -O2)

# MSVC
if(MSVC)
    add_compile_options(/W4)
endif()
```

---

## 六、完整极简示例（直接套用）
这是一个**能直接运行**的 CMakeLists.txt，包含所有核心语法：
```cmake
# 1. 最低版本
cmake_minimum_required(VERSION 3.10)

# 2. 项目名称
project(MyDemo)

# 3. C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 4. 头文件路径
include_directories(include)

# 5. 自动收集源文件
aux_source_directory(src SRC_FILES)

# 6. 生成可执行文件
add_executable(demo main.cpp ${SRC_FILES})

# 7. 生成库并链接
add_library(utils SHARED src/utils.cpp)
target_link_libraries(demo utils)
```

---

# 总结：必须掌握的核心清单
1. **命令格式**：`命令(参数)` + 变量 `${VAR}`
2. **5 个核心命令**：`project`、`add_executable`、`add_library`、`target_link_libraries`、`include_directories`
3. **条件判断**：`if-else`
4. **路径与编译配置**
掌握这些，你就能写**单文件、多文件、库、跨平台**项目的 CMakeLists.txt。

需要我给你整理一份**可直接复制的通用 CMakeLists.txt 模板**吗？