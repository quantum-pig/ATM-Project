#include "atm_system.h"

/**
 * 显示主菜单
 */
void showMainMenu() {
    clearScreen();
    printf("========================================\n");
    printf("          欢迎使用ATM仿真系统\n");
    printf("========================================\n");
    printf("1. 登录系统\n");
    printf("2. 退出系统\n");
    printf("========================================\n");
    printf("请选择操作: ");
}

/**
 * 显示登录菜单
 */
void showLoginMenu() {
    clearScreen();
    printf("========================================\n");
    printf("              ATM登录界面\n");
    printf("========================================\n");
}

/**
 * 显示交易菜单
 */
void showTransactionMenu() {
    clearScreen();
    printf("========================================\n");
    printf("              ATM主功能\n");
    printf("========================================\n");
    printf("1. 存款\n");
    printf("2. 取款\n");
    printf("3. 转账\n");
    printf("4. 查询账户\n");
    printf("5. 修改密码\n");
    printf("6. 退出登录\n");
    printf("========================================\n");
    printf("请选择操作: ");
}

/**
 * 清屏函数
 */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * 等待按键函数
 */
void waitForKey() {
    printf("\n按任意键继续...");
    getchar();
    getchar();
}
