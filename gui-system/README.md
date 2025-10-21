# ATM GUI系统

## 📋 系统简介

这是ATM仿真系统的图形界面版本，使用GTK+3开发，提供现代化的用户界面，支持跨平台运行。

## 🚀 快速开始

### Linux/macOS

```bash
# 构建项目
./build.sh

# 运行系统
./atm_gui
```

### Windows

```cmd
# 构建项目
build_windows.bat

# 运行系统
run_windows.bat
```

## 📁 文件结构

```
gui-system/
├── gui_main_entry.c         # GUI主程序入口
├── gui_common.c/h          # 通用GUI组件
├── gui_main.c              # 主窗口
├── gui_login.c             # 登录界面
├── gui_transaction.c       # 交易界面
├── CMakeLists.txt          # CMake配置
├── build.sh                # Linux构建脚本
├── build.bat               # Windows构建脚本
├── test_gui.sh             # 测试脚本
├── atm_gui                 # 可执行文件
└── README.md               # 说明文档
```

## 🎯 功能特色

- ✅ **现代化界面**: GTK+3图形界面
- ✅ **完整功能**: 存款、取款、转账、查询、修改密码
- ✅ **回单打印**: 模拟银行回单打印
- ✅ **安全机制**: 密码验证、账户锁定
- ✅ **跨平台**: 支持Linux、macOS、Windows
- ✅ **用户友好**: 直观的操作界面

## 🧪 测试账户

- **卡号**: 622202000001-622202000025
- **密码**: 123456

## 🔧 依赖要求

### Linux/macOS

```bash
# Ubuntu/Debian
sudo apt-get install libgtk-3-dev cmake pkg-config

# CentOS/RHEL
sudo yum install gtk3-devel cmake pkgconfig

# macOS
brew install gtk+3 cmake pkg-config
```

### Windows

- MinGW-w64 或 MSYS2
- GTK+3 运行时库
- CMake
- pkg-config

## 🏗️ 构建说明

### Linux/macOS

```bash
# 使用构建脚本 (推荐)
./build.sh

# 手动构建
mkdir build && cd build
cmake ..
make
```

### Windows

```cmd
# 使用构建脚本 (推荐)
build_windows.bat

# 手动构建
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

## 🎮 使用指南

### 启动系统

1. **运行可执行文件**
   ```bash
   ./atm_gui
   ```

2. **使用启动脚本** (Windows)
   ```cmd
   run_windows.bat
   ```

### 操作流程

1. **登录**: 输入卡号和密码
2. **选择功能**: 点击相应按钮
3. **输入信息**: 填写交易详情
4. **确认交易**: 查看确认信息
5. **打印回单**: 选择是否打印回单

## 🎨 界面特色

### 主界面
- 现代化卡片布局
- 渐变背景设计
- 清晰的功能按钮

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

1. **GTK+3未找到**
   - 安装GTK+3开发库
   - 检查环境变量

2. **编译错误**
   - 检查CMake版本
   - 确保依赖完整

3. **运行时错误**
   - 检查GTK+3运行时
   - 验证库文件路径

## 📊 性能优化

- 使用CMake构建系统
- 优化的GUI组件
- 内存管理优化
- 响应式界面设计

## 🎯 开发说明

### 代码结构

- **gui_common.c/h**: 通用组件和样式
- **gui_main.c**: 主窗口逻辑
- **gui_login.c**: 登录界面
- **gui_transaction.c**: 交易功能

### 扩展功能

- 添加新的交易类型
- 自定义界面主题
- 增强安全功能

## 📞 技术支持

如有问题，请查看项目根目录的文档或提交Issue。

---

**享受使用ATM GUI系统！** 🎉
