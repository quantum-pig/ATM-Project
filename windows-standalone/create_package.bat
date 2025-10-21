@echo off
chcp 65001 >nul
title ATM Windows安装包创建器

echo.
echo ========================================
echo      ATM Windows安装包创建器
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

echo 📦 创建Windows安装包...
echo.

REM 创建安装包目录
set PACKAGE_DIR=ATM_Windows_Package
if exist "%PACKAGE_DIR%" rmdir /s /q "%PACKAGE_DIR%"
mkdir "%PACKAGE_DIR%"

echo 📁 复制程序文件...
copy "atm_windows.exe" "%PACKAGE_DIR%\"
copy "run_windows.bat" "%PACKAGE_DIR%\"
copy "build_windows.bat" "%PACKAGE_DIR%\"

echo 📄 创建说明文档...
(
echo ATM Windows独立版本
echo ===================
echo.
echo 运行方式:
echo   双击 atm_windows.exe 直接运行
echo   或双击 run_windows.bat 启动脚本
echo.
echo 测试账户:
echo   卡号: 622202000001-622202000025
echo   密码: 123456
echo.
echo 系统要求:
echo   - Windows 10/11
echo   - GTK+3运行时库
echo   - Visual C++ Redistributable
echo.
echo 安装GTK+3运行时:
echo   1. 下载GTK+3运行时库
echo   2. 解压到 C:\gtk3\
echo   3. 将 C:\gtk3\bin 添加到PATH环境变量
echo.
echo 技术支持:
echo   GitHub: https://github.com/quantum-pig/ATM-Project
echo.
) > "%PACKAGE_DIR%\README.txt"

echo 📄 创建安装脚本...
(
echo @echo off
echo chcp 65001 ^>nul
echo title ATM系统安装器
echo.
echo echo ========================================
echo echo           ATM系统安装器
echo echo ========================================
echo echo.
echo echo 欢迎使用ATM仿真系统！
echo echo.
echo echo 本安装包将帮助您设置ATM系统运行环境。
echo echo.
echo pause
echo.
echo echo 检查系统环境...
echo where gtk3-demo ^>nul 2^>^&1
echo if errorlevel 1 ^(
echo     echo ⚠️  未检测到GTK+3运行时
echo     echo.
echo     echo 请安装GTK+3运行时库:
echo     echo 1. 下载地址: https://www.gtk.org/download/
echo     echo 2. 解压到 C:\gtk3\
echo     echo 3. 将 C:\gtk3\bin 添加到PATH环境变量
echo     echo.
echo     echo 安装完成后重新运行此程序。
echo     echo.
echo     pause
echo     exit /b 1
echo ^)
echo.
echo echo ✅ GTK+3运行时已安装
echo echo.
echo echo 🚀 启动ATM系统...
echo echo.
echo start atm_windows.exe
echo.
) > "%PACKAGE_DIR%\install.bat"

echo 📄 创建卸载脚本...
(
echo @echo off
echo chcp 65001 ^>nul
echo title ATM系统卸载器
echo.
echo echo ========================================
echo echo           ATM系统卸载器
echo echo ========================================
echo echo.
echo echo 确定要卸载ATM系统吗？
echo echo.
echo set /p confirm=输入 Y 确认卸载: 
echo if /i not "%%confirm%%"=="Y" exit /b 0
echo.
echo echo 正在卸载ATM系统...
echo del /q atm_windows.exe
echo del /q run_windows.bat
echo del /q build_windows.bat
echo del /q README.txt
echo del /q install.bat
echo del /q uninstall.bat
echo.
echo echo ✅ ATM系统已卸载
echo echo.
echo pause
echo.
) > "%PACKAGE_DIR%\uninstall.bat"

echo 📄 创建批处理文件...
(
echo @echo off
echo chcp 65001 ^>nul
echo title ATM系统
echo.
echo echo ========================================
echo echo           ATM系统
echo echo ========================================
echo echo.
echo echo 启动ATM系统...
echo echo.
echo start atm_windows.exe
echo.
) > "%PACKAGE_DIR%\ATM系统.bat"

echo.
echo ========================================
echo           安装包创建完成
echo ========================================
echo.

echo 🎉 Windows安装包创建成功！
echo.

echo 📁 安装包内容:
echo   📄 atm_windows.exe - 主程序
echo   📄 run_windows.bat - 运行脚本
echo   📄 build_windows.bat - 构建脚本
echo   📄 README.txt - 说明文档
echo   📄 install.bat - 安装脚本
echo   📄 uninstall.bat - 卸载脚本
echo   📄 ATM系统.bat - 快速启动
echo.

echo 📦 安装包位置: %PACKAGE_DIR%\
echo.

echo 🚀 分发说明:
echo   1. 将整个 %PACKAGE_DIR% 文件夹打包
echo   2. 用户解压后运行 install.bat
echo   3. 或直接双击 ATM系统.bat 启动
echo.

echo 按任意键退出...
pause >nul
exit /b 0
