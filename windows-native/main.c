#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "atm_system.h"
#include "win_gui.h"

// 全局变量定义
Account accounts[MAX_ACCOUNTS];
Statement statements[MAX_STATEMENTS];
int accountCount = 0;
int statementCount = 0;
char currentAccount[20] = "";

// Windows窗口句柄
HWND hMainWindow = NULL;
HWND hLoginWindow = NULL;
HWND hTransactionWindow = NULL;

/**
 * 初始化系统数据
 */
void initializeSystem() {
    // 加载账户数据
    if (!loadAccounts()) {
        createTestData();
    }

    // 加载流水数据
    loadStatements();
}

/**
 * 创建测试数据
 */
void createTestData() {
    // 创建25个测试账户
    for (int i = 0; i < 25; i++) {
        snprintf(accounts[i].ID, sizeof(accounts[i].ID), "622202000%03d", i + 1);
        snprintf(accounts[i].name, sizeof(accounts[i].name), "用户%d", i + 1);
        accounts[i].money = 10000.0 + i * 1000.0; // 不同余额
        accounts[i].isLocked = 0;
        
        // 设置默认密码123456
        int defaultPassword[6] = {1, 2, 3, 4, 5, 6};
        encryptPassword(defaultPassword, accounts[i].password);
    }
    
    accountCount = 25;
    saveAccounts();
}

/**
 * 显示错误消息框
 */
void showErrorMessage(const char* message) {
    MessageBoxA(NULL, message, "ATM系统 - 错误", MB_OK | MB_ICONERROR);
}

/**
 * 显示成功消息框
 */
void showSuccessMessage(const char* message) {
    MessageBoxA(NULL, message, "ATM系统 - 成功", MB_OK | MB_ICONINFORMATION);
}

/**
 * 显示信息消息框
 */
void showInfoMessage(const char* message) {
    MessageBoxA(NULL, message, "ATM系统 - 信息", MB_OK | MB_ICONINFORMATION);
}

/**
 * 显示确认对话框
 */
int showConfirmDialog(const char* message) {
    int result = MessageBoxA(NULL, message, "ATM系统 - 确认", MB_YESNO | MB_ICONQUESTION);
    return (result == IDYES);
}

/**
 * 获取当前时间字符串
 */
void getCurrentTime(char* timeStr) {
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);
    strftime(timeStr, 50, "%Y-%m-%d %H:%M:%S", tm_info);
}

/**
 * 生成流水ID
 */
void generateStatementID(char* id) {
    static int counter = 1;
    snprintf(id, 20, "ST%08d", counter++);
}

/**
 * Windows版本主程序入口
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 初始化随机数种子
    srand((unsigned int)time(NULL));

    // 初始化通用控件
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    // 初始化系统数据
    initializeSystem();
    
    // 创建并显示主窗口
    if (!createMainWindow(hInstance)) {
        showErrorMessage("无法创建主窗口！");
        return 1;
    }
    
    // 显示主窗口
    ShowWindow(hMainWindow, nCmdShow);
    UpdateWindow(hMainWindow);
    
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}
