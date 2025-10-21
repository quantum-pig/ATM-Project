# ATM Windows GUI 部署说明

## 📦 部署特点

- **零外部依赖**: 仅需Windows系统，无需安装额外库
- **轻量级**: 编译后文件约100KB
- **原生性能**: 使用Windows API，运行流畅
- **简单部署**: 单个exe文件即可运行

## 🚀 快速部署

### 方法一：直接运行
```cmd
# 下载或编译得到 atm_gui.exe
# 双击运行即可
atm_gui.exe
```

### 方法二：使用构建脚本
```cmd
# 运行构建脚本
build.bat

# 或使用测试脚本
test.bat
```

## 📋 系统要求

### 最低要求
- **操作系统**: Windows 7 或更高版本
- **内存**: 32MB RAM
- **磁盘空间**: 1MB
- **依赖**: 无外部依赖

### 推荐配置
- **操作系统**: Windows 10 或更高版本
- **内存**: 64MB RAM
- **磁盘空间**: 5MB
- **屏幕分辨率**: 1024x768 或更高

## 🔧 编译环境

### 开发环境要求
- **编译器**: GCC (MinGW-w64) 或 Visual Studio
- **系统**: Windows 7 或更高版本
- **工具**: 命令行工具

### 安装编译环境

#### 方法一：MinGW-w64
1. 下载MSYS2: https://www.msys2.org/
2. 安装MSYS2
3. 在MSYS2中安装GCC:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```

#### 方法二：Visual Studio
1. 安装Visual Studio Community
2. 安装C++开发工具
3. 使用Developer Command Prompt

## 📁 文件结构

```
windows-gui-system/
├── atm_gui.exe              # 主程序（编译后）
├── accounts.dat             # 账户数据文件（运行时生成）
├── statements.dat           # 交易流水文件（运行时生成）
├── build.bat               # 构建脚本
├── test.bat                # 测试脚本
├── README.md               # 说明文档
└── DEPLOY.md               # 部署说明（当前文件）
```

## 🎯 部署步骤

### 1. 编译程序
```cmd
# 使用构建脚本（推荐）
build.bat

# 或手动编译
gcc -o atm_gui.exe *.c -lgdi32 -luser32 -lcomctl32 -mwindows
```

### 2. 测试程序
```cmd
# 运行程序
atm_gui.exe

# 使用测试账户登录
# 卡号: 622202000001
# 密码: 123456
```

### 3. 部署到目标机器
```cmd
# 复制以下文件到目标机器：
# - atm_gui.exe
# - 可选：accounts.dat, statements.dat（如果有数据）
```

## 🔒 安全说明

### 数据安全
- 账户数据存储在本地文件
- 密码使用简单加密存储
- 建议定期备份数据文件

### 文件权限
- 程序需要读写当前目录权限
- 建议在用户目录下运行
- 避免在系统目录运行

## 🐛 故障排除

### 常见问题

#### 1. 程序无法启动
- **原因**: 缺少Windows API支持
- **解决**: 确保在Windows 7+系统运行

#### 2. 编译失败
- **原因**: 缺少GCC编译器
- **解决**: 安装MinGW-w64或Visual Studio

#### 3. 界面显示异常
- **原因**: 系统字体或DPI设置
- **解决**: 调整系统显示设置

#### 4. 数据文件错误
- **原因**: 文件损坏或权限问题
- **解决**: 删除accounts.dat和statements.dat重新生成

### 调试方法

#### 1. 检查依赖
```cmd
# 检查Windows版本
ver

# 检查文件权限
dir atm_gui.exe
```

#### 2. 查看错误信息
```cmd
# 在命令行运行查看错误
atm_gui.exe
```

#### 3. 重新编译
```cmd
# 清理并重新编译
del *.o atm_gui.exe
build.bat
```

## 📊 性能优化

### 编译优化
```cmd
# 使用优化编译
gcc -O2 -s -o atm_gui.exe *.c -lgdi32 -luser32 -lcomctl32 -mwindows
```

### 运行时优化
- 关闭不必要的后台程序
- 确保足够的可用内存
- 使用SSD硬盘提升I/O性能

## 🔄 更新维护

### 数据备份
```cmd
# 备份重要数据
copy accounts.dat accounts_backup.dat
copy statements.dat statements_backup.dat
```

### 程序更新
```cmd
# 停止程序
# 替换atm_gui.exe
# 重新启动程序
```

### 数据迁移
```cmd
# 将数据文件复制到新版本目录
# 确保文件权限正确
```

## 📞 技术支持

### 获取帮助
- 查看README.md文档
- 检查编译错误信息
- 验证系统环境

### 报告问题
- 提供错误信息
- 说明操作步骤
- 包含系统信息

---

**享受使用ATM Windows GUI系统！** 🎉
