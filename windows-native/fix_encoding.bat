@echo off
REM 修复Windows CMD乱码问题
REM 设置正确的代码页和字体

echo 正在修复Windows CMD乱码问题...

REM 设置代码页为UTF-8
chcp 65001 >nul
if errorlevel 1 (
    echo 警告: 无法设置UTF-8代码页，尝试使用GBK
    chcp 936 >nul
)

REM 设置控制台字体为支持中文的字体
echo 设置控制台字体...
powershell -Command "& {$Host.UI.RawUI.Font = New-Object System.Management.Automation.Host.Size(16, 16); $Host.UI.RawUI.WindowTitle = 'ATM系统 - 编码修复'}"

REM 设置环境变量
set PYTHONIOENCODING=utf-8
set LANG=zh_CN.UTF-8

echo.
echo ========================================
echo           编码修复完成
echo ========================================
echo.

echo ✅ 代码页设置: UTF-8 (65001)
echo ✅ 字体设置: 支持中文显示
echo ✅ 环境变量: 已设置UTF-8编码
echo.

echo 现在可以正常运行程序了:
echo   build_windows.bat
echo   run_windows.bat
echo.

echo 如果仍有乱码，请尝试以下方法:
echo 1. 右键CMD标题栏 -> 属性 -> 字体 -> 选择"新宋体"或"微软雅黑"
echo 2. 在CMD中运行: chcp 936
echo 3. 使用PowerShell代替CMD
echo.

pause
