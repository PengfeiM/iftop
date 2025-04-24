CC = gcc
CFLAGS = -Wall -I ./include # 包含头文件目录
LDFLAGS = -lpcap #  -lmylib # 包含库文件目录
BUILD_DIR = ./build
SRC_DIR = ./src

# 使用通配符匹配 main.c 和 src 下所有 c 文件
SRC = main.c $(wildcard src/*.c) $(wildcard lib/*.c)

# .c => .o
# OBJ = $(SRC:.c=$(BUILD_DIR)/%.o) # wrong way
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

EXEC = $(BUILD_DIR)/my_iftop

# 确保 build 目录存在
$(shell mkdir -p $(BUILD_DIR))
DIRS := $(sort $(dir $(OBJ)))
$(shell mkdir -p $(DIRS))


all: $(EXEC)

# 生成目标文件
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# 编译源代码文件
$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# 清理编译文件
clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: clean all
