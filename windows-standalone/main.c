#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "atm_system.h"
#include "gui_common.h"

// 全局变量定义
Account accounts[MAX_ACCOUNTS];
Statement statements[MAX_STATEMENTS];
int accountCount = 0;
int statementCount = 0;
char currentAccount[20] = "";

// GUI窗口变量
GtkWidget *main_window = NULL;
GtkWidget *login_window = NULL;
GtkWidget *transaction_window = NULL;

/**
 * 初始化系统数据
 */
void initializeSystem() {
    // 加载账户数据
    if (!loadAccounts()) {
        createTestData();
    }

    // 加载流水数据
    loadStatements();
}

/**
 * 创建测试数据
 */
void createTestData() {
    // 创建25个测试账户
    for (int i = 0; i < 25; i++) {
        snprintf(accounts[i].ID, sizeof(accounts[i].ID), "622202000%03d", i + 1);
        snprintf(accounts[i].name, sizeof(accounts[i].name), "用户%d", i + 1);
        accounts[i].money = 10000.0 + i * 1000.0; // 不同余额
        accounts[i].isLocked = 0;
        
        // 设置默认密码123456
        int defaultPassword[6] = {1, 2, 3, 4, 5, 6};
        encryptPassword(defaultPassword, accounts[i].password);
    }
    
    accountCount = 25;
    saveAccounts();
}

/**
 * 初始化GUI系统
 */
void gui_init() {
    // 设置CSS样式
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "window { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); }"
        ".main-container { padding: 20px; }"
        ".card { background: rgba(255, 255, 255, 0.95); border-radius: 10px; padding: 20px; margin: 10px; box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1); }"
        ".title { font-size: 24px; font-weight: bold; color: #2c3e50; margin-bottom: 20px; }"
        ".button { background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); color: white; border: none; border-radius: 5px; padding: 10px 20px; font-size: 14px; font-weight: bold; }"
        ".button:hover { background: linear-gradient(135deg, #5a6fd8 0%, #6a4190 100%); }"
        ".success-button { background: linear-gradient(135deg, #4CAF50 0%, #45a049 100%); }"
        ".warning-button { background: linear-gradient(135deg, #ff9800 0%, #f57c00 100%); }"
        ".entry { border: 2px solid #ddd; border-radius: 5px; padding: 10px; font-size: 14px; }"
        ".entry:focus { border-color: #667eea; }"
        ".info-text { color: #666; font-size: 12px; }", -1, NULL);
    
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

/**
 * Windows版本主程序入口
 */
int main(int argc, char *argv[]) {
    // 初始化随机数种子
    srand(time(NULL));

    // 初始化GTK
    gtk_init(&argc, &argv);

    // 初始化GUI系统
    gui_init();
    
    // 初始化系统数据
    initializeSystem();
    
    // 显示主窗口
    show_main_window();
    
    // 运行GTK主循环
    gtk_main();

    return 0;
}
