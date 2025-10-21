@echo off
chcp 65001 >nul
title ATM Windows独立版本构建器

echo.
echo ========================================
echo      ATM Windows独立版本构建器
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
if exist "*.exe" del /q *.exe
if exist "*.o" del /q *.o
echo ✅ 清理完成

echo.
echo 🔨 开始编译Windows独立版本...

REM 获取GTK+3编译参数
echo 📋 获取GTK+3编译参数...
for /f "tokens=*" %%i in ('pkg-config --cflags gtk+-3.0') do set GTK_CFLAGS=%%i
for /f "tokens=*" %%i in ('pkg-config --libs gtk+-3.0') do set GTK_LIBS=%%i

if errorlevel 1 (
    echo ❌ 无法获取GTK+3参数
    echo.
    echo 请确保GTK+3开发库已正确安装
    echo.
    pause
    exit /b 1
)

echo ✅ GTK+3参数获取成功

echo.
echo 🔨 编译源文件...

REM 编译所有源文件
gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c main.c -o main.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c gui_common.c -o gui_common.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c gui_main.c -o gui_main.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c gui_login.c -o gui_login.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c gui_transaction.c -o gui_transaction.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c account_management.c -o account_management.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c encryption.c -o encryption.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c file_operations.c -o file_operations.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c transaction.c -o transaction.o
if errorlevel 1 goto build_error

gcc -Wall -Wextra -std=c99 -g %GTK_CFLAGS% -c utils.c -o utils.o
if errorlevel 1 goto build_error

echo ✅ 源文件编译完成

echo.
echo 🔗 链接生成可执行文件...

REM 链接生成可执行文件
gcc main.o gui_common.o gui_main.o gui_login.o gui_transaction.o account_management.o encryption.o file_operations.o transaction.o utils.o %GTK_LIBS% -o atm_windows.exe
if errorlevel 1 goto build_error

echo ✅ 链接完成

echo.
echo ========================================
echo           构建完成
echo ========================================
echo.

echo 🎉 Windows独立版本构建成功！
echo.

echo 📁 生成的文件:
if exist "atm_windows.exe" (
    echo ✅ atm_windows.exe (Windows独立版本)
    echo.
    echo 📊 文件信息:
    for %%F in (atm_windows.exe) do echo    大小: %%~zF 字节
    echo    类型: Windows可执行文件
    echo    依赖: GTK+3运行时库
) else (
    echo ❌ atm_windows.exe (未生成)
)

echo.
echo 🚀 运行方式:
echo   双击 atm_windows.exe 直接运行
echo   或使用 run_windows.bat 启动脚本
echo.

echo 📋 测试账户:
echo   卡号: 622202000001-622202000025
echo   密码: 123456
echo.

echo ⚠️  注意事项:
echo   1. 确保已安装GTK+3运行时库
echo   2. 将GTK+3的bin目录添加到PATH环境变量
echo   3. 首次运行可能需要安装Visual C++ Redistributable
echo.

echo 按任意键退出...
pause >nul
exit /b 0

:build_error
echo.
echo ❌ 构建失败！
echo.
echo 可能的解决方案:
echo 1. 检查是否安装了所有必要的依赖
echo 2. 检查GTK+3开发库是否正确安装
echo 3. 检查编译器路径是否正确
echo 4. 确保所有源文件完整
echo.
echo 依赖检查:
echo - MinGW-w64 GCC编译器
echo - GTK+3开发库
echo - pkg-config工具
echo.
pause
exit /b 1
