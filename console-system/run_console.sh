#!/bin/bash

echo "========================================"
echo "        ATM控制台系统启动器"
echo "========================================"
echo

# 检查可执行文件是否存在
if [ ! -f "atm_system" ]; then
    echo "❌ 未找到可执行文件 atm_system"
    echo
    echo "请先编译项目:"
    echo "  make clean && make"
    echo
    exit 1
fi

echo "🚀 启动ATM控制台系统..."
echo
echo "测试账户信息:"
echo "  卡号: 622202000001-622202000025"
echo "  密码: 123456"
echo
echo "按任意键继续..."
read -n 1

./atm_system
