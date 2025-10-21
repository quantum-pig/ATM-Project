# ATM仿真系统

## 🏦 项目简介

这是一个完整的ATM银行系统仿真项目，提供控制台版本和图形界面版本，支持跨平台运行。

## 📁 项目结构

```
ATM-Project/
├── console-system/          # 控制台版本
│   ├── *.c/h              # 源代码文件
│   ├── Makefile           # 编译配置
│   ├── run_console.sh     # Linux启动脚本
│   ├── run_console.bat    # Windows启动脚本
│   └── README.md          # 控制台版本说明
├── gui-system/            # GUI版本
│   ├── gui_*.c/h          # GUI源代码
│   ├── CMakeLists.txt     # CMake配置
│   ├── build.sh           # Linux构建脚本
│   ├── build.bat          # Windows构建脚本
│   └── README.md          # GUI版本说明
├── docs/                  # 项目文档
├── scripts/               # 通用脚本
└── README.md              # 项目总览
```

## 🚀 快速开始

### 选择版本

#### 控制台版本 (轻量级)
```bash
cd console-system
make clean && make
./run_console.sh
```

#### GUI版本 (推荐)
```bash
cd gui-system
./build.sh
./atm_gui
```

### Windows用户

#### 控制台版本
```cmd
cd console-system
gcc -Wall -Wextra -std=c99 -g *.c -o atm_system.exe
run_console.bat
```

#### GUI版本
```cmd
cd gui-system
build_windows.bat
run_windows.bat
```

## 🎯 功能特色

### 核心功能
- ✅ **账户管理**: 登录、密码验证、账户锁定
- ✅ **存款功能**: 金额验证、回单打印
- ✅ **取款功能**: 余额检查、回单打印
- ✅ **转账功能**: 账户验证、回单打印
- ✅ **查询功能**: 账户信息、交易历史
- ✅ **密码管理**: 安全修改密码

### 技术特色
- 🔐 **安全机制**: 密码加密、输入验证
- 💾 **数据持久化**: 文件存储、数据备份
- 🌐 **跨平台**: 支持Linux、macOS、Windows
- 🎨 **现代界面**: GTK+3图形界面
- 📱 **用户友好**: 直观的操作体验

## 🧪 测试账户

- **卡号**: 622202000001-622202000025
- **密码**: 123456

## 📋 系统要求

### 控制台版本
- GCC编译器
- 标准C库
- 终端环境

### GUI版本
- GTK+3开发库
- CMake构建系统
- pkg-config工具

## 🔧 安装指南

### Linux/macOS

```bash
# 安装依赖
sudo apt-get install libgtk-3-dev cmake pkg-config  # Ubuntu/Debian
sudo yum install gtk3-devel cmake pkgconfig         # CentOS/RHEL
brew install gtk+3 cmake pkg-config                  # macOS
```

### Windows

参考各版本目录下的详细安装指南。

## 🎮 使用说明

### 控制台版本
1. 启动系统
2. 选择登录
3. 输入账户信息
4. 选择交易功能
5. 完成操作

### GUI版本
1. 启动图形界面
2. 点击登录按钮
3. 输入账户信息
4. 选择功能按钮
5. 确认交易信息
6. 选择回单打印

## 📊 版本对比

| 特性 | 控制台版本 | GUI版本 |
|------|------------|---------|
| 界面 | 命令行 | 图形界面 |
| 依赖 | 最小 | GTK+3 |
| 性能 | 轻量 | 现代 |
| 适用场景 | 服务器 | 桌面 |
| 学习价值 | 高 | 中 |

## 🔍 故障排除

### 常见问题

1. **编译错误**
   - 检查编译器安装
   - 验证依赖库

2. **运行时错误**
   - 检查文件权限
   - 验证环境变量

3. **界面问题**
   - 检查GTK+3安装
   - 验证显示环境

## 📞 技术支持

- 📖 查看各版本目录下的README
- 🐛 提交GitHub Issue
- 📧 联系开发团队

## 📄 许可证

本项目采用MIT许可证，详见LICENSE文件。

## 🤝 贡献指南

欢迎提交Pull Request和Issue！

1. Fork项目
2. 创建功能分支
3. 提交更改
4. 发起Pull Request

---

**感谢使用ATM仿真系统！** 🎉