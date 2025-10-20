#include "atm_system.h"

/**
 * 存款功能
 */
void deposit() {
    double amount;
    char choice;
    
    printf("\n=== 存款功能 ===\n");
    printf("请输入存款金额: ");
    scanf("%lf", &amount);
    
    if (!validateAmount(amount)) {
        printf("存款金额无效！\n");
        pause();
        return;
    }
    
    // 找到当前账户并更新余额
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            accounts[i].money += amount;
            printf("存款成功！当前余额: %.2f\n", accounts[i].money);
            
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
            
            // 询问是否打印回单
            printf("是否打印回单？(y/n): ");
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                printReceipt(DEPOSIT, amount, "");
            }
            break;
        }
    }
    pause();
}

/**
 * 取款功能
 */
void withdraw() {
    double amount;
    char choice;
    
    printf("\n=== 取款功能 ===\n");
    printf("请输入取款金额: ");
    scanf("%lf", &amount);
    
    if (!validateAmount(amount)) {
        printf("取款金额无效！\n");
        pause();
        return;
    }
    
    // 找到当前账户并检查余额
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            if (accounts[i].money < amount) {
                printf("余额不足！当前余额: %.2f\n", accounts[i].money);
                pause();
                return;
            }
            
            accounts[i].money -= amount;
            printf("取款成功！当前余额: %.2f\n", accounts[i].money);
            
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
            
            // 询问是否打印回单
            printf("是否打印回单？(y/n): ");
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                printReceipt(WITHDRAW, amount, "");
            }
            break;
        }
    }
    pause();
}

/**
 * 转账功能
 */
void transfer() {
    char toAccountID[20];
    double amount;
    char choice;
    int toAccountIndex = -1;
    
    printf("\n=== 转账功能 ===\n");
    printf("请输入对方账户: ");
    scanf("%s", toAccountID);
    
    if (!validateAccount(toAccountID)) {
        printf("对方账户不存在！\n");
        pause();
        return;
    }
    
    // 检查不能转给自己
    if (strcmp(toAccountID, currentAccount) == 0) {
        printf("不能转账给自己！\n");
        pause();
        return;
    }
    
    printf("请输入转账金额: ");
    scanf("%lf", &amount);
    
    if (!validateAmount(amount)) {
        printf("转账金额无效！\n");
        pause();
        return;
    }
    
    // 找到对方账户
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
                printf("余额不足！当前余额: %.2f\n", accounts[i].money);
                pause();
                return;
            }
            
            // 执行转账
            accounts[i].money -= amount;
            accounts[toAccountIndex].money += amount;
            
            printf("转账成功！当前余额: %.2f\n", accounts[i].money);
            
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
            
            // 询问是否打印回单
            printf("是否打印回单？(y/n): ");
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                printReceipt(TRANSFER, amount, toAccountID);
            }
            break;
        }
    }
    pause();
}

/**
 * 查询账户信息
 */
void queryAccount() {
    printf("\n=== 账户查询 ===\n");
    
    // 找到当前账户
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            printf("账户信息：\n");
            printf("卡号: %s\n", accounts[i].ID);
            printf("姓名: %s\n", accounts[i].name);
            printf("余额: %.2f\n", accounts[i].money);
            
            // 显示历史记录
            printf("\n最近交易记录：\n");
            printf("流水号\t\t时间\t\t类型\t\t金额\t\t对方账户\n");
            printf("------------------------------------------------------------\n");
            
            int count = 0;
            for (int j = statementCount - 1; j >= 0 && count < 10; j--) {
                if (strcmp(statements[j].accountID, currentAccount) == 0) {
                    printf("%s\t%s\t", statements[j].ID, statements[j].time);
                    
                    switch (statements[j].type) {
                        case DEPOSIT:
                            printf("存款\t\t+%.2f\t\t", statements[j].money);
                            break;
                        case WITHDRAW:
                            printf("取款\t\t-%.2f\t\t", statements[j].money);
                            break;
                        case TRANSFER:
                            printf("转账\t\t-%.2f\t\t%s", statements[j].money, statements[j].toAccount);
                            break;
                    }
                    printf("\n");
                    count++;
                }
            }
            
            // 余额预测分析（选做功能）
            printf("\n余额预测分析：\n");
            double prediction = calculateBalancePrediction(currentAccount);
            printf("基于历史数据的余额预测: %.2f\n", prediction);
            
            break;
        }
    }
    pause();
}

/**
 * 打印回单
 * @param type 交易类型
 * @param amount 交易金额
 * @param toAccount 对方账户
 */
void printReceipt(int type, double amount, char* toAccount) {
    printf("\n========== 交易回单 ==========\n");
    printf("交易时间: ");
    char timeStr[20];
    getCurrentTime(timeStr);
    printf("%s\n", timeStr);
    printf("账户: %s\n", currentAccount);
    
    switch (type) {
        case DEPOSIT:
            printf("交易类型: 存款\n");
            printf("交易金额: +%.2f\n", amount);
            break;
        case WITHDRAW:
            printf("交易类型: 取款\n");
            printf("交易金额: -%.2f\n", amount);
            break;
        case TRANSFER:
            printf("交易类型: 转账\n");
            printf("交易金额: -%.2f\n", amount);
            printf("对方账户: %s\n", toAccount);
            break;
    }
    
    // 显示当前余额
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            printf("当前余额: %.2f\n", accounts[i].money);
            break;
        }
    }
    printf("==============================\n");
}
