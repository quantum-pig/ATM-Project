# ATM Windows GUI Makefile

# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lgdi32 -luser32 -lcomctl32 -mwindows

# 源文件
SOURCES = win_gui_main_entry.c \
          win_gui_common.c \
          win_gui_main.c \
          win_gui_login.c \
          win_gui_transaction.c \
          account_management.c \
          transaction.c \
          encryption.c \
          file_operations.c \
          utils.c

# 目标文件
OBJECTS = $(SOURCES:.c=.o)

# 可执行文件
TARGET = atm_gui.exe

# 默认目标
all: $(TARGET)

# 编译可执行文件
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# 编译目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理
clean:
	del /Q *.o $(TARGET) 2>nul || true

# 运行
run: $(TARGET)
	./$(TARGET)

# 安装依赖（需要手动安装MinGW）
install-deps:
	@echo 请手动安装MinGW-w64或MSYS2
	@echo 下载地址: https://www.msys2.org/

# 帮助
help:
	@echo 可用目标:
	@echo   all        - 编译程序
	@echo   clean      - 清理编译文件
	@echo   run        - 编译并运行程序
	@echo   install-deps - 显示依赖安装说明
	@echo   help       - 显示此帮助信息

.PHONY: all clean run install-deps help
