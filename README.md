# ATM仿真系统 - 完整项目文档

## 📋 项目概述

ATM仿真系统是一个使用C语言开发的多平台银行系统模拟器，支持macOS和Windows平台，提供控制台和图形用户界面两种交互方式。系统实现了完整的银行ATM功能，包括账户管理、交易处理、安全验证等核心功能。

## 🏗️ 项目架构

### 系统架构图
```
┌─────────────────────────────────────────────────────────────┐
│                    ATM仿真系统架构                            │
├─────────────────────────────────────────────────────────────┤
│  用户界面层 (UI Layer)                                      │
│  ├── 控制台界面 (Console UI)                               │
│  ├── Mac GUI界面 (GTK+3)                                   │
│  └── Windows GUI界面 (Win32 API)                           │
├─────────────────────────────────────────────────────────────┤
│  业务逻辑层 (Business Logic Layer)                         │
│  ├── 账户管理 (Account Management)                         │
│  ├── 交易处理 (Transaction Processing)                     │
│  ├── 安全验证 (Security Validation)                        │
│  └── 数据持久化 (Data Persistence)                         │
├─────────────────────────────────────────────────────────────┤
│  数据访问层 (Data Access Layer)                            │
│  ├── 文件操作 (File Operations)                            │
│  ├── 数据加密 (Data Encryption)                            │
│  └── 数据存储 (Data Storage)                               │
└─────────────────────────────────────────────────────────────┘
```

## 📁 项目结构

```
ATM-Project/
├── console-system/              # Mac控制台版本
│   ├── main.c                   # 主程序入口
│   ├── account_management.c     # 账户管理模块
│   ├── transaction.c             # 交易处理模块
│   ├── encryption.c              # 数据加密模块
│   ├── file_operations.c         # 文件操作模块
│   ├── ui.c                      # 用户界面模块
│   ├── utils.c                   # 工具函数模块
│   ├── atm_system.h              # 系统头文件
│   ├── Makefile                  # 构建配置
│   ├── run_console.sh            # 运行脚本
│   ├── atm_system                # 可执行文件
│   └── README.md                 # 版本说明
├── gui-system/                  # Mac GUI版本
│   ├── gui_main.c              # 主窗口
│   ├── gui_login.c               # 登录界面
│   ├── gui_transaction.c         # 交易界面
│   ├── gui_common.c              # 通用功能
│   ├── gui_main_entry.c          # 程序入口
│   ├── CMakeLists.txt            # CMake配置
│   ├── build.sh                  # 构建脚本
│   ├── test_gui.sh               # 测试脚本
│   ├── atm_gui                   # GUI可执行文件
│   └── README.md                 # 版本说明
├── windows-gui-system/           # Windows GUI版本
│   ├── win_gui_main.c            # 主窗口
│   ├── win_gui_login.c           # 登录界面
│   ├── win_gui_transaction.c     # 交易界面
│   ├── win_gui_common.c          # 通用功能
│   ├── win_gui_main_entry.c      # 程序入口
│   ├── account_management.c      # 账户管理
│   ├── transaction.c             # 交易处理
│   ├── encryption.c              # 数据加密
│   ├── file_operations.c        # 文件操作
│   ├── utils.c                   # 工具函数
│   ├── atm_system.h              # 系统头文件
│   ├── Makefile                  # 构建配置
│   ├── build.bat                 # Windows构建脚本
│   ├── test.bat                  # 测试脚本
│   ├── DEPLOY.md                 # 部署说明
│   ├── PROJECT_SUMMARY.md        # 项目总结
│   └── README.md                 # 版本说明
├── accounts.dat                  # 账户数据文件
├── statements.dat               # 交易流水文件
└── README.md                     # 项目总览 (当前文件)
```

## 🎯 功能模块详解

### 1. 登录登出界面

#### 控制台版本
- **文件位置**: `console-system/ui.c`
- **主要函数**: `showLoginMenu()`, `login()`
- **功能**: 用户身份验证，账户锁定检测

#### Mac GUI版本
- **文件位置**: `gui-system/gui_login.c`
- **主要函数**: `createLoginWindow()`, `on_login_confirm_clicked()`
- **功能**: 图形化登录界面，密码输入验证

#### Windows GUI版本
- **文件位置**: `windows-gui-system/win_gui_login.c`
- **主要函数**: `create_login_window()`, `on_login_confirm()`
- **功能**: Windows原生登录界面，消息处理

