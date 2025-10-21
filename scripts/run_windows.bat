@echo off
chcp 65001 >nul
title ATM仿真系统 - Windows版本

echo.
echo ========================================
echo           ATM仿真系统启动器
echo ========================================
echo.

:menu
echo 请选择运行版本:
echo.
echo [1] GUI版本 (推荐) - 现代化图形界面
echo [2] 控制台版本 - 传统命令行界面
echo [3] 查看系统信息
echo [4] 退出
echo.
set /p choice=请输入选择 (1-4): 

if "%choice%"=="1" goto gui_version
if "%choice%"=="2" goto console_version
if "%choice%"=="3" goto system_info
if "%choice%"=="4" goto exit
echo 无效选择，请重新输入！
echo.
goto menu

:gui_version
echo.
echo ========================================
echo           启动GUI版本
echo ========================================
echo.

REM 检查GUI可执行文件是否存在
if not exist "atm_gui.exe" (
    echo ❌ 未找到GUI可执行文件 atm_gui.exe
    echo.
    echo 请先运行构建脚本:
    echo    build.bat
    echo.
    pause
    goto menu
)

REM 检查GTK+3依赖
echo 检查系统依赖...
where gtk3-demo >nul 2>&1
if errorlevel 1 (
    echo ⚠️  警告: 未检测到GTK+3运行时
    echo.
    echo 请确保已安装GTK+3运行时库
    echo 下载地址: https://www.gtk.org/download/
    echo.
    echo 或者使用控制台版本
    echo.
    pause
    goto menu
)

echo ✅ 依赖检查完成
echo.
echo 🚀 启动ATM GUI系统...
echo.
echo 测试账户信息:
echo   卡号: 622202000001-622202000025
echo   密码: 123456
echo.
pause

start "" "atm_gui.exe"
goto menu

:console_version
echo.
echo ========================================
echo           启动控制台版本
echo ========================================
echo.

REM 检查控制台可执行文件是否存在
if not exist "atm_system.exe" (
    echo ❌ 未找到控制台可执行文件 atm_system.exe
    echo.
    echo 请先运行构建脚本:
    echo    make.bat 或 gcc编译
    echo.
    pause
    goto menu
)

echo 🚀 启动ATM控制台系统...
echo.
echo 测试账户信息:
echo   卡号: 622202000001-622202000025
echo   密码: 123456
echo.
pause

atm_system.exe
goto menu

:system_info
echo.
echo ========================================
echo           系统信息
echo ========================================
echo.
echo 操作系统: %OS%
echo 处理器架构: %PROCESSOR_ARCHITECTURE%
echo 用户: %USERNAME%
echo 当前目录: %CD%
echo.
echo 项目文件:
if exist "atm_gui.exe" (
    echo ✅ atm_gui.exe (GUI版本)
) else (
    echo ❌ atm_gui.exe (未找到)
)

if exist "atm_system.exe" (
    echo ✅ atm_system.exe (控制台版本)
) else (
    echo ❌ atm_system.exe (未找到)
)

if exist "CMakeLists.txt" (
    echo ✅ CMakeLists.txt (构建配置)
) else (
    echo ❌ CMakeLists.txt (未找到)
)

if exist "build.bat" (
    echo ✅ build.bat (构建脚本)
) else (
    echo ❌ build.bat (未找到)
)

echo.
echo 依赖检查:
where gcc >nul 2>&1
if errorlevel 1 (
    echo ❌ GCC编译器 (未安装)
) else (
    echo ✅ GCC编译器
)

where cmake >nul 2>&1
if errorlevel 1 (
    echo ❌ CMake (未安装)
) else (
    echo ✅ CMake
)

where pkg-config >nul 2>&1
if errorlevel 1 (
    echo ❌ pkg-config (未安装)
) else (
    echo ✅ pkg-config
)

echo.
pause
goto menu

:exit
echo.
echo 感谢使用ATM仿真系统！
echo.
pause
exit

:error
echo.
echo ❌ 发生错误，请检查系统配置
echo.
pause
goto menu
