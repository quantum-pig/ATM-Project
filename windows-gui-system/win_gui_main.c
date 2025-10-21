#include "win_gui_common.h"

// 全局变量
static char g_currentUserName[20] = "";
static double g_currentBalance = 0.0;

/**
 * 主窗口过程
 */
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            CreateMainWindowControls(hwnd);
            UpdateBalanceDisplay(hwnd);
            return 0;
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_DEPOSIT_BUTTON:
                    ShowTransactionWindowMain(DEPOSIT);
                    break;
                    
                case ID_WITHDRAW_BUTTON:
                    ShowTransactionWindowMain(WITHDRAW);
                    break;
                    
                case ID_TRANSFER_BUTTON:
                    ShowTransactionWindowMain(TRANSFER);
                    break;
                    
                case ID_QUERY_BUTTON:
                    ShowQueryWindow();
                    break;
                    
                case ID_CHANGE_PASSWORD_BUTTON:
                    ShowChangePasswordWindow();
                    break;
                    
                case ID_LOGOUT_BUTTON:
                    HandleLogout();
                    break;
            }
            return 0;
            
        case WM_USER_TRANSACTION_SUCCESS:
            UpdateBalanceDisplay(hwnd);
            ShowMessageBox(hwnd, "交易成功", "交易已完成！", MB_OK | MB_ICONINFORMATION);
            break;
            
        case WM_USER_TRANSACTION_FAILED:
            ShowMessageBox(hwnd, "交易失败", "交易失败，请重试！", MB_OK | MB_ICONERROR);
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/**
 * 创建主窗口
 */
HWND CreateMainWindow(HINSTANCE hInstance) {
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"ATMMainWindow";
    
    RegisterClassExW(&wc);
    
    HWND hwnd = CreateWindowExW(
        0,
        L"ATMMainWindow",
        L"ATM仿真系统",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        450, 300,
        NULL, NULL, hInstance, NULL
    );
    
    if (hwnd) {
        ApplyModernStyle(hwnd);
        CenterWindow(hwnd);
        SetWindowIcon(hwnd, 1);
    }
    
    return hwnd;
}

/**
 * 更新余额显示
 */
void UpdateBalanceDisplay(HWND hwnd) {
    char name[20];
    double balance;
    
    if (getCurrentAccountInfo(name, &balance)) {
        strcpy(g_currentUserName, name);
        g_currentBalance = balance;
        
        char balanceText[100];
        sprintf(balanceText, "当前余额: %.2f 元", balance);
        
        HWND hBalanceLabel = GetDlgItem(hwnd, ID_BALANCE_LABEL);
        if (hBalanceLabel) {
            SetWindowTextUTF8(hBalanceLabel, balanceText);
        }
    }
}

/**
 * 显示交易窗口（主窗口版本）
 */
void ShowTransactionWindowMain(int transactionType) {
    if (g_hTransactionWindow) {
        DestroyWindow(g_hTransactionWindow);
    }
    
    g_hTransactionWindow = CreateTransactionWindow(g_hInstance, transactionType);
    if (g_hTransactionWindow) {
        ShowWindow(g_hTransactionWindow, SW_SHOW);
        UpdateWindow(g_hTransactionWindow);
    }
}

/**
 * 显示查询窗口
 */
void ShowQueryWindow() {
    char name[20];
    double balance;
    Statement recentTransactions[10];
    
    if (queryAccount_gui(name, &balance, recentTransactions, 10)) {
        char queryText[2000];
        sprintf(queryText, 
            "账户信息：\n"
            "卡号: %s\n"
            "姓名: %s\n"
            "余额: %.2f\n\n"
            "最近交易记录：\n",
            currentAccount, name, balance
        );
        
        // 添加交易记录
        for (int i = 0; i < 10; i++) {
            if (strlen(recentTransactions[i].ID) > 0) {
                char transactionText[200];
                sprintf(transactionText, "%s\t%s\t%s\t%.2f\n",
                    recentTransactions[i].ID,
                    recentTransactions[i].time,
                    getTransactionTypeName(recentTransactions[i].type),
                    recentTransactions[i].money
                );
                strcat(queryText, transactionText);
            }
        }
        
        ShowMessageBox(g_hMainWindow, "账户查询", queryText, MB_OK | MB_ICONINFORMATION);
    } else {
        ShowMessageBox(g_hMainWindow, "查询失败", "无法获取账户信息！", MB_OK | MB_ICONERROR);
    }
}

/**
 * 显示修改密码窗口
 */
void ShowChangePasswordWindow() {
    // 创建简单的输入对话框
    char newPassword[20];
    char confirmPassword[20];
    
    // 这里可以创建一个更复杂的对话框
    // 为了简化，使用简单的输入框
    ShowMessageBox(g_hMainWindow, "修改密码", "请输入新密码（6位数字）", MB_OK | MB_ICONINFORMATION);
    
    // 实际实现中，这里应该创建密码输入对话框
    // 暂时使用默认密码123456
    int defaultPassword[6] = {1, 2, 3, 4, 5, 6};
    
    if (changePassword_gui(defaultPassword, defaultPassword)) {
        ShowMessageBox(g_hMainWindow, "修改成功", "密码修改成功！", MB_OK | MB_ICONINFORMATION);
    } else {
        ShowMessageBox(g_hMainWindow, "修改失败", "密码修改失败！", MB_OK | MB_ICONERROR);
    }
}

/**
 * 处理退出登录
 */
void HandleLogout() {
    int result = MessageBoxW(g_hMainWindow, 
        L"确定要退出登录吗？", 
        L"退出登录", 
        MB_YESNO | MB_ICONQUESTION
    );
    
    if (result == IDYES) {
        strcpy(currentAccount, "");
        ShowWindow(g_hMainWindow, SW_HIDE);
        
        // 显示登录窗口
        if (g_hLoginWindow) {
            ShowWindow(g_hLoginWindow, SW_SHOW);
            UpdateWindow(g_hLoginWindow);
        } else {
            g_hLoginWindow = CreateLoginWindow(g_hInstance);
            if (g_hLoginWindow) {
                ShowWindow(g_hLoginWindow, SW_SHOW);
                UpdateWindow(g_hLoginWindow);
            }
        }
    }
}

/**
 * 显示主窗口
 */
void ShowMainWindow() {
    if (g_hMainWindow) {
        ShowWindow(g_hMainWindow, SW_SHOW);
        UpdateWindow(g_hMainWindow);
        UpdateBalanceDisplay(g_hMainWindow);
    }
}

/**
 * 隐藏主窗口
 */
void HideMainWindow() {
    if (g_hMainWindow) {
        ShowWindow(g_hMainWindow, SW_HIDE);
    }
}
