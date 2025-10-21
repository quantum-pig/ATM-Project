# ATM Windows GUI系统

## 📋 系统简介

这是ATM仿真系统的Windows原生GUI版本，使用Windows API (Win32)开发，提供现代化的用户界面，专为Windows系统优化。

## 🚀 快速开始

### 编译和运行

```cmd
# 编译项目
gcc -o atm_gui.exe *.c -lgdi32 -luser32 -lcomctl32

# 运行系统
atm_gui.exe
```

## 📁 文件结构

```
windows-gui-system/
├── atm_system.h              # 系统头文件（从console-system移植）
├── account_management.c      # 账户管理（从console-system移植）
├── transaction.c             # 交易功能（从console-system移植）
├── encryption.c              # 密码加密（从console-system移植）
├── file_operations.c         # 文件操作（从console-system移植）
├── utils.c                   # 工具函数（从console-system移植）
├── win_gui_main.c            # Windows GUI主程序
├── win_gui_login.c           # 登录界面
├── win_gui_transaction.c     # 交易界面
├── win_gui_common.c          # 通用GUI组件
├── win_gui_common.h          # 通用GUI头文件
├── build.bat                 # Windows构建脚本
├── atm_gui.exe               # 可执行文件
└── README.md                 # 说明文档
```

## 🎯 功能特色

- ✅ **原生Windows界面**: 使用Windows API，零外部依赖
- ✅ **完整功能**: 存款、取款、转账、查询、修改密码
- ✅ **回单打印**: 模拟银行回单打印
- ✅ **安全机制**: 密码验证、账户锁定
- ✅ **轻量级**: 编译后文件小，部署简单
- ✅ **用户友好**: 现代化Windows界面设计

## 🧪 测试账户

- **卡号**: 622202000001-622202000025
- **密码**: 123456

## 🔧 系统要求

- **操作系统**: Windows 7 或更高版本
- **编译器**: GCC (MinGW) 或 Visual Studio
- **依赖**: 仅需Windows SDK（系统自带）

## 🏗️ 构建说明

### 使用GCC (MinGW)

```cmd
# 编译项目
gcc -o atm_gui.exe *.c -lgdi32 -luser32 -lcomctl32

# 或使用构建脚本
build.bat
```

### 使用Visual Studio

```cmd
# 使用MSBuild
msbuild atm_gui.sln

# 或使用cl编译器
cl *.c /Fe:atm_gui.exe user32.lib gdi32.lib comctl32.lib
```

## 🎮 使用指南

### 启动系统

1. **直接运行**
   ```cmd
   atm_gui.exe
   ```

2. **使用构建脚本**
   ```cmd
   build.bat
   ```

### 操作流程

1. **登录**: 输入卡号和密码
2. **选择功能**: 点击相应按钮
3. **输入信息**: 填写交易详情
4. **确认交易**: 查看确认信息
5. **打印回单**: 选择是否打印回单

## 🎨 界面特色

### 主界面
- 现代化Windows风格
- 清晰的功能按钮
- 响应式布局

### 交易界面
- 实时余额显示
- 快速金额选择
- 确认对话框

### 回单功能
- 标准银行格式
- 等宽字体显示
- 模拟打印效果

## 🔍 故障排除

### 常见问题

1. **编译错误**
   - 确保安装了GCC或Visual Studio
   - 检查Windows SDK

2. **运行时错误**
   - 确保在Windows系统上运行
   - 检查系统版本兼容性

## 📊 性能优化

- 使用Windows原生API
- 优化的内存管理
- 响应式界面设计
- 最小化依赖

## 🎯 开发说明

### 代码结构

- **win_gui_common.c/h**: 通用组件和样式
- **win_gui_main.c**: 主窗口逻辑
- **win_gui_login.c**: 登录界面
- **win_gui_transaction.c**: 交易功能

### 扩展功能

- 添加新的交易类型
- 自定义界面主题
- 增强安全功能

## 📞 技术支持

如有问题，请查看项目根目录的文档或提交Issue。

---

**享受使用ATM Windows GUI系统！** 🎉
