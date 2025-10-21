@echo off
chcp 65001 >nul
title ATM仿真系统

echo.
echo ========================================
echo           ATM仿真系统
echo ========================================
echo.

REM 检查可执行文件
if exist "atm_gui.exe" (
    echo 🚀 启动GUI版本...
    echo.
    echo 测试账户: 622202000001-622202000025
    echo 密码: 123456
    echo.
    pause
    atm_gui.exe
) else if exist "atm_system.exe" (
    echo 🚀 启动控制台版本...
    echo.
    echo 测试账户: 622202000001-622202000025
    echo 密码: 123456
    echo.
    pause
    atm_system.exe
) else (
    echo ❌ 未找到可执行文件
    echo.
    echo 请先运行构建脚本:
    echo   build_windows.bat
    echo.
    pause
)
