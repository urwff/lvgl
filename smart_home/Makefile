CC = arm-buildroot-linux-gnueabihf-gcc

# 编译选项
CFLAGS = -O2 -Wall -Wextra
CFLAGS += -I./src
CFLAGS += -I./libs         # 指向 libs 目录
CFLAGS += -I./libs/lvgl
CFLAGS += -I./libs/lv_drivers
CFLAGS += -DLV_CONF_INCLUDE_SIMPLE
CFLAGS += -DLV_DRV_CONF_INCLUDE_SIMPLE

# 链接选项
LDFLAGS = -lm -lpthread

# LVGL 源文件
LVGL_DIR = ./libs/lvgl
LVGL_SRC = $(shell find $(LVGL_DIR)/src -name "*.c")

# LVGL 驱动源文件
LVGL_DRV_DIR = ./libs/lv_drivers
LVGL_DRV_SRC = $(LVGL_DRV_DIR)/display/fbdev.c \
               $(LVGL_DRV_DIR)/indev/evdev.c

# 应用源文件
APP_SRC = src/main.c

# 所有源文件
SRCS = $(APP_SRC) $(LVGL_SRC) $(LVGL_DRV_SRC)

# 目标文件
OBJS = $(SRCS:.c=.o)

# 可执行文件
TARGET = smart_home

# 默认目标
all: $(TARGET)
	@echo "\n✅ 编译完成！"
	@echo "📦 可执行文件: $(TARGET)"
	@echo "\n🚀 部署到开发板:"
	@echo "   scp $(TARGET) root@192.168.x.x:/root/"
	@echo "\n▶️  运行:"
	@echo "   ./$(TARGET)"

# 编译目标
$(TARGET): $(OBJS)
	@echo "🔗 链接中..."
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# 编译 C 文件
%.o: %.c
	@echo "📝 编译: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# 清理
clean:
	@echo "🧹 清理编译产物..."
	@rm -f $(OBJS) $(TARGET)
	@echo "✓ 清理完成"

# 帮助信息
help:
	@echo "可用命令:"
	@echo "  make          - 编译项目"
	@echo "  make clean    - 清理编译产物"
	@echo "  make help     - 显示帮助信息"

.PHONY: all clean help