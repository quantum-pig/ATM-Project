#!/bin/bash

# ATM GUI系统构建脚本
# 支持macOS和Linux

echo "=== ATM GUI系统构建脚本 ==="

# 检查操作系统
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "检测到macOS系统"
    PLATFORM="macos"
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "检测到Linux系统"
    PLATFORM="linux"
else
    echo "不支持的操作系统: $OSTYPE"
    exit 1
fi

# 检查依赖
echo "检查构建依赖..."

# 检查GTK3
if ! pkg-config --exists gtk+-3.0; then
    echo "错误: 未找到GTK3开发库"
    echo "请安装GTK3开发库:"
    if [[ "$PLATFORM" == "macos" ]]; then
        echo "  brew install gtk+3 pkg-config"
    else
        echo "  sudo apt-get install libgtk-3-dev pkg-config"
    fi
    exit 1
fi

# 检查CMake
if ! command -v cmake &> /dev/null; then
    echo "错误: 未找到CMake"
    echo "请安装CMake:"
    if [[ "$PLATFORM" == "macos" ]]; then
        echo "  brew install cmake"
    else
        echo "  sudo apt-get install cmake"
    fi
    exit 1
fi

echo "依赖检查完成"

# 清理之前的构建
echo "清理之前的构建文件..."
rm -rf build CMakeFiles CMakeCache.txt
rm -f atm_gui *.o

# 创建构建目录
mkdir -p build
cd build

# 配置CMake
echo "配置CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# 编译
echo "开始编译..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# 检查编译结果
if [ -f "atm_gui" ]; then
    echo "✅ 编译成功！"
    echo "可执行文件: build/atm_gui"
    
    # 复制到根目录
    cp atm_gui ../
    echo "可执行文件已复制到项目根目录"
    
    # 显示运行说明
    echo ""
    echo "=== 运行说明 ==="
    echo "运行GUI版本: ./atm_gui"
    echo "运行控制台版本: ./atm_system"
    echo ""
    echo "=== 测试账户 ==="
    echo "卡号: 622202000001-622202000025"
    echo "密码: 123456"
    
else
    echo "❌ 编译失败！"
    exit 1
fi

