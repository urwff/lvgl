# 目标系统与架构
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# 工具链三元组（与 Makefile 一致）
set(TOOLCHAIN_PREFIX arm-buildroot-linux-gnueabihf)
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

# 查找策略：仅从交叉 sysroot 中找库与头
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# 友好提示
message(STATUS "[toolchain] Using ${TOOLCHAIN_PREFIX}-gcc for ARM (i.MX 6ULL)")