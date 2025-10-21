# ATM仿真系统 - 现代化GUI版本

## 项目概述

这是ATM仿真系统的现代化GUI版本，使用GTK+3图形库开发，支持跨平台运行（macOS和Windows）。界面采用现代化设计，提供直观易用的用户体验。

## 功能特性

### 🎨 现代化界面
- 渐变背景和卡片式设计
- 响应式按钮和输入框
- 优雅的动画效果
- 中文界面支持

### 🔐 安全功能
- 密码隐藏输入
- 账户锁定机制
- 交易验证
- 错误提示对话框

### 💰 完整交易功能
- 存款/取款
- 转账功能
- 账户查询
- 密码修改
- 交易历史

## 系统要求

### macOS
- macOS 10.14 或更高版本
- Xcode Command Line Tools
- Homebrew（推荐）

### Windows
- Windows 10 或更高版本
- MSYS2 环境

## 安装依赖

### macOS安装
```bash
# 安装Homebrew（如果未安装）
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# 安装依赖
brew install gtk+3 pkg-config cmake

# 或者使用脚本自动安装
npm run install-deps-mac
```

### Windows安装
1. 下载并安装 [MSYS2](https://www.msys2.org/)
2. 打开MSYS2终端，运行：
```bash
pacman -S mingw-w64-x86_64-gtk3 mingw-w64-x86_64-pkg-config mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc
```

## 编译和运行

### 自动编译（推荐）

#### macOS/Linux
```bash
# 给脚本执行权限
chmod +x build.sh

# 运行构建脚本
./build.sh
```

#### Windows
```cmd
# 在MSYS2终端中运行
./build.bat
```

### 手动编译

#### 使用CMake
```bash
# 创建构建目录
mkdir build && cd build

# 配置项目
cmake .. -DCMAKE_BUILD_TYPE=Release

# 编译
make -j4

# 运行
./atm_gui
```

#### 使用传统Makefile（控制台版本）
```bash
# 编译控制台版本
make

# 运行控制台版本
./atm_system
```

## 运行程序

### GUI版本
```bash
./atm_gui
```

### 控制台版本
```bash
./atm_system
```

## 测试账户

系统预置了25个测试账户：

| 卡号 | 密码 | 姓名 | 余额范围 |
|------|------|------|----------|
| 622202000001 | 123456 | 张三 | 随机 |
| 622202000002 | 123456 | 李四 | 随机 |
| ... | ... | ... | ... |
| 622202000025 | 123456 | 吕二六 | 随机 |

## 界面预览

### 主界面
- 渐变背景设计
- 现代化卡片布局
- 清晰的按钮设计

### 登录界面
- 密码隐藏输入
- 实时验证反馈
- 友好的错误提示

### 交易界面
- 网格布局的功能按钮
- 实时余额显示
- 直观的操作流程

## 技术架构

### 图形库
- **GTK+3**: 跨平台图形界面库
- **CSS样式**: 现代化界面设计
- **响应式布局**: 适配不同屏幕尺寸

### 系统架构
```
GUI层 (GTK+3)
    ↓
业务逻辑层 (原有ATM系统)
    ↓
数据层 (文件存储)
```

### 文件结构
```
ATM-Project/
├── gui_common.h/c          # GUI通用功能
├── gui_main.h/c            # 主窗口
├── gui_login.h/c           # 登录界面
├── gui_transaction.h/c     # 交易界面
├── gui_main_entry.c        # GUI主程序入口
├── CMakeLists.txt          # CMake配置
├── build.sh               # macOS/Linux构建脚本
├── build.bat              # Windows构建脚本
└── package.json           # 项目配置
```

## 开发说明

### 添加新功能
1. 在相应的GUI模块中添加界面控件
2. 实现事件处理函数
3. 集成到现有的业务逻辑中

### 样式定制
修改 `gui_common.c` 中的CSS样式字符串来自定义界面外观。

### 跨平台兼容性
- 使用GTK+3确保跨平台兼容性
- 条件编译处理平台差异
- 统一的构建脚本

## 故障排除

### 常见问题

#### 1. 编译错误：找不到GTK3
**解决方案：**
- macOS: `brew install gtk+3 pkg-config`
- Windows: 在MSYS2中安装GTK3开发库

#### 2. 运行时错误：找不到GTK库
**解决方案：**
- 确保GTK3运行时库已安装
- 检查环境变量设置

#### 3. 界面显示异常
**解决方案：**
- 检查GTK主题设置
- 更新图形驱动程序

### 调试模式
```bash
# 启用调试信息
export GTK_DEBUG=1
./atm_gui
```

## 性能优化

### 编译优化
- 使用Release模式编译
- 启用编译器优化选项
- 静态链接减少依赖

### 运行时优化
- 延迟加载非关键资源
- 缓存常用数据
- 异步处理耗时操作

## 部署说明

### 打包发布
```bash
# 创建发布包
tar -czf atm_gui_release.tar.gz atm_gui README.md

# Windows
zip atm_gui_windows.zip atm_gui.exe README.md
```

### 安装程序
可以创建安装程序来简化部署：
- macOS: 使用PackageMaker或pkgbuild
- Windows: 使用NSIS或Inno Setup

## 贡献指南

1. Fork项目
2. 创建功能分支
3. 提交更改
4. 创建Pull Request

## 许可证

MIT License - 详见LICENSE文件

## 联系方式

如有问题或建议，请通过以下方式联系：
- 项目Issues
- 邮箱联系
- 技术讨论群

---

**注意：** 这是一个教学项目，仅用于学习和演示目的。在生产环境中使用前，请确保进行充分的安全测试。

