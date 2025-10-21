#include "atm_system.h"

/**
 * 验证金额是否有效
 * @param amount 金额
 * @return 有效返回1，无效返回0
 */
int validateAmount(double amount) {
    return amount > 0 && amount <= 100000;  // 限制单笔交易金额
}

/**
 * 验证账户是否存在
 * @param accountID 账户ID
 * @return 存在返回1，不存在返回0
 */
int validateAccount(char* accountID) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, accountID) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * 获取当前时间字符串
 * @param timeStr 用于存储时间的字符串
 */
void getCurrentTime(char* timeStr) {
    time_t now;
    struct tm* timeinfo;
    time(&now);
    timeinfo = localtime(&now);
    strftime(timeStr, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
}

/**
 * 计算余额预测（基于历史数据）
 * @param accountID 账户ID
 * @return 预测的余额
 */
double calculateBalancePrediction(char* accountID) {
    double totalChange = 0;
    int transactionCount = 0;
    
    // 计算最近10笔交易的平均变化
    for (int i = statementCount - 1; i >= 0 && transactionCount < 10; i--) {
        if (strcmp(statements[i].accountID, accountID) == 0) {
            if (statements[i].type == DEPOSIT) {
                totalChange += statements[i].money;
            } else if (statements[i].type == WITHDRAW || statements[i].type == TRANSFER) {
                totalChange -= statements[i].money;
            }
            transactionCount++;
        }
    }
    
    if (transactionCount == 0) {
        // 如果没有历史记录，返回当前余额
        for (int i = 0; i < accountCount; i++) {
            if (strcmp(accounts[i].ID, accountID) == 0) {
                return accounts[i].money;
            }
        }
        return 0;
    }
    
    double averageChange = totalChange / transactionCount;
    
    // 找到当前余额
    double currentBalance = 0;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, accountID) == 0) {
            currentBalance = accounts[i].money;
            break;
        }
    }
    
    // 基于平均变化预测未来余额
    return currentBalance + averageChange;
}

/**
 * 安全的密码输入函数，确保只接受6位数字
 * @param password 用于存储密码的数组
 * @param prompt 提示信息
 * @return 成功返回1，失败返回0
 */
int inputPassword(int* password, const char* prompt) {
    char input[20];  // 用于存储用户输入的字符串
    int len = 0;
    
    printf("%s", prompt);
    fflush(stdout);  // 确保提示信息立即显示
    
    // 清空输入缓冲区
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    // 读取用户输入
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }
    
    // 计算输入长度（不包括换行符）
    len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        len--;
    }
    
    // 检查长度是否为6
    if (len != PASSWORD_LENGTH) {
        printf("密码必须为6位数字！\n");
        return 0;
    }
    
    // 检查是否全为数字
    for (int i = 0; i < len; i++) {
        if (!isdigit(input[i])) {
            printf("密码只能包含数字！\n");
            return 0;
        }
        password[i] = input[i] - '0';
    }
    
    return 1;
}

/**
 * 延时退出函数，显示消息并等待指定时间
 * @param message 要显示的消息
 * @param seconds 延时秒数
 */
void delayExit(const char* message, int seconds) {
    printf("%s\n", message);
    printf("系统将在 %d 秒后继续...\n", seconds);
    
    // 倒计时显示
    for (int i = seconds; i > 0; i--) {
        printf("\r剩余时间: %d 秒", i);
        fflush(stdout);
        Sleep(1000);  // Windows下使用Sleep函数
    }
    printf("\r                    \r");  // 清除倒计时显示
}
