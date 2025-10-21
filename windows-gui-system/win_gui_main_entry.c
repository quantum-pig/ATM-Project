#include "win_gui_common.h"

// 全局变量定义
Account accounts[MAX_ACCOUNTS];
Statement statements[MAX_STATEMENTS];
int accountCount = 0;
int statementCount = 0;
char currentAccount[20] = "";

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
    // 创建测试账户数据
    char testNames[][20] = {
        "张三", "李四", "王五", "赵六", "钱七", "孙八", "周九", "吴十",
        "郑十一", "王十二", "冯十三", "陈十四", "褚十五", "卫十六", "蒋十七", "沈十八",
        "韩十九", "杨二十", "朱二一", "秦二二", "尤二三", "许二四", "何二五", "吕二六"
    };
    
    char testIDs[][20] = {
        "622202000001", "622202000002", "622202000003", "622202000004", "622202000005",
        "622202000006", "622202000007", "622202000008", "622202000009", "622202000010",
        "622202000011", "622202000012", "622202000013", "622202000014", "622202000015",
        "622202000016", "622202000017", "622202000018", "622202000019", "622202000020",
        "622202000021", "622202000022", "622202000023", "622202000024", "622202000025"
    };
    
    // 创建25个测试账户
    for (int i = 0; i < 25; i++) {
        strcpy(accounts[i].ID, testIDs[i]);
        strcpy(accounts[i].name, testNames[i]);
        
        // 设置默认密码为123456
        int defaultPassword[6] = {1, 2, 3, 4, 5, 6};
        encryptPassword(defaultPassword, accounts[i].password);
        
        // 设置随机余额
        accounts[i].money = 1000 + (rand() % 50000);
        accounts[i].isLocked = 0;
        accounts[i].wrongAttempts = 0;
    }
    
    accountCount = 25;
    saveAccounts();
    
    // 创建一些测试流水记录
    for (int i = 0; i < 50; i++) {
        Statement testStatement;
        generateStatementID(testStatement.ID);
        strcpy(testStatement.accountID, testIDs[rand() % 25]);
        getCurrentTime(testStatement.time);
        testStatement.type = (rand() % 3) + 1;  // 1-3 对应存款、取款、转账
        testStatement.money = 100 + (rand() % 5000);
        if (testStatement.type == TRANSFER) {
            strcpy(testStatement.toAccount, testIDs[rand() % 25]);
        } else {
            strcpy(testStatement.toAccount, "");
        }
        
        statements[i] = testStatement;
    }
    
    statementCount = 50;
    saveStatements();
}

/**
 * 主程序入口
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG msg;
    
    // 初始化随机数种子
    srand((unsigned int)time(NULL));
    
    // 初始化通用控件
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);
    
    // 保存实例句柄
    g_hInstance = hInstance;
    
    // 初始化系统数据
    initializeSystem();
    
    // 创建登录窗口
    g_hLoginWindow = CreateLoginWindow(hInstance);
    if (!g_hLoginWindow) {
        MessageBoxW(NULL, L"无法创建登录窗口！", L"错误", MB_OK | MB_ICONERROR);
        return 1;
    }
    
    // 显示登录窗口
    ShowWindow(g_hLoginWindow, nCmdShow);
    UpdateWindow(g_hLoginWindow);
    
    // 消息循环
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    // 清理资源
    CleanupGUI();
    
    return (int)msg.wParam;
}

/**
 * 处理登录成功
 */
void HandleLoginSuccess() {
    // 隐藏登录窗口
    HideLoginWindow();
    
    // 创建并显示主窗口
    if (!g_hMainWindow) {
        g_hMainWindow = CreateMainWindow(g_hInstance);
    }
    
    if (g_hMainWindow) {
        ShowMainWindow();
    }
}

/**
 * 处理登录失败
 */
void HandleLoginFailed(const char* errorMessage) {
    if (g_hLoginWindow) {
        ShowMessageBox(g_hLoginWindow, "登录失败", errorMessage, MB_OK | MB_ICONERROR);
    }
}

/**
 * 处理交易成功
 */
void HandleTransactionSuccess() {
    if (g_hMainWindow) {
        SendMessage(g_hMainWindow, WM_USER_TRANSACTION_SUCCESS, 0, 0);
    }
}

/**
 * 处理交易失败
 */
void HandleTransactionFailed(const char* errorMessage) {
    if (g_hTransactionWindow) {
        ShowMessageBox(g_hTransactionWindow, "交易失败", errorMessage, MB_OK | MB_ICONERROR);
    }
}

/**
 * 处理退出登录（主程序版本）
 */
void HandleLogoutMain() {
    // 清空当前账户
    strcpy(currentAccount, "");
    
    // 隐藏主窗口
    HideMainWindow();
    
    // 显示登录窗口
    ShowLoginWindow();
}

/**
 * 处理程序退出
 */
void HandleExit() {
    // 保存数据
    saveAccounts();
    saveStatements();
    
    // 清理资源
    CleanupGUI();
    
    // 退出程序
    PostQuitMessage(0);
}
