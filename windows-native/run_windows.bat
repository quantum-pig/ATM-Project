@echo off
REM 设置代码页为UTF-8
chcp 65001 >nul
title ATM Windows原生版本

echo.
echo ========================================
echo        ATM Windows原生版本
echo ========================================
echo.

REM 检查可执行文件是否存在
if not exist "atm_windows_native.exe" (
    echo ❌ 未找到可执行文件 atm_windows_native.exe
    echo.
    echo 请先运行构建脚本:
    echo   build_windows.bat
    echo.
    pause
    exit /b 1
)

echo ✅ 程序文件检查完成
echo.
echo 🚀 启动ATM Windows原生版本...
echo.
echo 测试账户信息:
echo   卡号: 622202000001-622202000025
echo   密码: 123456
echo.
echo ✨ 特色功能:
echo   - Windows原生界面
echo   - 无需额外依赖
echo   - 完整ATM功能
echo   - 现代化用户体验
echo.
echo 按任意键继续...
pause >nul

REM 启动程序
atm_windows_native.exe

REM 检查程序退出状态
if errorlevel 1 (
    echo.
    echo ❌ 程序运行出错
    echo.
    echo 可能的解决方案:
    echo 1. 检查程序文件是否完整
    echo 2. 重新构建程序
    echo 3. 检查系统兼容性
    echo.
    pause
) else (
    echo.
    echo ✅ 程序正常退出
)
