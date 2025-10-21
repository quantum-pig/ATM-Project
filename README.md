# ATM仿真系统 (Mac版本)

这是一个使用C语言开发的ATM仿真系统，专为macOS系统优化。系统提供控制台和图形用户界面两个版本，支持完整的银行功能。

## 🚀 快速开始

### 控制台版本

```bash
cd console-system
make clean && make
./run_console.sh
```

### GUI版本

```bash
cd gui-system
./build.sh
./atm_gui
```

## 📁 项目结构

```
ATM-Project/
├── console-system/          # 控制台版本
│   ├── *.c/h              # C语言源代码和头文件
│   ├── Makefile           # 构建配置
│   ├── atm_system         # 编译后的可执行文件
│   ├── run_console.sh     # Mac运行脚本
│   └── README.md          # 详细说明文档
├── gui-system/            # GUI版本
│   ├── gui_*.c/h          # GUI界面源代码
│   ├── CMakeLists.txt     # CMake构建配置
│   ├── atm_gui            # 编译后的GUI可执行文件
│   ├── build.sh           # Mac构建脚本
│   ├── test_gui.sh        # GUI测试脚本
│   └── README.md          # 详细说明文档
├── accounts.dat            # 账户数据文件
├── statements.dat          # 交易流水文件
└── README.md              # 项目总览 (当前文件)
```

## ✨ 功能特色

### 控制台版本
- ✅ **完整银行功能**: 存款、取款、转账、查询、修改密码
- ✅ **安全机制**: 密码加密存储，账户锁定保护
- ✅ **数据持久化**: 本地文件存储，数据不丢失
- ✅ **用户友好**: 清晰的界面提示和操作流程
- ✅ **零依赖**: 仅需标准C库

### GUI版本
- ✅ **现代化界面**: 基于GTK+3，美观易用
- ✅ **完整功能**: 与控制台版本功能一致
- ✅ **回单打印**: 模拟银行回单打印功能
- ✅ **响应式设计**: 支持窗口缩放和交互
- ✅ **跨平台**: 支持macOS和Linux

## 🧪 测试账户

- **卡号**: 622202000001-622202000025
- **密码**: 123456

## 🛠️ 系统要求

### 控制台版本
- **操作系统**: macOS 10.14 或更高版本
- **编译器**: GCC (通过Xcode Command Line Tools安装)
- **依赖**: 仅需标准C库

### GUI版本
- **操作系统**: macOS 10.14 或更高版本
- **编译器**: GCC + CMake
- **依赖**: GTK+3开发库

## 📋 安装依赖

### 安装Xcode Command Line Tools

```bash
# 安装Xcode Command Line Tools
xcode-select --install
```

### 安装GTK+3 (GUI版本需要)

```bash
# 使用Homebrew安装GTK+3
brew install gtk+3

# 或使用MacPorts
sudo port install gtk3
```

### 安装CMake (GUI版本需要)

```bash
# 使用Homebrew安装CMake
brew install cmake

# 或使用MacPorts
sudo port install cmake
```

## 🎮 使用指南

### 控制台版本

```bash
# 进入控制台版本目录
cd console-system

# 构建程序
make clean && make

# 运行程序
./run_console.sh
```

### GUI版本

```bash
# 进入GUI版本目录
cd gui-system

# 构建程序
./build.sh

# 运行程序
./atm_gui
```

### 操作流程

1. **启动程序**: 运行相应脚本
2. **登录系统**: 输入卡号和密码
3. **选择功能**: 根据菜单选择操作
4. **完成交易**: 按照提示完成操作
5. **退出系统**: 选择退出选项

## 🔧 开发说明

### 控制台版本构建

```bash
# 清理构建文件
make clean

# 构建程序
make

# 运行程序
make run
```

### GUI版本构建

```bash
# 使用构建脚本
./build.sh

# 或使用CMake
mkdir build && cd build
cmake ..
make
```

### 代码结构

#### 控制台版本
- **main.c**: 主程序入口
- **account_management.c**: 账户管理
- **transaction.c**: 交易功能
- **encryption.c**: 密码加密
- **file_operations.c**: 文件操作
- **ui.c**: 用户界面
- **utils.c**: 工具函数

#### GUI版本
- **gui_main.c**: 主窗口
- **gui_login.c**: 登录界面
- **gui_transaction.c**: 交易界面
- **gui_common.c**: 通用功能
- **gui_main_entry.c**: 程序入口

## 📊 数据文件

- **accounts.dat**: 存储账户信息
- **statements.dat**: 存储交易流水

**注意**: 这些文件由程序自动创建和管理，请勿手动修改。

## 🎯 技术特色

- **纯C语言**: 使用标准C语言开发
- **模块化设计**: 清晰的代码结构，易于维护
- **安全可靠**: 密码加密存储，数据安全
- **用户友好**: 直观的操作界面
- **Mac优化**: 专为macOS系统优化

## 📞 技术支持

- 📖 查看详细文档: 各版本目录下的README.md
- 🐛 提交问题: GitHub Issues
- 📧 联系开发团队

## 📄 许可证

本项目采用MIT许可证，详见LICENSE文件。

---

**享受使用ATM仿真系统！** 🎉