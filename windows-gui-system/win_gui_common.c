#include "win_gui_common.h"

// 全局变量定义
HWND g_hMainWindow = NULL;
HWND g_hLoginWindow = NULL;
HWND g_hTransactionWindow = NULL;
HINSTANCE g_hInstance = NULL;

// 字体句柄
static HFONT g_hFont = NULL;
static HFONT g_hTitleFont = NULL;

/**
 * 显示消息框
 */
void ShowMessageBox(HWND hwnd, const char* title, const char* message, UINT type) {
    // 将UTF-8字符串转换为宽字符
    int titleLen = MultiByteToWideChar(CP_UTF8, 0, title, -1, NULL, 0);
    int messageLen = MultiByteToWideChar(CP_UTF8, 0, message, -1, NULL, 0);
    
    wchar_t* wTitle = (wchar_t*)malloc(titleLen * sizeof(wchar_t));
    wchar_t* wMessage = (wchar_t*)malloc(messageLen * sizeof(wchar_t));
    
    MultiByteToWideChar(CP_UTF8, 0, title, -1, wTitle, titleLen);
    MultiByteToWideChar(CP_UTF8, 0, message, -1, wMessage, messageLen);
    
    MessageBoxW(hwnd, wMessage, wTitle, type);
    
    free(wTitle);
    free(wMessage);
}

/**
 * 设置窗口文本（UTF-8）
 */
void SetWindowTextUTF8(HWND hwnd, const char* text) {
    int len = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
    wchar_t* wText = (wchar_t*)malloc(len * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, text, -1, wText, len);
    SetWindowTextW(hwnd, wText);
    free(wText);
}

/**
 * 获取窗口文本（UTF-8）
 */
void GetWindowTextUTF8(HWND hwnd, char* buffer, int bufferSize) {
    int len = GetWindowTextLengthW(hwnd) + 1;
    wchar_t* wText = (wchar_t*)malloc(len * sizeof(wchar_t));
    GetWindowTextW(hwnd, wText, len);
    
    WideCharToMultiByte(CP_UTF8, 0, wText, -1, buffer, bufferSize, NULL, NULL);
    free(wText);
}

/**
 * 窗口居中显示
 */
void CenterWindow(HWND hwnd) {
    RECT rect;
    GetWindowRect(hwnd, &rect);
    
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    
    int x = (screenWidth - width) / 2;
    int y = (screenHeight - height) / 2;
    
    SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

/**
 * 设置窗口图标
 */
void SetWindowIcon(HWND hwnd, int iconId) {
    HICON hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(iconId));
    if (hIcon) {
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    }
}

/**
 * 应用现代化样式
 */
void ApplyModernStyle(HWND hwnd) {
    // 设置窗口样式
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_THICKFRAME;
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);
    
    // 设置扩展样式
    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    exStyle |= WS_EX_CLIENTEDGE;
    SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);
}

/**
 * 设置控件字体
 */
void SetControlFont(HWND hwnd, const char* fontName, int fontSize) {
    if (g_hFont) {
        DeleteObject(g_hFont);
    }
    
    int len = MultiByteToWideChar(CP_UTF8, 0, fontName, -1, NULL, 0);
    wchar_t* wFontName = (wchar_t*)malloc(len * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, fontName, -1, wFontName, len);
    
    g_hFont = CreateFontW(
        fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, wFontName
    );
    
    free(wFontName);
    
    if (g_hFont) {
        SendMessage(hwnd, WM_SETFONT, (WPARAM)g_hFont, TRUE);
    }
}

/**
 * 创建主窗口控件
 */
void CreateMainWindowControls(HWND hwnd) {
    // 创建标题标签
    HWND hTitleLabel = CreateWindowW(
        L"STATIC", L"ATM仿真系统",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        20, 20, 360, 40,
        hwnd, (HMENU)ID_BALANCE_LABEL, g_hInstance, NULL
    );
    
    // 创建余额显示标签
    HWND hBalanceLabel = CreateWindowW(
        L"STATIC", L"当前余额: 0.00 元",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        20, 70, 360, 30,
        hwnd, (HMENU)ID_BALANCE_LABEL, g_hInstance, NULL
    );
    
    // 创建功能按钮
    HWND hDepositButton = CreateWindowW(
        L"BUTTON", L"存款",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        50, 120, 100, 40,
        hwnd, (HMENU)ID_DEPOSIT_BUTTON, g_hInstance, NULL
    );
    
    HWND hWithdrawButton = CreateWindowW(
        L"BUTTON", L"取款",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        170, 120, 100, 40,
        hwnd, (HMENU)ID_WITHDRAW_BUTTON, g_hInstance, NULL
    );
    
    HWND hTransferButton = CreateWindowW(
        L"BUTTON", L"转账",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        290, 120, 100, 40,
        hwnd, (HMENU)ID_TRANSFER_BUTTON, g_hInstance, NULL
    );
    
    HWND hQueryButton = CreateWindowW(
        L"BUTTON", L"查询",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        50, 180, 100, 40,
        hwnd, (HMENU)ID_QUERY_BUTTON, g_hInstance, NULL
    );
    
    HWND hChangePasswordButton = CreateWindowW(
        L"BUTTON", L"修改密码",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        170, 180, 100, 40,
        hwnd, (HMENU)ID_CHANGE_PASSWORD_BUTTON, g_hInstance, NULL
    );
    
    HWND hLogoutButton = CreateWindowW(
        L"BUTTON", L"退出登录",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        290, 180, 100, 40,
        hwnd, (HMENU)ID_LOGOUT_BUTTON, g_hInstance, NULL
    );
    
    // 设置字体
    SetControlFont(hwnd, "Microsoft YaHei", 12);
}

