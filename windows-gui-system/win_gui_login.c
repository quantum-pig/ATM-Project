#include "win_gui_common.h"

// 全局变量
static int g_currentTransactionType = 0;

/**
 * 登录窗口过程
 */
LRESULT CALLBACK LoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            CreateLoginWindowControls(hwnd);
            return 0;
            
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_LOGIN_BUTTON:
                    HandleLoginButtonClick(hwnd);
                    break;
                    
                case ID_LOGIN_CANCEL_BUTTON:
                    PostQuitMessage(0);
                    break;
            }
            return 0;
            
        case WM_KEYDOWN:
            if (wParam == VK_RETURN) {
                HandleLoginButtonClick(hwnd);
            } else if (wParam == VK_ESCAPE) {
                PostQuitMessage(0);
            }
            return 0;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/**
 * 创建登录窗口
 */
HWND CreateLoginWindow(HINSTANCE hInstance) {
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = LoginWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"ATMLoginWindow";
    
    RegisterClassExW(&wc);
    
    HWND hwnd = CreateWindowExW(
        0,
        L"ATMLoginWindow",
        L"ATM登录",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 250,
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
 * 处理登录按钮点击
 */
void HandleLoginButtonClick(HWND hwnd) {
    char accountID[20];
    char passwordStr[20];
    int password[6];
    
    // 获取输入的账户ID
    GetWindowTextUTF8(GetDlgItem(hwnd, ID_LOGIN_ACCOUNT_EDIT), accountID, sizeof(accountID));
    
    // 获取输入的密码
    GetWindowTextUTF8(GetDlgItem(hwnd, ID_LOGIN_PASSWORD_EDIT), passwordStr, sizeof(passwordStr));
    
    // 验证输入
    if (strlen(accountID) == 0) {
        ShowMessageBox(hwnd, "输入错误", "请输入卡号！", MB_OK | MB_ICONWARNING);
        return;
    }
    
    if (strlen(passwordStr) != 6) {
        ShowMessageBox(hwnd, "输入错误", "密码必须为6位数字！", MB_OK | MB_ICONWARNING);
        return;
    }
    
    // 转换密码字符串为数字数组
    for (int i = 0; i < 6; i++) {
        if (!isdigit(passwordStr[i])) {
            ShowMessageBox(hwnd, "输入错误", "密码只能包含数字！", MB_OK | MB_ICONWARNING);
            return;
        }
        password[i] = passwordStr[i] - '0';
    }
    
    // 尝试登录
    if (login_gui(accountID, password)) {
        // 登录成功
        ShowMessageBox(hwnd, "登录成功", "登录成功！", MB_OK | MB_ICONINFORMATION);
        
        // 隐藏登录窗口
        ShowWindow(hwnd, SW_HIDE);
        
        // 显示主窗口
        if (g_hMainWindow) {
            ShowMainWindow();
        } else {
            g_hMainWindow = CreateMainWindow(g_hInstance);
            if (g_hMainWindow) {
                ShowMainWindow();
            }
        }
    } else {
        // 登录失败
        char errorMessage[200];
        int wrongAttempts = getAccountWrongAttempts(accountID);
        
        if (isAccountLocked(accountID)) {
            strcpy(errorMessage, "账户已被锁定，请联系银行客服！");
        } else if (wrongAttempts > 0) {
            sprintf(errorMessage, "密码错误！剩余尝试次数: %d", MAX_ATTEMPTS - wrongAttempts);
        } else {
            strcpy(errorMessage, "账户不存在或密码错误！");
        }
        
        ShowMessageBox(hwnd, "登录失败", errorMessage, MB_OK | MB_ICONERROR);
        
        // 清空密码输入框
        SetWindowTextW(GetDlgItem(hwnd, ID_LOGIN_PASSWORD_EDIT), L"");
    }
}

/**
 * 显示登录窗口
 */
void ShowLoginWindow() {
    if (g_hLoginWindow) {
        ShowWindow(g_hLoginWindow, SW_SHOW);
        UpdateWindow(g_hLoginWindow);
        
        // 清空输入框
        SetWindowTextW(GetDlgItem(g_hLoginWindow, ID_LOGIN_ACCOUNT_EDIT), L"");
        SetWindowTextW(GetDlgItem(g_hLoginWindow, ID_LOGIN_PASSWORD_EDIT), L"");
        
        // 设置焦点到账户输入框
        SetFocus(GetDlgItem(g_hLoginWindow, ID_LOGIN_ACCOUNT_EDIT));
    } else {
        g_hLoginWindow = CreateLoginWindow(g_hInstance);
        if (g_hLoginWindow) {
            ShowWindow(g_hLoginWindow, SW_SHOW);
            UpdateWindow(g_hLoginWindow);
            SetFocus(GetDlgItem(g_hLoginWindow, ID_LOGIN_ACCOUNT_EDIT));
        }
    }
}

/**
 * 隐藏登录窗口
 */
void HideLoginWindow() {
    if (g_hLoginWindow) {
        ShowWindow(g_hLoginWindow, SW_HIDE);
    }
}
