# ATM项目结构说明

## 📁 目录结构

```
ATM-Project/
├── console-system/          # 控制台版本
│   ├── *.c/h              # 源代码文件
│   ├── Makefile           # 编译配置
│   ├── atm_system         # 可执行文件
│   ├── run_console.sh     # Linux启动脚本
│   ├── run_console.bat    # Windows启动脚本
│   └── README.md          # 控制台版本说明
├── gui-system/            # GUI版本
│   ├── gui_*.c/h          # GUI源代码
│   ├── CMakeLists.txt     # CMake配置
│   ├── atm_gui            # 可执行文件
│   ├── build.sh           # Linux构建脚本
│   ├── build.bat          # Windows构建脚本
│   ├── test_gui.sh        # 测试脚本
│   └── README.md          # GUI版本说明
├── docs/                  # 项目文档
│   ├── GUI_README.md      # GUI详细说明
│   ├── Windows安装指南.md  # Windows安装指南
│   ├── 项目总结_GUI版本.md  # GUI版本总结
│   ├── 修复测试说明.md     # 修复说明
│   └── 项目总结.md         # 项目总结
├── scripts/               # 通用脚本
│   ├── run_windows.bat    # Windows运行脚本
│   ├── build_windows.bat  # Windows构建脚本
│   └── start.bat          # 快速启动脚本
├── build/                 # 构建目录
├── *.dat                  # 数据文件
├── README.md              # 项目总览
└── PROJECT_STRUCTURE.md   # 结构说明
```

## 🎯 版本说明

### 控制台版本 (console-system/)
- **特点**: 轻量级、无图形依赖
- **适用**: 服务器环境、学习用途
- **启动**: `./run_console.sh` 或 `run_console.bat`

### GUI版本 (gui-system/)
- **特点**: 现代化界面、用户友好
- **适用**: 桌面环境、演示用途
- **启动**: `./atm_gui` 或 `run_windows.bat`

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

## 📋 文件说明

### 核心文件
- `main.c` / `gui_main_entry.c`: 程序入口
- `atm_system.h`: 头文件定义
- `*.c`: 功能模块实现

### 构建文件
- `Makefile`: 控制台版本编译配置
- `CMakeLists.txt`: GUI版本编译配置
- `build.sh` / `build.bat`: 构建脚本

### 启动文件
- `run_console.sh` / `run_console.bat`: 控制台启动
- `atm_gui`: GUI可执行文件
- `start.bat`: Windows快速启动

### 文档文件
- `README.md`: 各版本说明
- `docs/`: 详细文档
- `PROJECT_STRUCTURE.md`: 结构说明

## 🔧 开发说明

### 添加新功能
1. 在对应版本目录下修改源代码
2. 更新README文档
3. 测试功能完整性
4. 提交代码更改

### 构建项目
1. 控制台版本: 使用Makefile
2. GUI版本: 使用CMake
3. 跨平台: 使用对应脚本

### 测试项目
1. 功能测试: 验证所有功能
2. 界面测试: 检查用户体验
3. 兼容性测试: 验证跨平台支持

## 📞 技术支持

- 查看各版本README
- 参考docs目录文档
- 提交GitHub Issue

---

**项目结构清晰，便于维护和扩展！** 🎉