/**
 * 创建登录窗口控件
 */
void CreateLoginWindowControls(HWND hwnd) {
    // 创建标题标签
    HWND hTitleLabel = CreateWindowW(
        L"STATIC", L"ATM登录系统",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        20, 20, 360, 30,
        hwnd, NULL, g_hInstance, NULL
    );
    
    // 创建账户输入标签和编辑框
    HWND hAccountLabel = CreateWindowW(
        L"STATIC", L"卡号:",
        WS_VISIBLE | WS_CHILD,
        50, 70, 60, 20,
        hwnd, NULL, g_hInstance, NULL
    );
    
    HWND hAccountEdit = CreateWindowW(
        L"EDIT", L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        120, 70, 200, 25,
        hwnd, (HMENU)ID_LOGIN_ACCOUNT_EDIT, g_hInstance, NULL
    );
    
    // 创建密码输入标签和编辑框
    HWND hPasswordLabel = CreateWindowW(
        L"STATIC", L"密码:",
        WS_VISIBLE | WS_CHILD,
        50, 110, 60, 20,
        hwnd, NULL, g_hInstance, NULL
    );
    
    HWND hPasswordEdit = CreateWindowW(
        L"EDIT", L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD | ES_AUTOHSCROLL,
        120, 110, 200, 25,
        hwnd, (HMENU)ID_LOGIN_PASSWORD_EDIT, g_hInstance, NULL
    );
    
    // 创建按钮
    HWND hLoginButton = CreateWindowW(
        L"BUTTON", L"登录",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        120, 160, 80, 35,
        hwnd, (HMENU)ID_LOGIN_BUTTON, g_hInstance, NULL
    );
    
    HWND hCancelButton = CreateWindowW(
        L"BUTTON", L"取消",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        220, 160, 80, 35,
        hwnd, (HMENU)ID_LOGIN_CANCEL_BUTTON, g_hInstance, NULL
    );
    
    // 设置字体
    SetControlFont(hwnd, "Microsoft YaHei", 12);
}

/**
 * 创建交易窗口控件
 */
void CreateTransactionWindowControls(HWND hwnd, int transactionType) {
    const char* title = "";
    const char* amountLabel = "金额:";
    const char* toAccountLabel = "";
    
    switch (transactionType) {
        case DEPOSIT:
            title = "存款功能";
            amountLabel = "存款金额:";
            break;
        case WITHDRAW:
            title = "取款功能";
            amountLabel = "取款金额:";
            break;
        case TRANSFER:
            title = "转账功能";
            amountLabel = "转账金额:";
            toAccountLabel = "对方账户:";
            break;
    }
    
    // 创建标题标签
    HWND hTitleLabel = CreateWindowW(
        L"STATIC", L"",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        20, 20, 360, 30,
        hwnd, NULL, g_hInstance, NULL
    );
    SetWindowTextUTF8(hTitleLabel, title);
    
    // 创建金额输入标签和编辑框
    HWND hAmountLabel = CreateWindowW(
        L"STATIC", L"",
        WS_VISIBLE | WS_CHILD,
        50, 70, 80, 20,
        hwnd, NULL, g_hInstance, NULL
    );
    SetWindowTextUTF8(hAmountLabel, amountLabel);
    
    HWND hAmountEdit = CreateWindowW(
        L"EDIT", L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        140, 70, 150, 25,
        hwnd, (HMENU)ID_AMOUNT_EDIT, g_hInstance, NULL
    );
    
    // 如果是转账，创建对方账户输入
    HWND hToAccountLabel = NULL;
    HWND hToAccountEdit = NULL;
    if (transactionType == TRANSFER) {
        hToAccountLabel = CreateWindowW(
            L"STATIC", L"",
            WS_VISIBLE | WS_CHILD,
            50, 110, 80, 20,
            hwnd, NULL, g_hInstance, NULL
        );
        SetWindowTextUTF8(hToAccountLabel, toAccountLabel);
        
        hToAccountEdit = CreateWindowW(
            L"EDIT", L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            140, 110, 150, 25,
            hwnd, (HMENU)ID_TO_ACCOUNT_EDIT, g_hInstance, NULL
        );
    }
    
    // 创建按钮
    HWND hConfirmButton = CreateWindowW(
        L"BUTTON", L"确认",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        100, 160, 80, 35,
        hwnd, (HMENU)ID_CONFIRM_BUTTON, g_hInstance, NULL
    );
    
    HWND hCancelButton = CreateWindowW(
        L"BUTTON", L"取消",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        200, 160, 80, 35,
        hwnd, (HMENU)ID_CANCEL_BUTTON, g_hInstance, NULL
    );
    
    HWND hReceiptButton = CreateWindowW(
        L"BUTTON", L"打印回单",
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
        300, 160, 80, 35,
        hwnd, (HMENU)ID_RECEIPT_BUTTON, g_hInstance, NULL
    );
    
    // 设置字体
    SetControlFont(hwnd, "Microsoft YaHei", 12);
}

/**
 * 清理资源
 */
void CleanupGUI() {
    if (g_hFont) {
        DeleteObject(g_hFont);
        g_hFont = NULL;
    }
    if (g_hTitleFont) {
        DeleteObject(g_hTitleFont);
        g_hTitleFont = NULL;
    }
}
