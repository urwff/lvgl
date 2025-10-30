cmake_minimum_required(VERSION 3.20)
project(smart_home C)
set(CMAKE_C_STANDARD 99)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
set(LV_BUILD_CONF_PATH ${CMAKE_SOURCE_DIR}/config/lv_conf.h)
set(CONFIG_LV_BUILD_DEMOS OFF)
set(CONFIG_LV_BUILD_EXAMPLES OFF)
add_subdirectory(libs/lvgl)
file(GLOB_RECURSE APP_SRC
  ${CMAKE_SOURCE_DIR}/src/*.c
  ${CMAKE_SOURCE_DIR}/src/core/*.c
  ${CMAKE_SOURCE_DIR}/src/service/*.c
  ${CMAKE_SOURCE_DIR}/src/ui/*.c
  ${CMAKE_SOURCE_DIR}/src/ui/components/*.c
  ${CMAKE_SOURCE_DIR}/src/ui/pages/*.c
  ${CMAKE_SOURCE_DIR}/src/utils/*.c)
add_executable(smart_home_ui ${APP_SRC})
target_include_directories(smart_home_ui PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/libs
  ${CMAKE_SOURCE_DIR}/libs/lvgl)
target_compile_options(smart_home_ui PRIVATE -Wall)
target_link_libraries(smart_home_ui PRIVATE lvgl m pthread)