# ATM Windows原生版本

## 📋 系统简介

这是ATM仿真系统的Windows原生版本，使用Windows API (Win32) 开发，提供真正的Windows原生界面，无需任何外部依赖库。

## 🚀 快速开始

### 1. 构建程序

```cmd
# 运行构建脚本
build_windows.bat
```

### 2. 运行程序

```cmd
# 方式1: 直接运行
atm_windows_native.exe

# 方式2: 使用启动脚本
run_windows.bat
```

## 📁 文件结构

```
windows-native/
├── main.c                    # 主程序入口
├── win_gui.h                 # Windows GUI头文件
├── win_main.c                # 主窗口实现
├── win_login.c               # 登录窗口实现
├── win_transaction.c         # 交易窗口实现
├── win_deposit.c             # 存款窗口实现
├── account_management.c      # 账户管理
├── encryption.c              # 加密功能
├── file_operations.c         # 文件操作
├── transaction.c             # 交易功能
├── utils.c                   # 工具函数
├── atm_system.h              # 头文件
├── build_windows.bat         # 构建脚本
├── run_windows.bat           # 运行脚本
└── README.md                 # 说明文档
```

## 🎯 功能特色

- ✅ **Windows原生**: 使用Windows API，真正的原生应用
- ✅ **零依赖**: 无需任何外部库，仅需Windows系统
- ✅ **完整功能**: 存款、取款、转账、查询、修改密码
- ✅ **现代界面**: Windows原生控件，熟悉的操作体验
- ✅ **高性能**: 直接调用系统API，运行效率高
- ✅ **兼容性**: 支持Windows 7/8/10/11

## 🧪 测试账户

- **卡号**: 622202000001-622202000025
- **密码**: 123456

## 🔧 系统要求

### 必需依赖
- **操作系统**: Windows 7/8/10/11
- **编译器**: MinGW-w64 GCC (仅构建时需要)
- **运行时**: 仅需Windows系统库

### 无需依赖
- ❌ GTK+3库
- ❌ 其他第三方库
- ❌ 复杂的运行时环境

## 🏗️ 构建说明

### 环境准备

1. **安装MinGW-w64**
   ```cmd
   # 下载并安装MSYS2
   # https://www.msys2.org/
   ```

2. **设置环境变量**
   ```
   PATH = C:\msys64\mingw64\bin;%PATH%
   ```

### 构建过程

```cmd
# 1. 检查环境
where gcc

# 2. 构建程序
build_windows.bat

# 3. 测试运行
run_windows.bat
```

## 🎮 使用指南

### 启动程序

1. **直接启动**
   ```cmd
   atm_windows_native.exe
   ```

2. **使用脚本启动**
   ```cmd
   run_windows.bat
   ```

### 操作流程

1. **主界面**: 选择"登录系统"
2. **登录界面**: 输入卡号和密码
3. **交易界面**: 选择需要的功能
4. **功能操作**: 按照提示完成操作
5. **退出登录**: 返回主界面

## 🔍 技术实现

### Windows API使用

- **窗口管理**: CreateWindowEx, ShowWindow
- **消息处理**: WndProc, WM_COMMAND
- **控件创建**: CreateWindow, 各种控件类
- **对话框**: MessageBox, 自定义对话框

### 界面设计

- **主窗口**: 欢迎界面，登录入口
- **登录窗口**: 用户身份验证
- **交易窗口**: 功能选择菜单
- **功能窗口**: 具体业务操作

### 数据管理

- **文件存储**: 使用标准C文件操作
- **数据加密**: 自定义加密算法
- **状态管理**: 全局变量管理

## 📊 性能优势

### 与GTK+3版本对比

| 特性 | GTK+3版本 | Windows原生版本 |
|------|-----------|-----------------|
| 依赖库 | GTK+3运行时 | 仅Windows系统 |
| 文件大小 | ~100MB | ~2MB |
| 启动速度 | 较慢 | 快速 |
| 内存占用 | 较高 | 较低 |
| 兼容性 | 需要GTK+3 | 原生支持 |

### 性能特点

- **启动快速**: 无需加载外部库
- **内存占用低**: 直接使用系统API
- **运行稳定**: 原生Windows应用
- **分发简单**: 单个exe文件

## 🔍 故障排除

### 常见问题

#### 1. "未找到gcc"错误

**解决方案**:
```cmd
# 安装MinGW-w64
# 设置PATH环境变量
```

#### 2. "编译失败"错误

**解决方案**:
- 检查MinGW-w64安装
- 验证编译器路径
- 检查源代码完整性

#### 3. "程序无法启动"错误

**解决方案**:
- 检查Windows版本兼容性
- 重新构建程序
- 检查系统权限

### 环境检查

```cmd
# 检查编译器
where gcc

# 检查Windows版本
ver

# 检查系统架构
echo %PROCESSOR_ARCHITECTURE%
```

## 🎯 开发说明

### 代码结构

- **main.c**: 程序入口和初始化
- **win_*.c**: Windows界面实现
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

**享受使用ATM Windows原生版本！** 🎉
