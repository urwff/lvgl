# ==============================================
# 编译器配置
# ==============================================
# 使用交叉编译工具链（用于 ARM 平台）
CC = arm-buildroot-linux-gnueabihf-gcc

# ==============================================
# 编译选项（CFLAGS）
# ==============================================
# -O2: 优化等级2，平衡编译速度和运行性能
# -Wall: 显示所有警告信息
CFLAGS = -O2 -Wall

# -I.: 包含当前目录（项目根目录），用于找到 lv_conf.h
CFLAGS += -I.

# -I./src: 包含 src 目录，用于找到项目源码的头文件
CFLAGS += -I./src

# -I./libs: 包含 libs 目录，配合 #include "lvgl/lvgl.h" 使用
#           编译器会在 ./libs 下查找 lvgl/lvgl.h
CFLAGS += -I./libs

# -DLV_CONF_INCLUDE_SIMPLE: 定义宏，让 LVGL 使用简化的配置文件包含方式
#                           LVGL 会直接查找 lv_conf.h 而不是 ../../lv_conf.h
CFLAGS += -DLV_CONF_INCLUDE_SIMPLE

# ==============================================
# 链接选项（LDFLAGS）
# ==============================================
# -lm: 链接数学库（LVGL 计算需要）
# -lpthread: 链接线程库（LVGL 定时器需要）
LDFLAGS = -lm -lpthread

# ==============================================
# 源文件列表
# ==============================================
# LVGL 9.4 源文件：递归查找 libs/lvgl/src 下的所有 .c 文件
# LVGL 9.4 已内置 framebuffer 和 evdev 驱动，无需外部 lv_drivers
LVGL_SRC = $(shell find ./libs/lvgl/src -name "*.c")

# 应用源文件：
# - src/main.c: 主程序入口
# - src/app_init.c: 应用初始化
# - src/core/*.c: 核心业务逻辑（设备管理、场景管理等）
APP_SRC = ./src/main.c ./src/app_init.c $(wildcard ./src/core/*.c)

# 合并所有源文件
SRCS = $(APP_SRC) $(LVGL_SRC)

# 目标可执行文件名
TARGET = smart_home

# ==============================================
# 编译规则
# ==============================================
# 默认目标：编译整个项目
all: $(TARGET)
	@echo ""
	@echo "✅ 编译完成！"
	@echo "📦 可执行文件: $(TARGET)"
	@echo ""
	@echo "🚀 部署到开发板:"
	@echo "   scp $(TARGET) root@192.168.x.x:/root/"
	@echo ""
	@echo "▶️  运行:"
	@echo "   ./$(TARGET)"
	@echo ""

# 链接规则：将所有 .o 文件链接成可执行文件
# $^: 所有依赖文件（即所有 .o 文件）
# $@: 目标文件（即 smart_home）
# @echo: 显示提示信息（@ 表示不显示命令本身）
# @$(CC): 执行编译但不显示命令（只显示我们的提示）
$(TARGET): $(SRCS:.c=.o)
	@echo "🔗 正在链接..."
	@$(CC) $^ -o $@ $(LDFLAGS)

# 编译规则：将 .c 文件编译成 .o 文件
# %.o: 任意 .o 文件
# %.c: 对应的 .c 文件
# $<: 第一个依赖文件（即对应的 .c 文件）
# $@: 目标文件（即对应的 .o 文件）
# -c: 只编译不链接
%.o: %.c
	@echo "📝 编译: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# 清理规则：删除编译产物
clean:
	@echo "🧹 清理编译产物..."
	@rm -f $(TARGET) $(SRCS:.c=.o)
	@echo "✅ 清理完成"

# 声明伪目标：这些目标不对应实际文件
# 即使存在名为 all 或 clean 的文件，make 也会执行这些命令
.PHONY: all clean