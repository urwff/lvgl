cmake_minimum_required(VERSION 3.20)

# 项目名称与语言
project(smart_home C)
set(CMAKE_C_STANDARD 99)

# 构建类型：默认使用 Release，便于板端部署（可用 -DCMAKE_BUILD_TYPE=Debug 切换）
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# 友好编译信息（配置阶段）
message(STATUS "[smart_home] Project: ${PROJECT_NAME}")
message(STATUS "[smart_home] Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "[smart_home] C compiler: ${CMAKE_C_COMPILER}")

# LVGL 配置：让 LVGL 以简化方式找到 config/lv_conf.h
# 需要你的 config/lv_conf.h 第一行为 #if 1，并与 LV_CONF_INCLUDE_SIMPLE 配合
set(LV_BUILD_CONF_PATH ${CMAKE_SOURCE_DIR}/config/lv_conf.h)
add_definitions(-DLV_CONF_INCLUDE_SIMPLE)

# 关闭 LVGL 示例/演示，保持与当前 Makefile 的最小依赖一致
set(CONFIG_LV_BUILD_DEMOS OFF CACHE BOOL "Build LVGL demos" FORCE)
set(CONFIG_LV_BUILD_EXAMPLES OFF CACHE BOOL "Build LVGL examples" FORCE)

# 引入 LVGL 源码（假设为官方仓库结构）
add_subdirectory(libs/lvgl)

# 收集应用源文件（与现有项目布局对齐）
file(GLOB_RECURSE APP_SRC
  ${CMAKE_SOURCE_DIR}/src/*.c
  ${CMAKE_SOURCE_DIR}/src/core/*.c
  ${CMAKE_SOURCE_DIR}/src/service/*.c
  ${CMAKE_SOURCE_DIR}/src/ui/*.c
  ${CMAKE_SOURCE_DIR}/src/ui/components/*.c
  ${CMAKE_SOURCE_DIR}/src/ui/pages/*.c
  ${CMAKE_SOURCE_DIR}/src/utils/*.c
)

# 目标可执行文件
add_executable(smart_home_ui ${APP_SRC})

# 头文件搜索路径（与 Make 等效）
target_include_directories(smart_home_ui PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/libs
  ${CMAKE_SOURCE_DIR}/libs/lvgl
)

# 编译与链接选项（与 Make 对齐，并给出可选优化）
target_compile_options(smart_home_ui PRIVATE -Wall)
# 可选：缩小体积（板端存储紧张时启用）
# target_compile_options(smart_home_ui PRIVATE -Os -ffunction-sections -fdata-sections)
# target_link_options(smart_home_ui PRIVATE -Wl,--gc-sections)

# 链接库：与 Make 的 -lm -lpthread 对齐
target_link_libraries(smart_home_ui PRIVATE lvgl m pthread)

# 关键路径提示（编译阶段）
add_custom_target(_echo_build_info ALL
  COMMAND ${CMAKE_COMMAND} -E echo "\n🧱 正在编译 smart_home_ui（${CMAKE_BUILD_TYPE}）..."
  COMMAND ${CMAKE_COMMAND} -E echo "📂 源码文件数: $<LENGTH:${APP_SRC}>"
  VERBATIM
)
add_dependencies(_echo_build_info smart_home_ui)

# 构建完成提示
add_custom_command(TARGET smart_home_ui POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo "\n✅ 构建完成: $<TARGET_FILE:smart_home_ui>"
  COMMAND ${CMAKE_COMMAND} -E echo "💡 部署到开发板: scp $<TARGET_FILE:smart_home_ui> root@<board_ip>:/root/"
  COMMAND ${CMAKE_COMMAND} -E echo "▶️  板上运行: ./smart_home_ui"
  VERBATIM
)