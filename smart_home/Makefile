# ===== 编译器配置 =====
CC = arm-buildroot-linux-gnueabihf-gcc
CFLAGS = -O2 -Wall -Wextra
CFLAGS += -I./src -I./libs/lvgl -I./
CFLAGS += -DLV_CONF_INCLUDE_SIMPLE
LDFLAGS = -lm -lpthread

# ===== 源文件 =====
LVGL_DIR = libs/lvgl

# LVGL 核心源文件（排除示例和测试）
LVGL_SRCS = $(shell find $(LVGL_DIR)/src -name "*.c" \
    -not -path "*/demos/*" \
    -not -path "*/examples/*" \
    -not -path "*/tests/*")

# 应用源文件
APP_SRCS = src/main.c \
           src/ui/ui_styles.c \
           src/ui/ui_card.c \
           src/ui/ui_home.c

# 所有源文件
SRCS = $(APP_SRCS) $(LVGL_SRCS)
OBJS = $(SRCS:.c=.o)

TARGET = smart_home_ui

# ===== 构建规则 =====
all: $(TARGET)
	@echo ""
	@echo "========================================"
	@echo "  ✅ 编译完成: $(TARGET)"
	@echo "========================================"

$(TARGET): $(OBJS)
	@echo "[链接] $@"
	@$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	@echo "[编译] $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "清理编译文件..."
	@rm -f $(TARGET) $(OBJS)
	@echo "✓ 清理完成"

.PHONY: all clean