# ATM仿真系统 - Windows安装指南

## 🎯 系统要求

- **操作系统**: Windows 10/11 (推荐)
- **内存**: 至少 4GB RAM
- **磁盘空间**: 至少 100MB 可用空间
- **网络**: 用于下载依赖包

## 📦 依赖安装

### 1. 安装开发环境

#### 方法一：使用 MSYS2 (推荐)

1. 下载并安装 [MSYS2](https://www.msys2.org/)
2. 打开 MSYS2 终端，运行以下命令：

```bash
# 更新包管理器
pacman -Syu

# 安装开发工具
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-pkg-config
pacman -S mingw-w64-x86_64-gtk3
pacman -S mingw-w64-x86_64-gtkmm3
```

#### 方法二：使用 Chocolatey

```powershell
# 安装 Chocolatey (如果未安装)
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

# 安装依赖
choco install mingw
choco install cmake
choco install gtk3
```

### 2. 安装 GTK+3 运行时

1. 下载 [GTK+3 运行时](https://www.gtk.org/download/)
2. 解压到 `C:\gtk3\`
3. 将 `C:\gtk3\bin` 添加到系统 PATH 环境变量

## 🚀 快速开始

### 1. 下载项目

```bash
git clone https://github.com/quantum-pig/ATM-Project.git
cd ATM-Project
```

### 2. 构建项目

#### 使用构建脚本 (推荐)

```cmd
# 双击运行
build_windows.bat
```

#### 手动构建

```cmd
# 构建GUI版本
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .

# 构建控制台版本
gcc -Wall -Wextra -std=c99 -g *.c -o atm_system.exe
```

### 3. 运行系统

```cmd
# 双击运行
run_windows.bat
```

## 🎮 使用说明

### 启动方式

1. **图形界面启动器** (推荐)
   - 双击 `run_windows.bat`
   - 选择运行版本
   - 查看系统信息

2. **直接运行**
   - GUI版本: `atm_gui.exe`
   - 控制台版本: `atm_system.exe`

### 测试账户

- **卡号**: 622202000001-622202000025
- **密码**: 123456

## 🔧 故障排除

### 常见问题

#### 1. "未找到 gcc" 错误

**解决方案**:
- 确保已安装 MinGW-w64
- 将 MinGW 的 bin 目录添加到 PATH
- 重启命令提示符

#### 2. "未找到 GTK+3" 错误

**解决方案**:
- 安装 GTK+3 运行时库
- 确保 GTK+3 的 bin 目录在 PATH 中
- 重启应用程序

#### 3. "CMake 配置失败"

**解决方案**:
- 更新 CMake 到最新版本
- 检查 pkg-config 是否正确安装
- 确保 GTK+3 开发库已安装

#### 4. 编译错误

**解决方案**:
- 检查所有依赖是否正确安装
- 确保使用正确的编译器
- 检查源代码文件是否完整

### 环境变量设置

确保以下路径在系统 PATH 中：

```
C:\msys64\mingw64\bin
C:\gtk3\bin
C:\Program Files\CMake\bin
```

## 📁 项目结构

```
ATM-Project/
├── atm_gui.exe          # GUI版本可执行文件
├── atm_system.exe       # 控制台版本可执行文件
├── run_windows.bat      # Windows启动脚本
├── build_windows.bat    # Windows构建脚本
├── CMakeLists.txt       # CMake配置文件
├── gui_*.c/h           # GUI模块源代码
├── *.c/h               # 核心功能源代码
└── 文档/               # 项目文档
```

## 🎯 功能特色

### GUI版本特色
- 🎨 现代化图形界面
- 💰 完整的银行功能
- 🖨️ 回单打印功能
- 🔐 安全验证机制

### 控制台版本特色
- ⚡ 轻量级运行
- 🖥️ 传统命令行界面
- 🔧 服务器友好
- 📊 完整功能支持

## 📞 技术支持

如果遇到问题，请：

1. 检查本指南的故障排除部分
2. 查看项目文档
3. 提交 GitHub Issue
4. 联系开发团队

## 📄 许可证

本项目采用 MIT 许可证，详见 LICENSE 文件。

---

**享受使用 ATM 仿真系统！** 🎉
