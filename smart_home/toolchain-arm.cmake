# ==============================================
# 交叉编译工具链配置文件
# ==============================================
# 用途：告诉 CMake 使用 ARM 交叉编译器而不是本机编译器
# 使用方法：cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-arm.cmake

# ==============================================
# 目标系统配置
# ==============================================

# 目标操作系统：Linux（而不是当前的开发机系统）
set(CMAKE_SYSTEM_NAME Linux)

# 目标处理器架构：ARM（i.MX 6ULL 是 ARM Cortex-A7）
set(CMAKE_SYSTEM_PROCESSOR arm)

# ==============================================
# 交叉编译工具链设置
# ==============================================

# 定义工具链前缀（三元组）
# arm-buildroot-linux-gnueabihf = ARM + Buildroot + Linux + GNU EABI + 硬件浮点
set(TOOLCHAIN_PREFIX arm-buildroot-linux-gnueabihf)

# 指定 C 编译器（必须在 PATH 中或使用绝对路径）
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)

# 指定 C++ 编译器（如果需要 C++）
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

# ==============================================
# 查找策略配置
# ==============================================
# 控制 CMake 在哪里查找程序、库和头文件

# 程序（如 shell 工具）：永远不在目标系统中查找，使用宿主机的
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# 库文件（.so, .a）：只在目标系统的 sysroot 中查找
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

# 头文件（.h）：只在目标系统的 sysroot 中查找
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# 友好提示：显示正在使用的工具链
message(STATUS "[toolchain] Using ${TOOLCHAIN_PREFIX}-gcc for ARM")