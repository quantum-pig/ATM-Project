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
        
        // 更新卡号显示
        char cardText[100];
        sprintf(cardText, "卡号: %s", currentAccount);
        
        HWND hCardNumberLabel = GetDlgItem(hwnd, ID_CARD_NUMBER_LABEL);
        if (hCardNumberLabel) {
            SetWindowTextUTF8(hCardNumberLabel, cardText);
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
    
    // 初始化交易记录数组
    memset(recentTransactions, 0, sizeof(recentTransactions));
    
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
    if (g_hChangePasswordWindow) {
        DestroyWindow(g_hChangePasswordWindow);
    }
    
    g_hChangePasswordWindow = CreateChangePasswordWindow(g_hInstance);
    if (g_hChangePasswordWindow) {
        ShowWindow(g_hChangePasswordWindow, SW_SHOW);
        UpdateWindow(g_hChangePasswordWindow);
        
        // 设置焦点到旧密码输入框
        SetFocus(GetDlgItem(g_hChangePasswordWindow, ID_OLD_PASSWORD_EDIT));
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
        // 显示保存银行卡的提示，持续3秒
        ShowMessageBox(g_hMainWindow, "重要提示", 
            "请妥善保管您的银行卡！\n\n"
            "• 请将银行卡放在安全的地方\n"
            "• 不要将银行卡与密码放在一起\n"
            "• 如发现银行卡丢失，请立即联系银行\n"
            "• 感谢您使用ATM服务！", 
            MB_OK | MB_ICONINFORMATION
        );
        
        // 等待3秒
        Sleep(3000);
        
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

/**
 * 修改密码窗口过程
 */
LRESULT CALLBACK ChangePasswordWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            CreateChangePasswordWindowControls(hwnd);
            return 0;
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_CHANGE_PASSWORD_CONFIRM_BUTTON:
                    HandleChangePasswordConfirmButtonClick(hwnd);
                    break;
                    
                case ID_CHANGE_PASSWORD_CANCEL_BUTTON:
                    DestroyWindow(hwnd);
                    break;
            }
            return 0;
            
        case WM_KEYDOWN:
            if (wParam == VK_RETURN) {
                HandleChangePasswordConfirmButtonClick(hwnd);
            } else if (wParam == VK_ESCAPE) {
                DestroyWindow(hwnd);
            }
            return 0;
            
        case WM_DESTROY:
            g_hChangePasswordWindow = NULL;
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/**
 * 创建修改密码窗口
 */
HWND CreateChangePasswordWindow(HINSTANCE hInstance) {
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = ChangePasswordWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"ATMChangePasswordWindow";
    
    RegisterClassExW(&wc);
    
    HWND hwnd = CreateWindowExW(
        0,
        L"ATMChangePasswordWindow",
        L"修改密码",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
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
 * 处理修改密码确认按钮点击
 */
void HandleChangePasswordConfirmButtonClick(HWND hwnd) {
    char oldPasswordStr[20];
    char newPasswordStr[20];
    char confirmPasswordStr[20];
    
    // 获取输入
    GetWindowTextUTF8(GetDlgItem(hwnd, ID_OLD_PASSWORD_EDIT), oldPasswordStr, sizeof(oldPasswordStr));
    GetWindowTextUTF8(GetDlgItem(hwnd, ID_NEW_PASSWORD_EDIT), newPasswordStr, sizeof(newPasswordStr));
    GetWindowTextUTF8(GetDlgItem(hwnd, ID_CONFIRM_PASSWORD_EDIT), confirmPasswordStr, sizeof(confirmPasswordStr));
    
    // 验证输入
    if (strlen(oldPasswordStr) == 0) {
        ShowMessageBox(hwnd, "输入错误", "请输入旧密码！", MB_OK | MB_ICONWARNING);
        return;
    }
    
    if (strlen(newPasswordStr) == 0) {
        ShowMessageBox(hwnd, "输入错误", "请输入新密码！", MB_OK | MB_ICONWARNING);
        return;
    }
    
    if (strlen(confirmPasswordStr) == 0) {
        ShowMessageBox(hwnd, "输入错误", "请确认新密码！", MB_OK | MB_ICONWARNING);
        return;
    }
    
    if (strcmp(newPasswordStr, confirmPasswordStr) != 0) {
        ShowMessageBox(hwnd, "输入错误", "新密码和确认密码不一致！", MB_OK | MB_ICONWARNING);
        return;
    }
    
    if (strlen(newPasswordStr) != 6) {
        ShowMessageBox(hwnd, "输入错误", "密码必须是6位数字！", MB_OK | MB_ICONWARNING);
        return;
    }
    
    // 验证密码是否全为数字
    for (int i = 0; i < 6; i++) {
        if (newPasswordStr[i] < '0' || newPasswordStr[i] > '9') {
            ShowMessageBox(hwnd, "输入错误", "密码必须全为数字！", MB_OK | MB_ICONWARNING);
            return;
        }
    }
    
    for (int i = 0; i < 6; i++) {
        if (confirmPasswordStr[i] < '0' || confirmPasswordStr[i] > '9') {
            ShowMessageBox(hwnd, "输入错误", "确认密码必须全为数字！", MB_OK | MB_ICONWARNING);
            return;
        }
    }
    
    // 验证旧密码 - 从当前账户中获取存储的密码进行验证
    int oldPassword[6];
    for (int i = 0; i < 6; i++) {
        oldPassword[i] = oldPasswordStr[i] - '0';
    }
    
    // 找到当前账户并验证旧密码
    int passwordValid = 0;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            int decryptedPassword[6];
            decryptPassword(accounts[i].password, decryptedPassword);
            
            // 比较输入的旧密码与存储的密码
            passwordValid = 1;
            for (int j = 0; j < 6; j++) {
                if (oldPassword[j] != decryptedPassword[j]) {
                    passwordValid = 0;
                    break;
                }
            }
            break;
        }
    }
    
    if (!passwordValid) {
        ShowMessageBox(hwnd, "密码错误", "旧密码不正确！", MB_OK | MB_ICONERROR);
        return;
    }
    
    // 转换密码为整数数组
    int newPassword[6], confirmPassword[6];
    for (int i = 0; i < 6; i++) {
        newPassword[i] = newPasswordStr[i] - '0';
        confirmPassword[i] = confirmPasswordStr[i] - '0';
    }
    
    // 执行密码修改
    int result = changePassword_gui(newPassword, confirmPassword);
    if (result == 1) {
        ShowMessageBox(hwnd, "修改成功", "密码修改成功！", MB_OK | MB_ICONINFORMATION);
        DestroyWindow(hwnd);
    } else if (result == -1) {
        ShowMessageBox(hwnd, "修改失败", "新密码不能与旧密码相同！", MB_OK | MB_ICONERROR);
    } else {
        ShowMessageBox(hwnd, "修改失败", "密码修改失败！", MB_OK | MB_ICONERROR);
    }
}
