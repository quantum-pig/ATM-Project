#include "win_gui.h"
#include "atm_system.h"

// 全局变量
HWND hMainWindow = NULL;

/**
 * 创建主窗口
 */
BOOL createMainWindow(HINSTANCE hInstance) {
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "ATMMainWindow";
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(1));
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(1));

    if (!RegisterClassEx(&wc)) {
        return FALSE;
    }

    hMainWindow = CreateWindowEx(
        0,
        "ATMMainWindow",
        "ATM仿真系统",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT,
        500, 400,
        NULL, NULL, hInstance, NULL
    );

    if (!hMainWindow) {
        return FALSE;
    }

    setWindowIcon(hMainWindow, hInstance);
    centerWindow(hMainWindow);
    return TRUE;
}

/**
 * 主窗口过程
 */
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // 创建标题
            createLabel(hwnd, ID_MAIN_TITLE, "欢迎使用ATM仿真系统", 50, 30, 400, 40);
            
            // 创建登录按钮
            createButton(hwnd, ID_MAIN_LOGIN_BUTTON, "登录系统", 150, 120, 200, 50);
            
            // 创建退出按钮
            createButton(hwnd, ID_MAIN_EXIT_BUTTON, "退出系统", 150, 200, 200, 50);
            
            // 创建状态栏
            HWND hStatusBar = CreateWindowEx(0, STATUSCLASSNAME, NULL,
                WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
                0, 0, 0, 0, hwnd, NULL, GetModuleHandle(NULL), NULL);
            
            // 设置状态栏文本
            SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)"准备就绪");
            break;
        }
        
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case ID_MAIN_LOGIN_BUTTON:
                    if (createLoginWindow(GetModuleHandle(NULL))) {
                        ShowWindow(hLoginWindow, SW_SHOW);
                        EnableWindow(hwnd, FALSE);
                    }
                    break;
                    
                case ID_MAIN_EXIT_BUTTON:
                    if (showConfirmDialog("确定要退出ATM系统吗？")) {
                        PostQuitMessage(0);
                    }
                    break;
            }
            break;
        }
        
        case WM_CLOSE:
            if (showConfirmDialog("确定要退出ATM系统吗？")) {
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
 * 创建按钮
 */
void createButton(HWND parent, int id, const char* text, int x, int y, int width, int height) {
    CreateWindowEx(
        0, "BUTTON", text,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        x, y, width, height,
        parent, (HMENU)id, GetModuleHandle(NULL), NULL
    );
}

/**
 * 创建标签
 */
void createLabel(HWND parent, int id, const char* text, int x, int y, int width, int height) {
    CreateWindowEx(
        0, "STATIC", text,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        x, y, width, height,
        parent, (HMENU)id, GetModuleHandle(NULL), NULL
    );
}

/**
 * 创建编辑框
 */
void createEdit(HWND parent, int id, int x, int y, int width, int height, BOOL password) {
    DWORD style = WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL;
    if (password) {
        style |= ES_PASSWORD;
    }
    
    CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT", "",
        style,
        x, y, width, height,
        parent, (HMENU)id, GetModuleHandle(NULL), NULL
    );
}

/**
 * 设置窗口图标
 */
void setWindowIcon(HWND hwnd, HINSTANCE hInstance) {
    HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(1));
    if (hIcon) {
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }
}

/**
 * 居中显示窗口
 */
void centerWindow(HWND hwnd) {
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
