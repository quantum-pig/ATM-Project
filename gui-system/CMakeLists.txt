cmake_minimum_required(VERSION 3.16)
project(ATM_GUI_System)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 查找GTK3
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

# 包含目录
include_directories(${GTK3_INCLUDE_DIRS})
include_directories(.)

# 添加编译选项
add_compile_options(${GTK3_CFLAGS})

# 源文件
set(SOURCES
    encryption.c
    file_operations.c
    account_management.c
    transaction.c
    ui.c
    utils.c
    gui_main.c
    gui_login.c
    gui_transaction.c
    gui_common.c
    gui_main_entry.c
)

# 创建可执行文件
add_executable(atm_gui ${SOURCES})

# 链接库
target_link_libraries(atm_gui ${GTK3_LIBRARIES})

# 设置链接目录
target_link_directories(atm_gui PRIVATE ${GTK3_LIBRARY_DIRS})

# 安装规则
install(TARGETS atm_gui DESTINATION bin)
