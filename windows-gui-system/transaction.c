#include "atm_system.h"

/**
 * 存款功能（GUI版本）
 * @param amount 存款金额
 * @return 成功返回1，失败返回0
 */
int deposit_gui(double amount) {
    if (!validateAmount(amount)) {
        return 0;  // 金额无效
    }
    
    // 找到当前账户并更新余额
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            accounts[i].money += amount;
            
            // 记录流水
            Statement newStatement;
            generateStatementID(newStatement.ID);
            strcpy(newStatement.accountID, currentAccount);
            getCurrentTime(newStatement.time);
            newStatement.type = DEPOSIT;
            newStatement.money = amount;
            strcpy(newStatement.toAccount, "");
            
            statements[statementCount] = newStatement;
            statementCount++;
            saveStatements();
            saveAccounts();
            
            return 1;  // 存款成功
        }
    }
    
    return 0;  // 未找到账户
}

/**
 * 取款功能（GUI版本）
 * @param amount 取款金额
 * @return 成功返回1，余额不足返回-1，失败返回0
 */
int withdraw_gui(double amount) {
    if (!validateAmount(amount)) {
        return 0;  // 金额无效
    }
    
    // 找到当前账户并检查余额
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            if (accounts[i].money < amount) {
                return -1;  // 余额不足
            }
            
            accounts[i].money -= amount;
            
            // 记录流水
            Statement newStatement;
            generateStatementID(newStatement.ID);
            strcpy(newStatement.accountID, currentAccount);
            getCurrentTime(newStatement.time);
            newStatement.type = WITHDRAW;
            newStatement.money = amount;
            strcpy(newStatement.toAccount, "");
            
            statements[statementCount] = newStatement;
            statementCount++;
            saveStatements();
            saveAccounts();
            
            return 1;  // 取款成功
        }
    }
    
    return 0;  // 未找到账户
}

/**
 * 转账功能（GUI版本）
 * @param toAccountID 对方账户ID
 * @param amount 转账金额
 * @return 成功返回1，余额不足返回-1，账户不存在返回-2，不能转给自己返回-3，失败返回0
 */
int transfer_gui(char* toAccountID, double amount) {
    if (!validateAccount(toAccountID)) {
        return -2;  // 对方账户不存在
    }
    
    // 检查不能转给自己
    if (strcmp(toAccountID, currentAccount) == 0) {
        return -3;  // 不能转账给自己
    }
    
    if (!validateAmount(amount)) {
        return 0;  // 金额无效
    }
    
    // 找到对方账户
    int toAccountIndex = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, toAccountID) == 0) {
            toAccountIndex = i;
            break;
        }
    }
    
    // 找到当前账户并检查余额
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            if (accounts[i].money < amount) {
                return -1;  // 余额不足
            }
            
            // 执行转账
            accounts[i].money -= amount;
            accounts[toAccountIndex].money += amount;
            
            // 记录流水
            Statement newStatement;
            generateStatementID(newStatement.ID);
            strcpy(newStatement.accountID, currentAccount);
            getCurrentTime(newStatement.time);
            newStatement.type = TRANSFER;
            newStatement.money = amount;
            strcpy(newStatement.toAccount, toAccountID);
            
            statements[statementCount] = newStatement;
            statementCount++;
            saveStatements();
            saveAccounts();
            
            return 1;  // 转账成功
        }
    }
    
    return 0;  // 未找到账户
}

/**
 * 查询账户信息（GUI版本）
 * @param name 用于存储姓名的缓冲区
 * @param balance 用于存储余额的指针
 * @param recentTransactions 用于存储最近交易的缓冲区
 * @param maxTransactions 最大交易记录数
 * @return 成功返回1，失败返回0
 */
int queryAccount_gui(char* name, double* balance, Statement* recentTransactions, int maxTransactions) {
    // 找到当前账户
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            strcpy(name, accounts[i].name);
            *balance = accounts[i].money;
            
            // 获取最近交易记录
            int count = 0;
            for (int j = statementCount - 1; j >= 0 && count < maxTransactions; j--) {
                if (strcmp(statements[j].accountID, currentAccount) == 0) {
                    recentTransactions[count] = statements[j];
                    count++;
                }
            }
            
            return 1;
        }
    }
    
    return 0;
}

/**
 * 获取交易类型名称
 * @param type 交易类型
 * @return 交易类型名称
 */
const char* getTransactionTypeName(int type) {
    switch (type) {
        case DEPOSIT:
            return "存款";
        case WITHDRAW:
            return "取款";
        case TRANSFER:
            return "转账";
        default:
            return "未知";
    }
}

/**
 * 生成回单内容
 * @param type 交易类型
 * @param amount 交易金额
 * @param toAccount 对方账户
 * @param receipt 用于存储回单内容的缓冲区
 * @param maxLength 缓冲区最大长度
 * @return 成功返回1，失败返回0
 */
int generateReceipt(int type, double amount, char* toAccount, char* receipt, int maxLength) {
    char timeStr[20];
    getCurrentTime(timeStr);
    
    int len = 0;
    len += snprintf(receipt + len, maxLength - len, "========== 交易回单 ==========\n");
    len += snprintf(receipt + len, maxLength - len, "交易时间: %s\n", timeStr);
    len += snprintf(receipt + len, maxLength - len, "账户: %s\n", currentAccount);
    len += snprintf(receipt + len, maxLength - len, "交易类型: %s\n", getTransactionTypeName(type));
    
    if (type == DEPOSIT) {
        len += snprintf(receipt + len, maxLength - len, "交易金额: +%.2f\n", amount);
    } else if (type == WITHDRAW) {
        len += snprintf(receipt + len, maxLength - len, "交易金额: -%.2f\n", amount);
    } else if (type == TRANSFER) {
        len += snprintf(receipt + len, maxLength - len, "交易金额: -%.2f\n", amount);
        len += snprintf(receipt + len, maxLength - len, "对方账户: %s\n", toAccount);
    }
    
    // 显示当前余额
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            len += snprintf(receipt + len, maxLength - len, "当前余额: %.2f\n", accounts[i].money);
            break;
        }
    }
    
    len += snprintf(receipt + len, maxLength - len, "==============================\n");
    
    return 1;
}
