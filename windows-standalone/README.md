# ATM Windows独立版本

## 📋 系统简介

这是ATM仿真系统的Windows独立版本，基于GTK+3开发，提供现代化的图形界面，可以直接在Windows系统上运行。

## 🚀 快速开始

### 1. 构建程序

```cmd
# 运行构建脚本
build_windows.bat
```

### 2. 运行程序

```cmd
# 方式1: 直接运行
atm_windows.exe

# 方式2: 使用启动脚本
run_windows.bat
```

### 3. 创建安装包

```cmd
# 创建分发安装包
create_package.bat
```

## 📁 文件结构

```
windows-standalone/
├── main.c                    # 主程序入口
├── gui_*.c/h                # GUI界面模块
├── account_management.c      # 账户管理
├── encryption.c              # 加密功能
├── file_operations.c         # 文件操作
├── transaction.c             # 交易功能
├── utils.c                   # 工具函数
├── atm_system.h              # 头文件
├── build_windows.bat         # 构建脚本
├── run_windows.bat           # 运行脚本
├── create_package.bat        # 安装包创建脚本
└── README.md                 # 说明文档
```

## 🎯 功能特色

- ✅ **独立运行**: 单个.exe文件，无需安装
- ✅ **现代界面**: GTK+3图形界面
- ✅ **完整功能**: 存款、取款、转账、查询、修改密码
- ✅ **回单打印**: 模拟银行回单打印
- ✅ **安全机制**: 密码验证、账户锁定
- ✅ **数据持久化**: 本地文件存储

## 🧪 测试账户

- **卡号**: 622202000001-622202000025
- **密码**: 123456

## 🔧 系统要求

### 必需依赖
- **操作系统**: Windows 10/11
- **运行时**: GTK+3运行时库
- **编译器**: MinGW-w64 GCC (仅构建时需要)

### 可选依赖
- Visual C++ Redistributable
- Windows SDK

## 🏗️ 构建说明

### 环境准备

1. **安装MinGW-w64**
   ```cmd
   # 下载并安装MSYS2
   # https://www.msys2.org/
   ```

2. **安装GTK+3开发库**
   ```bash
   # 在MSYS2中运行
   pacman -S mingw-w64-x86_64-gtk3
   pacman -S mingw-w64-x86_64-pkg-config
   ```

3. **设置环境变量**
   ```
   PATH = C:\msys64\mingw64\bin;%PATH%
   ```

### 构建过程

```cmd
# 1. 检查环境
where gcc
where pkg-config

# 2. 构建程序
build_windows.bat

# 3. 测试运行
run_windows.bat
```

## 📦 分发说明

### 创建安装包

```cmd
# 运行安装包创建脚本
create_package.bat
```

### 安装包内容

- `atm_windows.exe` - 主程序
- `run_windows.bat` - 运行脚本
- `README.txt` - 用户说明
- `install.bat` - 安装脚本
- `uninstall.bat` - 卸载脚本
- `ATM系统.bat` - 快速启动

### 用户安装

1. **解压安装包**
2. **运行install.bat** (检查依赖)
3. **双击ATM系统.bat** (启动程序)

## 🎮 使用指南

### 启动程序

1. **直接启动**
   ```cmd
   atm_windows.exe
   ```

2. **使用脚本启动**
   ```cmd
   run_windows.bat
   ```

### 操作流程

1. **登录系统**: 输入卡号和密码
2. **选择功能**: 点击相应按钮
3. **输入信息**: 填写交易详情
4. **确认交易**: 查看确认信息
5. **打印回单**: 选择是否打印回单

## 🔍 故障排除

### 常见问题

#### 1. "未找到GTK+3"错误

**解决方案**:
```cmd
# 下载GTK+3运行时
# https://www.gtk.org/download/

# 解压到 C:\gtk3\
# 添加到PATH: C:\gtk3\bin
```

#### 2. "程序无法启动"错误

**解决方案**:
- 安装Visual C++ Redistributable
- 检查系统架构匹配 (x64/x86)
- 重新构建程序

#### 3. "编译失败"错误

**解决方案**:
- 检查MinGW-w64安装
- 验证GTK+3开发库
- 检查pkg-config配置

### 环境检查

```cmd
# 检查编译器
where gcc

# 检查GTK+3
pkg-config --cflags gtk+-3.0
pkg-config --libs gtk+-3.0

# 检查运行时
where gtk3-demo
```

## 📊 性能优化

### 编译优化

```cmd
# 使用优化编译
gcc -O2 -Wall -Wextra -std=c99 %GTK_CFLAGS% *.c %GTK_LIBS% -o atm_windows.exe
```

### 运行时优化

- 使用静态链接减少依赖
- 优化GUI组件加载
- 内存使用优化

## 🎯 开发说明

### 代码结构

- **main.c**: 程序入口和初始化
- **gui_*.c**: GUI界面实现
- **account_management.c**: 账户管理
- **transaction.c**: 交易功能
- **utils.c**: 工具函数

### 扩展功能

- 添加新的交易类型
- 自定义界面主题
- 增强安全功能
- 优化用户体验

## 📞 技术支持

- 📖 查看项目文档
- 🐛 提交GitHub Issue
- 📧 联系开发团队

## 📄 许可证

本项目采用MIT许可证，详见LICENSE文件。

---

**享受使用ATM Windows独立版本！** 🎉
