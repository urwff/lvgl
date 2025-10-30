cmake_minimum_required(VERSION 3.10)

project(smart_home C)
set(CMAKE_C_STANDARD 99)

# 默认使用 Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# 配置提示
message(STATUS "[smart_home] Project: ${PROJECT_NAME}")
message(STATUS "[smart_home] Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "[smart_home] C compiler: ${CMAKE_C_COMPILER}")

# LVGL：使用简化包含 + 指定配置文件
add_definitions(-DLV_CONF_INCLUDE_SIMPLE)
set(LV_BUILD_CONF_PATH ${CMAKE_SOURCE_DIR}/config/lv_conf.h)

# 收集项目源码
file(GLOB_RECURSE APP_SRC
  ${CMAKE_SOURCE_DIR}/src/*.c
  ${CMAKE_SOURCE_DIR}/src/core/*.c
  ${CMAKE_SOURCE_DIR}/src/service/*.c
  ${CMAKE_SOURCE_DIR}/src/ui/*.c
  ${CMAKE_SOURCE_DIR}/src/ui/components/*.c
  ${CMAKE_SOURCE_DIR}/src/ui/pages/*.c
  ${CMAKE_SOURCE_DIR}/src/utils/*.c
)

# 直接收集 LVGL 源码（避免对官方 CMake 最低版本要求）
file(GLOB_RECURSE LVGL_SRC
  ${CMAKE_SOURCE_DIR}/libs/lvgl/src/*.c
)

add_executable(smart_home_ui ${APP_SRC} ${LVGL_SRC})

# 头文件路径
target_include_directories(smart_home_ui PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/libs
  ${CMAKE_SOURCE_DIR}/libs/lvgl
)

# 编译与链接
target_compile_options(smart_home_ui PRIVATE -Wall)
# 如需体积优化：
# target_compile_options(smart_home_ui PRIVATE -Os -ffunction-sections -fdata-sections)
# target_link_options(smart_home_ui PRIVATE -Wl,--gc-sections)

target_link_libraries(smart_home_ui m pthread)

# 构建完成提示（避免使用尖括号占位）
add_custom_command(TARGET smart_home_ui POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo ""
  COMMAND ${CMAKE_COMMAND} -E echo "✅ 构建完成: $<TARGET_FILE:smart_home_ui>"
  COMMAND ${CMAKE_COMMAND} -E echo "💡 部署: scp $<TARGET_FILE:smart_home_ui> root@[BOARD_IP]:/root/"
  COMMAND ${CMAKE_COMMAND} -E echo "▶️  运行: ./smart_home_ui"
)