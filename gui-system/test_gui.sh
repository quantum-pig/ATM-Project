#!/bin/bash

# GUI系统测试脚本

echo "=== ATM GUI系统测试脚本 ==="

# 检查依赖
echo "检查GTK3依赖..."
if ! pkg-config --exists gtk+-3.0; then
    echo "❌ 未找到GTK3，请先安装依赖："
    echo "   macOS: brew install gtk+3 pkg-config"
    echo "   Linux: sudo apt-get install libgtk-3-dev pkg-config"
    exit 1
fi

echo "✅ GTK3依赖检查通过"

# 检查编译环境
echo "检查编译环境..."
if ! command -v gcc &> /dev/null; then
    echo "❌ 未找到GCC编译器"
    exit 1
fi

if ! command -v cmake &> /dev/null; then
    echo "❌ 未找到CMake"
    exit 1
fi

echo "✅ 编译环境检查通过"

# 尝试编译
echo "开始编译GUI系统..."
if ./build.sh; then
    echo "✅ 编译成功！"
    
    # 检查可执行文件
    if [ -f "atm_gui" ]; then
        echo "✅ 可执行文件已生成"
        
        # 显示文件信息
        echo "文件信息："
        ls -la atm_gui
        
        echo ""
        echo "=== 测试说明 ==="
        echo "1. 运行GUI版本: ./atm_gui"
        echo "2. 运行控制台版本: ./atm_system"
        echo ""
        echo "=== 测试账户 ==="
        echo "卡号: 622202000001"
        echo "密码: 123456"
        echo ""
        echo "是否现在运行GUI版本进行测试？(y/n)"
        read -r response
        if [[ "$response" =~ ^[Yy]$ ]]; then
            echo "启动GUI系统..."
            ./atm_gui
        fi
    else
        echo "❌ 可执行文件未生成"
        exit 1
    fi
else
    echo "❌ 编译失败"
    exit 1
fi