### 2. 存取款功能

#### 控制台版本
- **文件位置**: `console-system/transaction.c`
- **主要函数**: `deposit()`, `withdraw()`
- **功能**: 金额验证，余额检查，交易记录

#### Mac GUI版本
- **文件位置**: `gui-system/gui_transaction.c`
- **主要函数**: `create_deposit_window()`, `on_deposit_confirm_clicked()`
- **功能**: 图形化存取款界面，快速金额选择

#### Windows GUI版本
- **文件位置**: `windows-gui-system/win_gui_transaction.c`
- **主要函数**: `create_deposit_window()`, `on_deposit_confirm()`
- **功能**: Windows原生存取款界面，控件交互

### 3. 转账功能

#### 控制台版本
- **文件位置**: `console-system/transaction.c`
- **主要函数**: `transfer()`
- **功能**: 目标账户验证，余额检查，双向交易记录

#### Mac GUI版本
- **文件位置**: `gui-system/gui_transaction.c`
- **主要函数**: `create_transfer_window()`, `on_transfer_confirm_clicked()`
- **功能**: 图形化转账界面，账户验证

#### Windows GUI版本
- **文件位置**: `windows-gui-system/win_gui_transaction.c`
- **主要函数**: `create_transfer_window()`, `on_transfer_confirm()`
- **功能**: Windows原生转账界面，输入验证

### 4. 回单打印功能

#### Mac GUI版本
- **文件位置**: `gui-system/gui_transaction.c`
- **主要函数**: `print_deposit_receipt()`, `print_withdraw_receipt()`, `print_transfer_receipt()`
- **功能**: 格式化回单显示，打印确认

#### Windows GUI版本
- **文件位置**: `windows-gui-system/win_gui_transaction.c`
- **主要函数**: `print_receipt()`, `on_print_receipt_clicked()`
- **功能**: Windows原生回单显示，打印对话框

### 5. 历史记录查询

#### 控制台版本
- **文件位置**: `console-system/transaction.c`
- **主要函数**: `query()`
- **功能**: 账户余额显示，交易历史查询

#### Mac GUI版本
- **文件位置**: `gui-system/gui_transaction.c`
- **主要函数**: `create_query_window()`, `on_query_close_clicked()`
- **功能**: 图形化查询界面，滚动显示历史记录

#### Windows GUI版本
- **文件位置**: `windows-gui-system/win_gui_transaction.c`
- **主要函数**: `create_query_window()`, `on_query_close()`
- **功能**: Windows原生查询界面，列表显示

### 6. 密码修改功能

#### 控制台版本
- **文件位置**: `console-system/transaction.c`
- **主要函数**: `changePassword()`
- **功能**: 密码验证，加密存储

#### Mac GUI版本
- **文件位置**: `gui-system/gui_transaction.c`
- **主要函数**: `create_change_password_window()`, `on_change_password_confirm_clicked()`
- **功能**: 图形化密码修改界面，输入验证

#### Windows GUI版本
- **文件位置**: `windows-gui-system/win_gui_transaction.c`
- **主要函数**: `create_change_password_window()`, `on_change_password_confirm()`
- **功能**: Windows原生密码修改界面，安全验证

## 📄 文件详细说明

### 核心模块文件

#### 1. 账户管理模块 (`account_management.c`)

**实现功能**:
- 账户信息管理
- 账户状态控制
- 账户数据验证

**主要函数**:
- `loadAccounts()`: 加载账户数据
- `saveAccounts()`: 保存账户数据
- `findAccount()`: 查找账户
- `lockAccount()`: 锁定账户
- `unlockAccount()`: 解锁账户

#### 2. 交易处理模块 (`transaction.c`)

**实现功能**:
- 存款交易处理
- 取款交易处理
- 转账交易处理
- 交易记录管理

**主要函数**:
- `deposit()`: 存款处理
- `withdraw()`: 取款处理
- `transfer()`: 转账处理
- `query()`: 查询处理
- `changePassword()`: 密码修改

#### 3. 数据加密模块 (`encryption.c`)

**实现功能**:
- 密码加密存储
- 数据安全验证
- 加密算法实现

**主要函数**:
- `encryptPassword()`: 密码加密
- `decryptPassword()`: 密码解密
- `verifyPassword()`: 密码验证

