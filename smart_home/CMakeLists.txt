# ==============================================
# 项目基础配置
# ==============================================

# 要求最低 CMake 版本为 3.10（Ubuntu 18.04 默认版本）
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和语言（只用 C 语言）
project(smart_home C)

# 设置 C 标准为 C99（兼容性好，功能够用）
set(CMAKE_C_STANDARD 99)

# ==============================================
# 构建类型配置
# ==============================================

# 如果用户没有指定构建类型，默认使用 Release
# Release = 优化编译，适合生产环境
# Debug = 包含调试信息，适合开发调试
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# 打印友好的配置信息
message(STATUS "[smart_home] Project: ${PROJECT_NAME}")
message(STATUS "[smart_home] Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "[smart_home] C compiler: ${CMAKE_C_COMPILER}")

# ==============================================
# LVGL 库配置
# ==============================================

# 添加 LVGL 配置宏，告诉 LVGL 使用简化配置方式
# 这样 LVGL 会查找名为 lv_conf.h 的文件
add_definitions(-DLV_CONF_INCLUDE_SIMPLE)

# 设置 LVGL 配置文件的路径（LVGL 9.4 新要求）
# CMAKE_SOURCE_DIR = 项目根目录
set(LV_BUILD_CONF_PATH ${CMAKE_SOURCE_DIR}/config/lv_conf.h)

# ==============================================
# 源文件收集
# ==============================================

# 递归收集应用程序的所有 .c 文件
# GLOB_RECURSE = 递归查找所有子目录
file(GLOB_RECURSE APP_SRC
  ${CMAKE_SOURCE_DIR}/src/*.c              # 主源码目录
  ${CMAKE_SOURCE_DIR}/src/core/*.c         # 核心业务逻辑
  ${CMAKE_SOURCE_DIR}/src/service/*.c      # 服务层
  ${CMAKE_SOURCE_DIR}/src/ui/*.c           # UI 界面
  ${CMAKE_SOURCE_DIR}/src/ui/components/*.c  # UI 组件
  ${CMAKE_SOURCE_DIR}/src/ui/pages/*.c     # UI 页面
  ${CMAKE_SOURCE_DIR}/src/utils/*.c        # 工具函数
)

# 递归收集 LVGL 库的所有 .c 文件
# 注意：只收集 src 目录，会自动包含所有驱动和核心代码
file(GLOB_RECURSE LVGL_SRC
  ${CMAKE_SOURCE_DIR}/libs/lvgl/src/*.c
)

# ==============================================
# 生成可执行文件
# ==============================================

# 创建可执行文件 smart_home_ui
# 将应用源码和 LVGL 源码一起编译
add_executable(smart_home_ui ${APP_SRC} ${LVGL_SRC})

# ==============================================
# 头文件路径配置
# ==============================================

# 设置头文件搜索路径（PRIVATE = 只对当前目标生效）
target_include_directories(smart_home_ui PRIVATE
  ${CMAKE_SOURCE_DIR}              # 项目根目录（用于 config/lv_conf.h）
  ${CMAKE_SOURCE_DIR}/src          # src 目录（用于 #include "core/xxx.h"）
  ${CMAKE_SOURCE_DIR}/libs         # libs 目录（用于 #include "lvgl/lvgl.h"）
  ${CMAKE_SOURCE_DIR}/libs/lvgl    # lvgl 目录（用于 LVGL 内部头文件）
)

# ==============================================
# 编译和链接选项
# ==============================================

# 编译选项：-Wall = 显示所有警告
target_compile_options(smart_home_ui PRIVATE -Wall)

# 链接数学库 (m) 和线程库 (pthread)
# m = 数学函数（sin, cos 等）
# pthread = POSIX 线程库（LVGL 需要）
target_link_libraries(smart_home_ui m pthread)

# ==============================================
# 构建完成后的提示信息
# ==============================================

# POST_BUILD = 构建成功后执行
add_custom_command(TARGET smart_home_ui POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo ""
  COMMAND ${CMAKE_COMMAND} -E echo "✅ 构建完成！"
  COMMAND ${CMAKE_COMMAND} -E echo "📦 可执行文件: $<TARGET_FILE:smart_home_ui>"
  COMMAND ${CMAKE_COMMAND} -E echo ""
)