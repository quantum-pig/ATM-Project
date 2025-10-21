@echo off
REM ATM GUI系统Windows构建脚本

echo === ATM GUI系统Windows构建脚本 ===

REM 检查MSYS2环境
where gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo 错误: 未找到GCC编译器
    echo 请确保已安装MSYS2并添加到PATH
    echo 下载地址: https://www.msys2.org/
    pause
    exit /b 1
)

REM 检查GTK3
pkg-config --exists gtk+-3.0
if %errorlevel% neq 0 (
    echo 错误: 未找到GTK3开发库
    echo 请在MSYS2中安装: pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-pkg-config
    pause
    exit /b 1
)

REM 检查CMake
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo 错误: 未找到CMake
    echo 请在MSYS2中安装: pacman -S mingw-w64-x86_64-cmake
    pause
    exit /b 1
)

echo 依赖检查完成

REM 清理之前的构建
echo 清理之前的构建文件...
if exist build rmdir /s /q build
if exist CMakeFiles rmdir /s /q CMakeFiles
del /q CMakeCache.txt atm_gui.exe *.o 2>nul

REM 创建构建目录
mkdir build
cd build

REM 配置CMake
echo 配置CMake...
cmake -G "MinGW Makefiles" .. -DCMAKE_BUILD_TYPE=Release

REM 编译
echo 开始编译...
mingw32-make -j4

REM 检查编译结果
if exist atm_gui.exe (
    echo ✅ 编译成功！
    echo 可执行文件: build\atm_gui.exe
    
    REM 复制到根目录
    copy atm_gui.exe ..\
    echo 可执行文件已复制到项目根目录
    
    REM 显示运行说明
    echo.
    echo === 运行说明 ===
    echo 运行GUI版本: atm_gui.exe
    echo 运行控制台版本: atm_system.exe
    echo.
    echo === 测试账户 ===
    echo 卡号: 622202000001-622202000025
    echo 密码: 123456
    
) else (
    echo ❌ 编译失败！
    pause
    exit /b 1
)

pause

