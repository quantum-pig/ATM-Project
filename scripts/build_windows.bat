@echo off
chcp 65001 >nul
title ATM系统构建脚本 - Windows版本

echo.
echo ========================================
echo         ATM系统构建脚本
echo ========================================
echo.

REM 检查必要的工具
echo 检查构建环境...

where gcc >nul 2>&1
if errorlevel 1 (
    echo ❌ 未找到GCC编译器
    echo.
    echo 请安装MinGW-w64或MSYS2:
    echo   https://www.msys2.org/
    echo   https://www.mingw-w64.org/
    echo.
    pause
    exit /b 1
)
echo ✅ GCC编译器已找到

where cmake >nul 2>&1
if errorlevel 1 (
    echo ❌ 未找到CMake
    echo.
    echo 请安装CMake:
    echo   https://cmake.org/download/
    echo.
    pause
    exit /b 1
)
echo ✅ CMake已找到

where pkg-config >nul 2>&1
if errorlevel 1 (
    echo ❌ 未找到pkg-config
    echo.
    echo 请安装pkg-config (通常包含在GTK+3开发包中)
    echo.
    pause
    exit /b 1
)
echo ✅ pkg-config已找到

echo.
echo ========================================
echo           开始构建过程
echo ========================================
echo.

REM 清理之前的构建
echo 🧹 清理之前的构建文件...
if exist "build" rmdir /s /q build
if exist "*.exe" del /q *.exe
if exist "*.o" del /q *.o
echo ✅ 清理完成

echo.
echo 🔨 开始编译...

REM 选择构建方式
echo 请选择构建方式:
echo [1] 使用CMake构建GUI版本 (推荐)
echo [2] 使用Makefile构建控制台版本
echo [3] 同时构建两个版本
echo.
set /p build_choice=请输入选择 (1-3): 

if "%build_choice%"=="1" goto cmake_build
if "%build_choice%"=="2" goto makefile_build
if "%build_choice%"=="3" goto build_both
echo 无效选择，使用默认CMake构建
goto cmake_build

:cmake_build
echo.
echo ========================================
echo           使用CMake构建GUI版本
echo ========================================
echo.

echo 📋 配置CMake...
mkdir build 2>nul
cd build
cmake .. -G "MinGW Makefiles"
if errorlevel 1 (
    echo ❌ CMake配置失败
    cd ..
    pause
    exit /b 1
)

echo.
echo 🔨 编译项目...
cmake --build .
if errorlevel 1 (
    echo ❌ 编译失败
    cd ..
    pause
    exit /b 1
)

echo.
echo 📦 复制可执行文件...
copy atm_gui.exe ..\ 2>nul
cd ..

if exist "atm_gui.exe" (
    echo ✅ GUI版本构建成功: atm_gui.exe
) else (
    echo ❌ GUI版本构建失败
    pause
    exit /b 1
)

goto build_complete

:makefile_build
echo.
echo ========================================
echo           使用Makefile构建控制台版本
echo ========================================
echo.

echo 🔨 编译控制台版本...
gcc -Wall -Wextra -std=c99 -g -c main.c -o main.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c encryption.c -o encryption.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c file_operations.c -o file_operations.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c account_management.c -o account_management.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c transaction.c -o transaction.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c ui.c -o ui.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c utils.c -o utils.o
if errorlevel 1 goto build_error

gcc main.o encryption.o file_operations.o account_management.o transaction.o ui.o utils.o -o atm_system.exe
if errorlevel 1 goto build_error

echo ✅ 控制台版本构建成功: atm_system.exe
goto build_complete

:build_both
echo.
echo ========================================
echo           构建两个版本
echo ========================================
echo.

echo 🔨 构建控制台版本...
call :makefile_build
if errorlevel 1 goto build_error

echo.
echo 🔨 构建GUI版本...
call :cmake_build
if errorlevel 1 goto build_error

goto build_complete

:build_error
echo.
echo ❌ 构建失败！
echo.
echo 可能的解决方案:
echo 1. 检查是否安装了所有必要的依赖
echo 2. 检查GTK+3开发库是否正确安装
echo 3. 检查编译器路径是否正确
echo.
pause
exit /b 1

:build_complete
echo.
echo ========================================
echo           构建完成
echo ========================================
echo.

echo 🎉 构建成功完成！
echo.

echo 📁 生成的文件:
if exist "atm_gui.exe" (
    echo ✅ atm_gui.exe (GUI版本)
) else (
    echo ❌ atm_gui.exe (未生成)
)

if exist "atm_system.exe" (
    echo ✅ atm_system.exe (控制台版本)
) else (
    echo ❌ atm_system.exe (未生成)
)

echo.
echo 🚀 运行方式:
echo   双击 run_windows.bat 启动系统
echo   或直接运行对应的 .exe 文件
echo.

echo 📋 测试账户:
echo   卡号: 622202000001-622202000025
echo   密码: 123456
echo.

echo 按任意键退出...
pause >nul
exit /b 0
