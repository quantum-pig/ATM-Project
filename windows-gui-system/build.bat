@echo off
echo ========================================
echo    ATM Windows GUI 系统构建脚本
echo ========================================
echo.

REM 检查GCC是否可用
echo 检查编译环境...
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo [错误] 未找到GCC编译器
    echo 请安装MinGW-w64或MSYS2
    echo 下载地址: https://www.msys2.org/
    pause
    exit /b 1
)

echo [信息] GCC编译器可用
echo.

REM 清理旧的编译文件
echo 清理旧的编译文件...
del /Q *.o 2>nul
del /Q atm_gui.exe 2>nul

REM 编译项目
echo 正在编译项目...
gcc -Wall -Wextra -std=c99 -O2 -c *.c
if %errorlevel% neq 0 (
    echo [错误] 编译失败！
    pause
    exit /b 1
)

echo 正在链接程序...
gcc -o atm_gui.exe *.o -lgdi32 -luser32 -lcomctl32 -mwindows
if %errorlevel% neq 0 (
    echo [错误] 链接失败！
    pause
    exit /b 1
)

echo.
echo [成功] 编译完成！
echo.
echo 程序信息：
echo - 可执行文件: atm_gui.exe
echo - 文件大小: 
dir atm_gui.exe | findstr atm_gui.exe
echo.
echo 测试账户信息：
echo - 卡号: 622202000001-622202000025
echo - 密码: 123456
echo.
echo 功能特色：
echo - 原生Windows界面
echo - 零外部依赖
echo - 完整ATM功能
echo - 轻量级部署
echo.
echo 是否立即运行程序？(y/n)
set /p choice=
if /i "%choice%"=="y" (
    echo 启动程序...
    atm_gui.exe
)

pause
