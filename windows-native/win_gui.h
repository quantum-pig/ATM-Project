#ifndef WIN_GUI_H
#define WIN_GUI_H

#include <windows.h>
#include <commctrl.h>

// 控件ID定义
#define ID_MAIN_LOGIN_BUTTON     1001
#define ID_MAIN_EXIT_BUTTON      1002
#define ID_MAIN_TITLE            1003

#define ID_LOGIN_CARD_EDIT       2001
#define ID_LOGIN_PASSWORD_EDIT   2002
#define ID_LOGIN_CONFIRM_BUTTON  2003
#define ID_LOGIN_BACK_BUTTON     2004
#define ID_LOGIN_STATUS_LABEL    2005

#define ID_TRANS_DEPOSIT_BUTTON  3001
#define ID_TRANS_WITHDRAW_BUTTON 3002
#define ID_TRANS_TRANSFER_BUTTON 3003
#define ID_TRANS_QUERY_BUTTON    3004
#define ID_TRANS_PASSWORD_BUTTON 3005
#define ID_TRANS_LOGOUT_BUTTON   3006
#define ID_TRANS_USER_INFO       3007
#define ID_TRANS_BALANCE_LABEL   3008

#define ID_DEPOSIT_AMOUNT_EDIT   4001
#define ID_DEPOSIT_CONFIRM_BUTTON 4002
#define ID_DEPOSIT_CANCEL_BUTTON 4003
#define ID_DEPOSIT_QUICK_100     4004
#define ID_DEPOSIT_QUICK_500     4005
#define ID_DEPOSIT_QUICK_1000    4006
#define ID_DEPOSIT_QUICK_2000    4007

#define ID_WITHDRAW_AMOUNT_EDIT  5001
#define ID_WITHDRAW_CONFIRM_BUTTON 5002
#define ID_WITHDRAW_CANCEL_BUTTON 5003
#define ID_WITHDRAW_QUICK_100    5004
#define ID_WITHDRAW_QUICK_500    5005
#define ID_WITHDRAW_QUICK_1000   5006
#define ID_WITHDRAW_QUICK_2000   5007

#define ID_TRANSFER_TO_EDIT      6001
#define ID_TRANSFER_AMOUNT_EDIT  6002
#define ID_TRANSFER_CONFIRM_BUTTON 6003
#define ID_TRANSFER_CANCEL_BUTTON 6004

#define ID_QUERY_CLOSE_BUTTON    7001
#define ID_QUERY_TEXT            7002

#define ID_PASSWORD_OLD_EDIT     8001
#define ID_PASSWORD_NEW_EDIT     8002
#define ID_PASSWORD_CONFIRM_EDIT 8003
#define ID_PASSWORD_CONFIRM_BUTTON 8004
#define ID_PASSWORD_CANCEL_BUTTON 8005

// 窗口句柄
extern HWND hMainWindow;
extern HWND hLoginWindow;
extern HWND hTransactionWindow;

// 函数声明
// 主窗口
BOOL createMainWindow(HINSTANCE hInstance);
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 登录窗口
BOOL createLoginWindow(HINSTANCE hInstance);
LRESULT CALLBACK LoginWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void onLoginConfirm();
void onLoginBack();

// 交易窗口
BOOL createTransactionWindow(HINSTANCE hInstance);
LRESULT CALLBACK TransactionWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void onDeposit();
void onWithdraw();
void onTransfer();
void onQuery();
void onChangePassword();
void onLogout();

// 存款窗口
BOOL createDepositWindow(HINSTANCE hInstance);
LRESULT CALLBACK DepositWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void onDepositConfirm();
void onDepositCancel();
void onQuickAmount(int amount);

// 取款窗口
BOOL createWithdrawWindow(HINSTANCE hInstance);
LRESULT CALLBACK WithdrawWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void onWithdrawConfirm();
void onWithdrawCancel();
void onWithdrawQuickAmount(int amount);

// 转账窗口
BOOL createTransferWindow(HINSTANCE hInstance);
LRESULT CALLBACK TransferWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void onTransferConfirm();
void onTransferCancel();

// 查询窗口
BOOL createQueryWindow(HINSTANCE hInstance);
LRESULT CALLBACK QueryWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void onQueryClose();

// 修改密码窗口
BOOL createPasswordWindow(HINSTANCE hInstance);
LRESULT CALLBACK PasswordWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void onPasswordConfirm();
void onPasswordCancel();

// 工具函数
void createButton(HWND parent, int id, const char* text, int x, int y, int width, int height);
void createLabel(HWND parent, int id, const char* text, int x, int y, int width, int height);
void createEdit(HWND parent, int id, int x, int y, int width, int height, BOOL password);
void setWindowIcon(HWND hwnd, HINSTANCE hInstance);
void centerWindow(HWND hwnd);
void updateUserInfo();
int verifyLogin(const char* card_id, const char* password);
int performDeposit(double amount);
int performWithdraw(double amount);
int performTransfer(const char* to_account, double amount);
int performChangePassword(const char* new_password);

// 消息框函数
void showErrorMessage(const char* message);
void showSuccessMessage(const char* message);
void showInfoMessage(const char* message);
int showConfirmDialog(const char* message);

#endif // WIN_GUI_H
