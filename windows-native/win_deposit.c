#include "win_gui.h"
#include "atm_system.h"

// 全局变量
HWND hDepositWindow = NULL;

/**
 * 创建存款窗口
 */
BOOL createDepositWindow(HINSTANCE hInstance) {
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = DepositWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "ATMDepositWindow";
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(1));
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(1));

    if (!RegisterClassEx(&wc)) {
        return FALSE;
    }

    hDepositWindow = CreateWindowEx(
        0,
        "ATMDepositWindow",
        "ATM系统 - 存款",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        450, 400,
        hTransactionWindow, NULL, hInstance, NULL
    );

    if (!hDepositWindow) {
        return FALSE;
    }

    setWindowIcon(hDepositWindow, hInstance);
    centerWindow(hDepositWindow);
    return TRUE;
}

/**
 * 存款窗口过程
 */
LRESULT CALLBACK DepositWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // 创建标题
            createLabel(hwnd, ID_MAIN_TITLE, "存款", 50, 20, 350, 30);
            
            // 显示当前余额
            char balanceInfo[100];
            int userIndex = -1;
            for (int i = 0; i < accountCount; i++) {
                if (strcmp(accounts[i].ID, currentAccount) == 0) {
                    userIndex = i;
                    break;
                }
            }
            
            if (userIndex != -1) {
                snprintf(balanceInfo, sizeof(balanceInfo), "当前余额：¥%.2f", accounts[userIndex].money);
                createLabel(hwnd, 0, balanceInfo, 50, 60, 350, 20);
            }
            
            // 创建金额输入
            createLabel(hwnd, 0, "请输入存款金额：", 50, 100, 150, 20);
            createEdit(hwnd, ID_DEPOSIT_AMOUNT_EDIT, 50, 125, 350, 25, FALSE);
            
            // 创建快速金额按钮
            createLabel(hwnd, 0, "快速选择金额：", 50, 160, 150, 20);
            createButton(hwnd, ID_DEPOSIT_QUICK_100, "100", 50, 185, 80, 30);
            createButton(hwnd, ID_DEPOSIT_QUICK_500, "500", 140, 185, 80, 30);
            createButton(hwnd, ID_DEPOSIT_QUICK_1000, "1000", 230, 185, 80, 30);
            createButton(hwnd, ID_DEPOSIT_QUICK_2000, "2000", 320, 185, 80, 30);
            
            // 创建按钮
            createButton(hwnd, ID_DEPOSIT_CONFIRM_BUTTON, "确认存款", 120, 250, 100, 35);
            createButton(hwnd, ID_DEPOSIT_CANCEL_BUTTON, "取消", 280, 250, 100, 35);
            break;
        }
        
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case ID_DEPOSIT_CONFIRM_BUTTON:
                    onDepositConfirm();
                    break;
                    
                case ID_DEPOSIT_CANCEL_BUTTON:
                    onDepositCancel();
                    break;
                    
                case ID_DEPOSIT_QUICK_100:
                    onQuickAmount(100);
                    break;
                    
                case ID_DEPOSIT_QUICK_500:
                    onQuickAmount(500);
                    break;
                    
                case ID_DEPOSIT_QUICK_1000:
                    onQuickAmount(1000);
                    break;
                    
                case ID_DEPOSIT_QUICK_2000:
                    onQuickAmount(2000);
                    break;
            }
            break;
        }
        
        case WM_CLOSE:
            onDepositCancel();
            return 0;
            
        case WM_DESTROY:
            hDepositWindow = NULL;
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/**
 * 存款确认
 */
void onDepositConfirm() {
    char amountText[50] = {0};
    GetWindowTextA(GetDlgItem(hDepositWindow, ID_DEPOSIT_AMOUNT_EDIT), amountText, sizeof(amountText));
    
    if (strlen(amountText) == 0) {
        showErrorMessage("请输入存款金额！");
        return;
    }
    
    double amount = atof(amountText);
    if (amount <= 0) {
        showErrorMessage("存款金额必须大于0！");
        return;
    }
    
    if (amount > 50000) {
        showErrorMessage("单次存款金额不能超过50,000元！");
        return;
    }
    
    // 显示确认对话框
    char confirmMessage[200];
    snprintf(confirmMessage, sizeof(confirmMessage), 
             "确认存款 ¥%.2f 元？\n\n存款后余额将更新。", amount);
    
    if (showConfirmDialog(confirmMessage)) {
        if (performDeposit(amount)) {
            char successMessage[200];
            snprintf(successMessage, sizeof(successMessage), 
                     "存款成功！\n\n存款金额：¥%.2f\n请保存好回单。", amount);
            showSuccessMessage(successMessage);
            
            // 关闭存款窗口，更新交易窗口
            ShowWindow(hDepositWindow, SW_HIDE);
            EnableWindow(hTransactionWindow, TRUE);
            updateUserInfo();
            SetFocus(hTransactionWindow);
        } else {
            showErrorMessage("存款失败，请重试！");
        }
    }
}

/**
 * 存款取消
 */
void onDepositCancel() {
    ShowWindow(hDepositWindow, SW_HIDE);
    EnableWindow(hTransactionWindow, TRUE);
    SetFocus(hTransactionWindow);
}

/**
 * 快速金额选择
 */
void onQuickAmount(int amount) {
    char amountText[20];
    snprintf(amountText, sizeof(amountText), "%d", amount);
    SetWindowTextA(GetDlgItem(hDepositWindow, ID_DEPOSIT_AMOUNT_EDIT), amountText);
}
