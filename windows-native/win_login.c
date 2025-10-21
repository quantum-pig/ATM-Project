#include "win_gui.h"
#include "atm_system.h"

// 全局变量
HWND hLoginWindow = NULL;

/**
 * 创建登录窗口
 */
BOOL createLoginWindow(HINSTANCE hInstance) {
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = LoginWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "ATMLoginWindow";
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(1));
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(1));

    if (!RegisterClassEx(&wc)) {
        return FALSE;
    }

    hLoginWindow = CreateWindowEx(
        0,
        "ATMLoginWindow",
        "ATM系统 - 用户登录",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 350,
        hMainWindow, NULL, hInstance, NULL
    );

    if (!hLoginWindow) {
        return FALSE;
    }

    setWindowIcon(hLoginWindow, hInstance);
    centerWindow(hLoginWindow);
    return TRUE;
}

/**
 * 登录窗口过程
 */
LRESULT CALLBACK LoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // 创建标题
            createLabel(hwnd, ID_MAIN_TITLE, "用户登录", 50, 20, 300, 30);
            
            // 创建卡号标签和输入框
            createLabel(hwnd, 0, "请输入银行卡号：", 50, 70, 150, 20);
            createEdit(hwnd, ID_LOGIN_CARD_EDIT, 50, 95, 300, 25, FALSE);
            
            // 创建密码标签和输入框
            createLabel(hwnd, 0, "请输入6位密码：", 50, 130, 150, 20);
            createEdit(hwnd, ID_LOGIN_PASSWORD_EDIT, 50, 155, 300, 25, TRUE);
            
            // 创建状态标签
            createLabel(hwnd, ID_LOGIN_STATUS_LABEL, "", 50, 190, 300, 20);
            
            // 创建按钮
            createButton(hwnd, ID_LOGIN_CONFIRM_BUTTON, "确认登录", 80, 230, 100, 35);
            createButton(hwnd, ID_LOGIN_BACK_BUTTON, "返回", 220, 230, 100, 35);
            
            // 创建帮助标签
            createLabel(hwnd, 0, "测试账户：622202000001-622202000025\n默认密码：123456", 
                        50, 280, 300, 40);
            break;
        }
        
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case ID_LOGIN_CONFIRM_BUTTON:
                    onLoginConfirm();
                    break;
                    
                case ID_LOGIN_BACK_BUTTON:
                    onLoginBack();
                    break;
            }
            break;
        }
        
        case WM_CLOSE:
            onLoginBack();
            return 0;
            
        case WM_DESTROY:
            hLoginWindow = NULL;
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/**
 * 登录确认
 */
void onLoginConfirm() {
    char cardId[20] = {0};
    char password[10] = {0};
    
    // 获取输入
    GetWindowTextA(GetDlgItem(hLoginWindow, ID_LOGIN_CARD_EDIT), cardId, sizeof(cardId));
    GetWindowTextA(GetDlgItem(hLoginWindow, ID_LOGIN_PASSWORD_EDIT), password, sizeof(password));
    
    // 验证输入
    if (strlen(cardId) == 0) {
        SetWindowTextA(GetDlgItem(hLoginWindow, ID_LOGIN_STATUS_LABEL), "请输入银行卡号！");
        return;
    }
    
    if (strlen(password) == 0) {
        SetWindowTextA(GetDlgItem(hLoginWindow, ID_LOGIN_STATUS_LABEL), "请输入密码！");
        return;
    }
    
    if (strlen(password) != 6) {
        SetWindowTextA(GetDlgItem(hLoginWindow, ID_LOGIN_STATUS_LABEL), "密码必须为6位数字！");
        return;
    }
    
    // 验证登录
    if (verifyLogin(cardId, password)) {
        strcpy(currentAccount, cardId);
        SetWindowTextA(GetDlgItem(hLoginWindow, ID_LOGIN_STATUS_LABEL), "登录成功！");
        
        // 关闭登录窗口，打开交易窗口
        ShowWindow(hLoginWindow, SW_HIDE);
        EnableWindow(hMainWindow, TRUE);
        
        if (createTransactionWindow(GetModuleHandle(NULL))) {
            ShowWindow(hTransactionWindow, SW_SHOW);
        }
    } else {
        SetWindowTextA(GetDlgItem(hLoginWindow, ID_LOGIN_STATUS_LABEL), "卡号或密码错误！");
    }
}

/**
 * 返回主窗口
 */
void onLoginBack() {
    ShowWindow(hLoginWindow, SW_HIDE);
    EnableWindow(hMainWindow, TRUE);
    SetFocus(hMainWindow);
}
