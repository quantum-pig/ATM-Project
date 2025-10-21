#include "gui_common.h"

// 全局变量定义
Account accounts[MAX_ACCOUNTS];
Statement statements[MAX_STATEMENTS];
int accountCount = 0;
int statementCount = 0;
char currentAccount[20] = "";

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
    // 创建测试账户数据
    char testNames[][20] = {
        "张三", "李四", "王五", "赵六", "钱七", "孙八", "周九", "吴十",
        "郑十一", "王十二", "冯十三", "陈十四", "褚十五", "卫十六", "蒋十七", "沈十八",
        "韩十九", "杨二十", "朱二一", "秦二二", "尤二三", "许二四", "何二五", "吕二六"
    };
    
    char testIDs[][20] = {
        "622202000001", "622202000002", "622202000003", "622202000004", "622202000005",
        "622202000006", "622202000007", "622202000008", "622202000009", "622202000010",
        "622202000011", "622202000012", "622202000013", "622202000014", "622202000015",
        "622202000016", "622202000017", "622202000018", "622202000019", "622202000020",
        "622202000021", "622202000022", "622202000023", "622202000024", "622202000025"
    };
    
    // 创建25个测试账户
    for (int i = 0; i < 25; i++) {
        strcpy(accounts[i].ID, testIDs[i]);
        strcpy(accounts[i].name, testNames[i]);
        
        // 设置默认密码为123456
        int defaultPassword[6] = {1, 2, 3, 4, 5, 6};
        encryptPassword(defaultPassword, accounts[i].password);
        
        // 设置随机余额
        accounts[i].money = 1000 + (rand() % 50000);
        accounts[i].isLocked = 0;
        accounts[i].wrongAttempts = 0;
    }
    
    accountCount = 25;
    saveAccounts();
    
    // 创建一些测试流水记录
    for (int i = 0; i < 50; i++) {
        Statement testStatement;
        generateStatementID(testStatement.ID);
        strcpy(testStatement.accountID, testIDs[rand() % 25]);
        getCurrentTime(testStatement.time);
        testStatement.type = (rand() % 3) + 1;  // 1-3 对应存款、取款、转账
        testStatement.money = 100 + (rand() % 5000);
        if (testStatement.type == TRANSFER) {
            strcpy(testStatement.toAccount, testIDs[rand() % 25]);
        } else {
            strcpy(testStatement.toAccount, "");
        }
        
        statements[i] = testStatement;
    }
    
    statementCount = 50;
    saveStatements();
}

/**
 * GUI版本主程序入口
 */
int main(int argc, char *argv[]) {
    // 初始化随机数种子
    srand(time(NULL));
    
    // 初始化GUI系统
    gui_init();
    
    // 初始化ATM系统数据
    initializeSystem();
    
    // 显示主窗口
    show_main_window();
    
    // 启动GTK主循环
    gtk_main();
    
    // 清理资源
    gui_cleanup();
    
    return 0;
}

