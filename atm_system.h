#ifndef ATM_SYSTEM_H
#define ATM_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

// 常量定义
#define MAX_ACCOUNTS 100        // 最大账户数量
#define MAX_STATEMENTS 1000     // 最大流水记录数量
#define PASSWORD_LENGTH 6       // 密码长度
#define MAX_ATTEMPTS 3          // 最大尝试次数
#define ENCRYPT_KEY 13          // 加密密钥

// 交易类型枚举
typedef enum {
    DEPOSIT = 1,    // 存款
    WITHDRAW = 2,   // 取款
    TRANSFER = 3,   // 转账
    QUERY = 4       // 查询
} TransactionType;

// 账户结构体
typedef struct {
    char ID[20];        // 卡号
    char name[20];      // 姓名
    int password[6];    // 密码（加密存储）
    double money;       // 账户余额
    int isLocked;       // 是否被锁定
    int wrongAttempts;  // 错误尝试次数
} Account;

// 流水记录结构体
typedef struct {
    char ID[20];        // 流水编号
    char accountID[20];  // 对应账号
    char time[20];      // 交易时间
    int type;           // 交易类型
    double money;        // 交易数额
    char toAccount[20];  // 对方账号
} Statement;

// 全局变量声明
extern Account accounts[MAX_ACCOUNTS];
extern Statement statements[MAX_STATEMENTS];
extern int accountCount;
extern int statementCount;
extern char currentAccount[20];  // 当前登录账户

// 函数声明

// 加密解密函数
void encryptPassword(int* password, int* encrypted);
void decryptPassword(int* encrypted, int* password);

// 文件操作函数
int loadAccounts();
int saveAccounts();
int loadStatements();
int saveStatements();
void generateStatementID(char* id);

// 账户管理函数
int login();
void changePassword();
void lockAccount(char* accountID);
int isAccountLocked(char* accountID);

// 交易功能函数
void deposit();
void withdraw();
void transfer();
void queryAccount();
void printReceipt(int type, double amount, char* toAccount);

// 界面函数
void showMainMenu();
void showLoginMenu();
void showTransactionMenu();
void clearScreen();
void waitForKey();

// 工具函数
int validateAmount(double amount);
int validateAccount(char* accountID);
void getCurrentTime(char* timeStr);
double calculateBalancePrediction(char* accountID);

// 系统初始化函数
void initializeSystem();
void createTestData();

// 密码输入验证函数
int inputPassword(int* password, const char* prompt);
void delayExit(const char* message, int seconds);

#endif
