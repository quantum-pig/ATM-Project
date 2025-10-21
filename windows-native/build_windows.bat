@echo off
REM 设置代码页为UTF-8
chcp 65001 >nul
title ATM Windows原生版本构建器

echo.
echo ========================================
echo      ATM Windows原生版本构建器
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

echo.
echo ========================================
echo           开始构建过程
echo ========================================
echo.

REM 清理之前的构建
echo 🧹 清理之前的构建文件...
if exist "*.exe" del /q *.exe
if exist "*.o" del /q *.o
echo ✅ 清理完成

echo.
echo 🔨 开始编译Windows原生版本...

REM 编译所有源文件
echo 📝 编译主程序...
gcc -Wall -Wextra -std=c99 -g -c main.c -o main.o
if errorlevel 1 goto build_error

echo 📝 编译主窗口...
gcc -Wall -Wextra -std=c99 -g -c win_main.c -o win_main.o
if errorlevel 1 goto build_error

echo 📝 编译登录窗口...
gcc -Wall -Wextra -std=c99 -g -c win_login.c -o win_login.o
if errorlevel 1 goto build_error

echo 📝 编译交易窗口...
gcc -Wall -Wextra -std=c99 -g -c win_transaction.c -o win_transaction.o
if errorlevel 1 goto build_error

echo 📝 编译存款窗口...
gcc -Wall -Wextra -std=c99 -g -c win_deposit.c -o win_deposit.o
if errorlevel 1 goto build_error

echo 📝 编译核心模块...
gcc -Wall -Wextra -std=c99 -g -c account_management.c -o account_management.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c encryption.c -o encryption.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c file_operations.c -o file_operations.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c transaction.c -o transaction.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g -c utils.c -o utils.o
if errorlevel 1 goto build_error

echo ✅ 源文件编译完成

echo.
echo 🔗 链接生成可执行文件...

REM 链接生成可执行文件
gcc main.o win_main.o win_login.o win_transaction.o win_deposit.o account_management.o encryption.o file_operations.o transaction.o utils.o -o atm_windows_native.exe -lcomctl32 -lgdi32 -luser32 -lkernel32
if errorlevel 1 goto build_error

echo ✅ 链接完成

echo.
echo ========================================
echo           构建完成
echo ========================================
echo.

echo 🎉 Windows原生版本构建成功！
echo.

echo 📁 生成的文件:
if exist "atm_windows_native.exe" (
    echo ✅ atm_windows_native.exe (Windows原生版本)
    echo.
    echo 📊 文件信息:
    for %%F in (atm_windows_native.exe) do echo    大小: %%~zF 字节
    echo    类型: Windows原生可执行文件
    echo    依赖: 仅需Windows系统库
) else (
    echo ❌ atm_windows_native.exe (未生成)
)

echo.
echo 🚀 运行方式:
echo   双击 atm_windows_native.exe 直接运行
echo   或使用 run_windows.bat 启动脚本
echo.

echo 📋 测试账户:
echo   卡号: 622202000001-622202000025
echo   密码: 123456
echo.

echo ✨ 优势特色:
echo   1. 真正的Windows原生应用
echo   2. 无需额外依赖库
echo   3. 使用Windows API界面
echo   4. 完全兼容Windows系统
echo.

echo 按任意键退出...
pause >nul
exit /b 0

:build_error
echo.
echo ❌ 构建失败！
echo.
echo 可能的解决方案:
echo 1. 检查是否安装了MinGW-w64编译器
echo 2. 检查编译器路径是否正确
echo 3. 确保所有源文件完整
echo 4. 检查是否有语法错误
echo.
echo 依赖检查:
echo - MinGW-w64 GCC编译器
echo - Windows SDK (通常已包含)
echo.
pause
exit /b 1
