#include "win_gui.h"
#include "atm_system.h"

// 全局变量
HWND hTransactionWindow = NULL;

/**
 * 创建交易窗口
 */
BOOL createTransactionWindow(HINSTANCE hInstance) {
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = TransactionWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "ATMTransactionWindow";
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(1));
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(1));

    if (!RegisterClassEx(&wc)) {
        return FALSE;
    }

    hTransactionWindow = CreateWindowEx(
        0,
        "ATMTransactionWindow",
        "ATM系统 - 交易菜单",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        600, 500,
        hMainWindow, NULL, hInstance, NULL
    );

    if (!hTransactionWindow) {
        return FALSE;
    }

    setWindowIcon(hTransactionWindow, hInstance);
    centerWindow(hTransactionWindow);
    return TRUE;
}

/**
 * 交易窗口过程
 */
LRESULT CALLBACK TransactionWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // 创建用户信息标签
            createLabel(hwnd, ID_TRANS_USER_INFO, "", 20, 20, 560, 30);
            
            // 创建余额标签
            createLabel(hwnd, ID_TRANS_BALANCE_LABEL, "", 20, 60, 560, 30);
            
            // 创建功能按钮
            createButton(hwnd, ID_TRANS_DEPOSIT_BUTTON, "存款", 50, 120, 120, 50);
            createButton(hwnd, ID_TRANS_WITHDRAW_BUTTON, "取款", 200, 120, 120, 50);
            createButton(hwnd, ID_TRANS_TRANSFER_BUTTON, "转账", 350, 120, 120, 50);
            
            createButton(hwnd, ID_TRANS_QUERY_BUTTON, "查询账户", 50, 200, 120, 50);
            createButton(hwnd, ID_TRANS_PASSWORD_BUTTON, "修改密码", 200, 200, 120, 50);
            createButton(hwnd, ID_TRANS_LOGOUT_BUTTON, "退出登录", 350, 200, 120, 50);
            
            // 更新用户信息
            updateUserInfo();
            break;
        }
        
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case ID_TRANS_DEPOSIT_BUTTON:
                    onDeposit();
                    break;
                    
                case ID_TRANS_WITHDRAW_BUTTON:
                    onWithdraw();
                    break;
                    
                case ID_TRANS_TRANSFER_BUTTON:
                    onTransfer();
                    break;
                    
                case ID_TRANS_QUERY_BUTTON:
                    onQuery();
                    break;
                    
                case ID_TRANS_PASSWORD_BUTTON:
                    onChangePassword();
                    break;
                    
                case ID_TRANS_LOGOUT_BUTTON:
                    onLogout();
                    break;
            }
            break;
        }
        
        case WM_CLOSE:
            onLogout();
            return 0;
            
        case WM_DESTROY:
            hTransactionWindow = NULL;
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/**
 * 存款功能
 */
void onDeposit() {
    if (createDepositWindow(GetModuleHandle(NULL))) {
        ShowWindow(hDepositWindow, SW_SHOW);
        EnableWindow(hTransactionWindow, FALSE);
    }
}

/**
 * 取款功能
 */
void onWithdraw() {
    if (createWithdrawWindow(GetModuleHandle(NULL))) {
        ShowWindow(hWithdrawWindow, SW_SHOW);
        EnableWindow(hTransactionWindow, FALSE);
    }
}

/**
 * 转账功能
 */
void onTransfer() {
    if (createTransferWindow(GetModuleHandle(NULL))) {
        ShowWindow(hTransferWindow, SW_SHOW);
        EnableWindow(hTransactionWindow, FALSE);
    }
}

/**
 * 查询功能
 */
void onQuery() {
    if (createQueryWindow(GetModuleHandle(NULL))) {
        ShowWindow(hQueryWindow, SW_SHOW);
        EnableWindow(hTransactionWindow, FALSE);
    }
}

/**
 * 修改密码功能
 */
void onChangePassword() {
    if (createPasswordWindow(GetModuleHandle(NULL))) {
        ShowWindow(hPasswordWindow, SW_SHOW);
        EnableWindow(hTransactionWindow, FALSE);
    }
}

/**
 * 退出登录
 */
void onLogout() {
    if (showConfirmDialog("确定要退出登录吗？")) {
        strcpy(currentAccount, "");
        ShowWindow(hTransactionWindow, SW_HIDE);
        EnableWindow(hMainWindow, TRUE);
        SetFocus(hMainWindow);
    }
}

/**
 * 更新用户信息
 */
void updateUserInfo() {
    if (strlen(currentAccount) == 0) return;
    
    // 查找用户信息
    int userIndex = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            userIndex = i;
            break;
        }
    }
    
    if (userIndex != -1) {
        char userInfo[200];
        char balanceInfo[100];
        
        snprintf(userInfo, sizeof(userInfo), "当前用户：%s (%s)", 
                 accounts[userIndex].name, accounts[userIndex].ID);
        snprintf(balanceInfo, sizeof(balanceInfo), "账户余额：¥%.2f", 
                 accounts[userIndex].money);
        
        SetWindowTextA(GetDlgItem(hTransactionWindow, ID_TRANS_USER_INFO), userInfo);
        SetWindowTextA(GetDlgItem(hTransactionWindow, ID_TRANS_BALANCE_LABEL), balanceInfo);
    }
}
