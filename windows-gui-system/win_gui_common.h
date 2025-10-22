#ifndef WIN_GUI_COMMON_H
#define WIN_GUI_COMMON_H

#include <windows.h>
#include <commctrl.h>
#include "atm_system.h"

// 窗口ID定义
#define ID_MAIN_WINDOW 1000
#define ID_LOGIN_WINDOW 1001
#define ID_TRANSACTION_WINDOW 1002

// 控件ID定义
// 登录窗口控件
#define ID_LOGIN_ACCOUNT_EDIT 2001
#define ID_LOGIN_PASSWORD_EDIT 2002
#define ID_LOGIN_BUTTON 2003
#define ID_LOGIN_CANCEL_BUTTON 2004

// 主窗口控件
#define ID_DEPOSIT_BUTTON 3001
#define ID_WITHDRAW_BUTTON 3002
#define ID_TRANSFER_BUTTON 3003
#define ID_QUERY_BUTTON 3004
#define ID_CHANGE_PASSWORD_BUTTON 3005
#define ID_LOGOUT_BUTTON 3006
#define ID_BALANCE_LABEL 3007
#define ID_CARD_NUMBER_LABEL 3008

// 修改密码窗口控件
#define ID_OLD_PASSWORD_EDIT 5001
#define ID_NEW_PASSWORD_EDIT 5002
#define ID_CONFIRM_PASSWORD_EDIT 5003
#define ID_CHANGE_PASSWORD_CONFIRM_BUTTON 5004
#define ID_CHANGE_PASSWORD_CANCEL_BUTTON 5005

// 交易窗口控件
#define ID_AMOUNT_EDIT 4001
#define ID_TO_ACCOUNT_EDIT 4002
#define ID_CONFIRM_BUTTON 4003
#define ID_CANCEL_BUTTON 4004
#define ID_RECEIPT_BUTTON 4005
#define ID_TRANSACTION_TYPE_LABEL 4006

// 消息定义
#define WM_USER_LOGIN_SUCCESS (WM_USER + 1)
#define WM_USER_LOGIN_FAILED (WM_USER + 2)
#define WM_USER_TRANSACTION_SUCCESS (WM_USER + 3)
#define WM_USER_TRANSACTION_FAILED (WM_USER + 4)

// 全局变量声明
extern HWND g_hMainWindow;
extern HWND g_hLoginWindow;
extern HWND g_hTransactionWindow;
extern HWND g_hChangePasswordWindow;
extern HINSTANCE g_hInstance;

// 函数声明
// 窗口过程
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK TransactionWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChangePasswordWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 窗口创建函数
HWND CreateMainWindow(HINSTANCE hInstance);
HWND CreateLoginWindow(HINSTANCE hInstance);
HWND CreateTransactionWindow(HINSTANCE hInstance, int transactionType);
HWND CreateChangePasswordWindow(HINSTANCE hInstance);

// 控件创建函数
void CreateMainWindowControls(HWND hwnd);
void CreateLoginWindowControls(HWND hwnd);
void CreateTransactionWindowControls(HWND hwnd, int transactionType);
void CreateChangePasswordWindowControls(HWND hwnd);

// 消息处理函数
void HandleLoginButtonClick(HWND hwnd);
void HandleTransactionButtonClick(HWND hwnd, int transactionType);
void HandleConfirmButtonClick(HWND hwnd);
void HandleLogoutButtonClick(HWND hwnd);

// 工具函数
void ShowMessageBox(HWND hwnd, const char* title, const char* message, UINT type);
void SetWindowTextUTF8(HWND hwnd, const char* text);
void GetWindowTextUTF8(HWND hwnd, char* buffer, int bufferSize);
void CenterWindow(HWND hwnd);
void SetWindowIcon(HWND hwnd, int iconId);

// 样式和主题
void ApplyModernStyle(HWND hwnd);
void SetControlFont(HWND hwnd, const char* fontName, int fontSize);

// 清理函数
void CleanupGUI();

// 主窗口函数
void UpdateBalanceDisplay(HWND hwnd);
void ShowTransactionWindowMain(int transactionType);
void ShowQueryWindow();
void ShowChangePasswordWindow();
void HandleLogout();
void ShowMainWindow();
void HideMainWindow();

// 登录窗口函数
void ShowLoginWindow();
void HideLoginWindow();

// 交易窗口函数
void ShowTransactionWindow(int transactionType);
void HideTransactionWindow();
void HandleConfirmButtonClick(HWND hwnd);
void HandleReceiptButtonClick(HWND hwnd);
void HandleChangePasswordConfirmButtonClick(HWND hwnd);

// 主程序函数
void HandleLoginSuccess();
void HandleLoginFailed(const char* errorMessage);
void HandleTransactionSuccess();
void HandleTransactionFailed(const char* errorMessage);
void HandleLogoutMain();
void HandleExit();

#endif
