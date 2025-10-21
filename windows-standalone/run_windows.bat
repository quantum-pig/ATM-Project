@echo off
chcp 65001 >nul
title ATM Windows独立版本

echo.
echo ========================================
echo        ATM Windows独立版本
echo ========================================
echo.

REM 检查可执行文件是否存在
if not exist "atm_windows.exe" (
    echo ❌ 未找到可执行文件 atm_windows.exe
    echo.
    echo 请先运行构建脚本:
    echo   build_windows.bat
    echo.
    pause
    exit /b 1
)

REM 检查GTK+3运行时
echo 检查系统依赖...
where gtk3-demo >nul 2>&1
if errorlevel 1 (
    echo ⚠️  警告: 未检测到GTK+3运行时
    echo.
    echo 请确保已安装GTK+3运行时库
    echo 下载地址: https://www.gtk.org/download/
    echo.
    echo 或者将GTK+3的bin目录添加到PATH环境变量
    echo.
    echo 是否继续运行? (Y/N)
    set /p continue=
    if /i not "%continue%"=="Y" exit /b 1
)

echo ✅ 依赖检查完成
echo.
echo 🚀 启动ATM Windows独立版本...
echo.
echo 测试账户信息:
echo   卡号: 622202000001-622202000025
echo   密码: 123456
echo.
echo 按任意键继续...
pause >nul

REM 启动程序
atm_windows.exe

REM 检查程序退出状态
if errorlevel 1 (
    echo.
    echo ❌ 程序运行出错
    echo.
    echo 可能的解决方案:
    echo 1. 检查GTK+3运行时是否正确安装
    echo 2. 检查系统环境变量设置
    echo 3. 重新构建程序
    echo.
    pause
)
