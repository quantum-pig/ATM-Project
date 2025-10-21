#include "win_gui_common.h"
#include <stdint.h>

// 全局变量
static int g_currentTransactionType = 0;
static double g_lastTransactionAmount = 0.0;
static char g_lastToAccount[20] = "";

/**
 * 交易窗口过程
 */
LRESULT CALLBACK TransactionWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            {
                CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
                g_currentTransactionType = (int)(intptr_t)cs->lpCreateParams;
                CreateTransactionWindowControls(hwnd, g_currentTransactionType);
            }
            return 0;
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_CONFIRM_BUTTON:
                    HandleConfirmButtonClick(hwnd);
                    break;
                    
                case ID_CANCEL_BUTTON:
                    DestroyWindow(hwnd);
                    break;
                    
                case ID_RECEIPT_BUTTON:
                    HandleReceiptButtonClick(hwnd);
                    break;
            }
            return 0;
            
        case WM_KEYDOWN:
            if (wParam == VK_RETURN) {
                HandleConfirmButtonClick(hwnd);
            } else if (wParam == VK_ESCAPE) {
                DestroyWindow(hwnd);
            }
            return 0;
            
        case WM_DESTROY:
            g_hTransactionWindow = NULL;
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/**
 * 创建交易窗口
 */
HWND CreateTransactionWindow(HINSTANCE hInstance, int transactionType) {
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = TransactionWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"ATMTransactionWindow";
    
    RegisterClassExW(&wc);
    
    const char* title = "";
    switch (transactionType) {
        case DEPOSIT:
            title = "存款功能";
            break;
        case WITHDRAW:
            title = "取款功能";
            break;
        case TRANSFER:
            title = "转账功能";
            break;
    }
    
    HWND hwnd = CreateWindowExW(
        0,
        L"ATMTransactionWindow",
        L"",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        450, 250,
        NULL, NULL, hInstance, (LPVOID)(intptr_t)transactionType
    );
    
    if (hwnd) {
        ApplyModernStyle(hwnd);
        CenterWindow(hwnd);
        SetWindowIcon(hwnd, 1);
        
        // 设置窗口标题
        int titleLen = MultiByteToWideChar(CP_UTF8, 0, title, -1, NULL, 0);
        wchar_t* wTitle = (wchar_t*)malloc(titleLen * sizeof(wchar_t));
        MultiByteToWideChar(CP_UTF8, 0, title, -1, wTitle, titleLen);
        SetWindowTextW(hwnd, wTitle);
        free(wTitle);
    }
    
    return hwnd;
}

/**
 * 处理确认按钮点击
 */
void HandleConfirmButtonClick(HWND hwnd) {
    char amountStr[50];
    char toAccountStr[20];
    double amount;
    
    // 获取金额输入
    GetWindowTextUTF8(GetDlgItem(hwnd, ID_AMOUNT_EDIT), amountStr, sizeof(amountStr));
    
    if (strlen(amountStr) == 0) {
        ShowMessageBox(hwnd, "输入错误", "请输入金额！", MB_OK | MB_ICONWARNING);
        return;
    }
    
    // 验证金额格式
    if (sscanf(amountStr, "%lf", &amount) != 1) {
        ShowMessageBox(hwnd, "输入错误", "请输入有效的金额！", MB_OK | MB_ICONWARNING);
        return;
    }
    
    // 如果是转账，获取对方账户
    if (g_currentTransactionType == TRANSFER) {
        GetWindowTextUTF8(GetDlgItem(hwnd, ID_TO_ACCOUNT_EDIT), toAccountStr, sizeof(toAccountStr));
        
        if (strlen(toAccountStr) == 0) {
            ShowMessageBox(hwnd, "输入错误", "请输入对方账户！", MB_OK | MB_ICONWARNING);
            return;
        }
    }
    
    // 执行交易
    int result = 0;
    char successMessage[200];
    char errorMessage[200];
    
    switch (g_currentTransactionType) {
        case DEPOSIT:
            result = deposit_gui(amount);
            if (result) {
                sprintf(successMessage, "存款成功！金额: %.2f 元", amount);
                g_lastTransactionAmount = amount;
                strcpy(g_lastToAccount, "");
            } else {
                strcpy(errorMessage, "存款失败！");
            }
            break;
            
        case WITHDRAW:
            result = withdraw_gui(amount);
            if (result == 1) {
                sprintf(successMessage, "取款成功！金额: %.2f 元", amount);
                g_lastTransactionAmount = amount;
                strcpy(g_lastToAccount, "");
            } else if (result == -1) {
                strcpy(errorMessage, "余额不足！");
            } else {
                strcpy(errorMessage, "取款失败！");
            }
            break;
            
        case TRANSFER:
            result = transfer_gui(toAccountStr, amount);
            if (result == 1) {
                sprintf(successMessage, "转账成功！金额: %.2f 元，对方账户: %s", amount, toAccountStr);
                g_lastTransactionAmount = amount;
                strcpy(g_lastToAccount, toAccountStr);
            } else if (result == -1) {
                strcpy(errorMessage, "余额不足！");
            } else if (result == -2) {
                strcpy(errorMessage, "对方账户不存在！");
            } else if (result == -3) {
                strcpy(errorMessage, "不能转账给自己！");
            } else {
                strcpy(errorMessage, "转账失败！");
            }
            break;
    }
    
    if (result == 1) {
        ShowMessageBox(hwnd, "交易成功", successMessage, MB_OK | MB_ICONINFORMATION);
        
        // 通知主窗口更新余额
        if (g_hMainWindow) {
            SendMessage(g_hMainWindow, WM_USER_TRANSACTION_SUCCESS, 0, 0);
        }
        
        // 关闭交易窗口
        DestroyWindow(hwnd);
    } else {
        ShowMessageBox(hwnd, "交易失败", errorMessage, MB_OK | MB_ICONERROR);
    }
}

/**
 * 处理回单按钮点击
 */
void HandleReceiptButtonClick(HWND hwnd) {
    if (g_lastTransactionAmount > 0) {
        char receipt[1000];
        if (generateReceipt(g_currentTransactionType, g_lastTransactionAmount, g_lastToAccount, receipt, sizeof(receipt))) {
            ShowMessageBox(hwnd, "交易回单", receipt, MB_OK | MB_ICONINFORMATION);
        } else {
            ShowMessageBox(hwnd, "回单生成失败", "无法生成回单！", MB_OK | MB_ICONERROR);
        }
    } else {
        ShowMessageBox(hwnd, "无交易记录", "没有可打印的交易记录！", MB_OK | MB_ICONWARNING);
    }
}

/**
 * 显示交易窗口
 */
void ShowTransactionWindow(int transactionType) {
    if (g_hTransactionWindow) {
        DestroyWindow(g_hTransactionWindow);
    }
    
    g_hTransactionWindow = CreateTransactionWindow(g_hInstance, transactionType);
    if (g_hTransactionWindow) {
        ShowWindow(g_hTransactionWindow, SW_SHOW);
        UpdateWindow(g_hTransactionWindow);
        
        // 设置焦点到金额输入框
        SetFocus(GetDlgItem(g_hTransactionWindow, ID_AMOUNT_EDIT));
    }
}

/**
 * 隐藏交易窗口
 */
void HideTransactionWindow() {
    if (g_hTransactionWindow) {
        ShowWindow(g_hTransactionWindow, SW_HIDE);
    }
}
