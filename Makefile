# ATM仿真系统 Makefile

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = atm_system
SOURCES = main.c encryption.c file_operations.c account_management.c transaction.c ui.c utils.c
OBJECTS = $(SOURCES:.c=.o)

# 默认目标
all: $(TARGET)

# 编译可执行文件
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# 编译目标文件
%.o: %.c atm_system.h
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译文件
clean:
	rm -f $(OBJECTS) $(TARGET) *.dat

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 安装依赖（如果需要）
install:
	@echo "无需额外依赖，直接编译即可"

# 帮助信息
help:
	@echo "可用命令："
	@echo "  make        - 编译程序"
	@echo "  make run    - 编译并运行程序"
	@echo "  make clean  - 清理编译文件"
	@echo "  make help   - 显示此帮助信息"

.PHONY: all clean run install help
