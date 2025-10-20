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
