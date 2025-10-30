CC = arm-buildroot-linux-gnueabihf-gcc
CFLAGS = -O2 -Wall -I./src -I./libs -I. -DLV_CONF_INCLUDE_SIMPLE
LDFLAGS = -lm -lpthread

# LVGL 9.4源文件（内置驱动）
LVGL_SRC = $(shell find libs/lvgl/src -name "*.c")

# 应用源文件
APP_SRC = src/main.c src/app_init.c $(wildcard src/core/*.c) $(wildcard src/ui/**/*.c)

SRCS = $(APP_SRC) $(LVGL_SRC)
TARGET = smart_home

all: $(TARGET)

$(TARGET): $(SRCS:.c=.o)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(SRCS:.c=.o)