#### 4. 文件操作模块 (`file_operations.c`)

**实现功能**:
- 数据文件读写
- 文件状态管理
- 数据备份恢复

**主要函数**:
- `loadAccounts()`: 加载账户文件
- `saveAccounts()`: 保存账户文件
- `loadStatements()`: 加载交易流水
- `saveStatements()`: 保存交易流水

#### 5. 工具函数模块 (`utils.c`)

**实现功能**:
- 时间处理
- 字符串操作
- 数据格式化

**主要函数**:
- `getCurrentTime()`: 获取当前时间
- `formatAmount()`: 金额格式化
- `validateInput()`: 输入验证

### 界面模块文件

#### 1. 控制台界面 (`ui.c`)

**实现功能**:
- 控制台菜单显示
- 用户输入处理
- 界面交互控制

**主要函数**:
- `showMainMenu()`: 显示主菜单
- `showLoginMenu()`: 显示登录菜单
- `showTransactionMenu()`: 显示交易菜单
- `waitForKey()`: 等待用户输入

#### 2. Mac GUI界面 (`gui_*.c`)

**实现功能**:
- GTK+3界面创建
- 事件处理
- 界面交互

**主要函数**:
- `create_modern_button()`: 创建按钮
- `create_modern_label()`: 创建标签
- `show_error_dialog()`: 显示错误对话框
- `show_success_dialog()`: 显示成功对话框

#### 3. Windows GUI界面 (`win_gui_*.c`)

**实现功能**:
- Windows API界面创建
- 消息处理
- 控件交互

**主要函数**:
- `createButton()`: 创建按钮
- `createLabel()`: 创建标签
- `createEdit()`: 创建编辑框
- `showErrorMessage()`: 显示错误消息

## 🚀 快速开始

### 环境要求

#### Mac系统
- **操作系统**: macOS 10.14+
- **编译器**: GCC (Xcode Command Line Tools)
- **GUI依赖**: GTK+3 (仅GUI版本需要)

#### Windows系统
- **操作系统**: Windows 10/11
- **编译器**: MinGW-w64 GCC
- **依赖**: Windows SDK

### 安装依赖

#### Mac系统
```bash
# 安装Xcode Command Line Tools
xcode-select --install

# 安装GTK+3 (GUI版本需要)
brew install gtk+3

# 安装CMake (GUI版本需要)
brew install cmake
```

#### Windows系统
```bash
# 安装MinGW-w64
# 下载并安装MSYS2: https://www.msys2.org/

# 在MSYS2中安装开发工具
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
```

### 构建和运行

#### Mac控制台版本
```bash
cd console-system
make clean && make
./run_console.sh
```

#### Mac GUI版本
```bash
cd gui-system
./build.sh
./atm_gui
```

#### Windows GUI版本
```cmd
cd windows-gui-system
build.bat
atm_system.exe
```

## 🧪 测试账户

- **卡号**: 622202000001-622202000025
- **密码**: 123456

## 📊 技术特色

### 1. 跨平台支持
- **Mac系统**: 控制台 + GTK+3 GUI
- **Windows系统**: Win32 API GUI
- **代码复用**: 核心业务逻辑共享

### 2. 安全机制
- **密码加密**: 自定义加密算法
- **账户锁定**: 多次失败自动锁定
- **数据验证**: 输入数据完整性检查

### 3. 用户体验
- **多界面支持**: 控制台 + 图形界面
- **操作友好**: 直观的用户交互
- **错误处理**: 完善的错误提示

### 4. 数据管理
- **持久化存储**: 文件系统数据存储
- **交易记录**: 完整的操作日志
- **数据备份**: 自动数据备份机制

## 🔧 开发说明

### 代码结构
- **模块化设计**: 清晰的模块分离
- **接口统一**: 统一的函数接口
- **错误处理**: 完善的错误处理机制

### 扩展性
- **新功能添加**: 易于扩展新功能
- **界面定制**: 支持界面个性化
- **平台移植**: 易于移植到新平台

## 📞 技术支持

- **项目地址**: https://github.com/quantum-pig/ATM-Project
- **问题反馈**: GitHub Issues
- **技术交流**: 项目讨论区

## 📄 许可证

本项目采用MIT许可证，详见LICENSE文件。

---

**享受使用ATM仿真系统！** 🎉