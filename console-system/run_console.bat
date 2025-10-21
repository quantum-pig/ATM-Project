@echo off
chcp 65001 >nul
title ATM控制台系统

echo ========================================
echo        ATM控制台系统启动器
echo ========================================
echo.

REM 检查可执行文件是否存在
if not exist "atm_system.exe" (
    echo ❌ 未找到可执行文件 atm_system.exe
    echo.
    echo 请先编译项目:
    echo   make clean ^&^& make
    echo   或使用 gcc 手动编译
    echo.
    pause
    exit /b 1
)

echo 🚀 启动ATM控制台系统...
echo.
echo 测试账户信息:
echo   卡号: 622202000001-622202000025
echo   密码: 123456
echo.
echo 按任意键继续...
pause >nul

atm_system.exe
