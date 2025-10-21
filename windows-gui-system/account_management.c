#include "atm_system.h"

/**
 * 用户登录功能（GUI版本）
 * @param accountID 输入的账户ID
 * @param password 输入的密码数组
 * @return 成功返回1，失败返回0
 */
int login_gui(char* accountID, int* password) {
    int encryptedPassword[6];
    
    // 检查账户是否被锁定
    if (isAccountLocked(accountID)) {
        return 0;  // 账户被锁定
    }
    
    // 查找账户
    int accountIndex = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, accountID) == 0) {
            accountIndex = i;
            break;
        }
    }
    
    if (accountIndex == -1) {
        return 0;  // 账户不存在
    }
    
    // 加密输入的密码进行比较
    encryptPassword(password, encryptedPassword);
    
    // 验证密码
    int passwordMatch = 1;
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        if (encryptedPassword[i] != accounts[accountIndex].password[i]) {
            passwordMatch = 0;
            break;
        }
    }
    
    if (passwordMatch) {
        strcpy(currentAccount, accountID);
        accounts[accountIndex].wrongAttempts = 0;  // 重置错误次数
        return 1;  // 登录成功
    } else {
        accounts[accountIndex].wrongAttempts++;
        
        if (accounts[accountIndex].wrongAttempts >= MAX_ATTEMPTS) {
            lockAccount(accountID);
        }
        return 0;  // 密码错误
    }
}

/**
 * 修改密码功能（GUI版本）
 * @param newPassword 新密码数组
 * @param confirmPassword 确认密码数组
 * @return 成功返回1，失败返回0
 */
int changePassword_gui(int* newPassword, int* confirmPassword) {
    // 验证两次输入的密码是否一致
    int passwordMatch = 1;
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        if (newPassword[i] != confirmPassword[i]) {
            passwordMatch = 0;
            break;
        }
    }
    
    if (!passwordMatch) {
        return 0;  // 两次密码不一致
    }
    
    // 找到当前账户并更新密码
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            int encryptedNewPassword[6];
            encryptPassword(newPassword, encryptedNewPassword);
            for (int j = 0; j < PASSWORD_LENGTH; j++) {
                accounts[i].password[j] = encryptedNewPassword[j];
            }
            saveAccounts();
            return 1;  // 修改成功
        }
    }
    
    return 0;  // 未找到账户
}

/**
 * 锁定账户
 * @param accountID 要锁定的账户ID
 */
void lockAccount(char* accountID) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, accountID) == 0) {
            accounts[i].isLocked = 1;
            saveAccounts();
            break;
        }
    }
}

/**
 * 检查账户是否被锁定
 * @param accountID 账户ID
 * @return 锁定返回1，未锁定返回0
 */
int isAccountLocked(char* accountID) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, accountID) == 0) {
            return accounts[i].isLocked;
        }
    }
    return 0;
}

/**
 * 获取当前账户信息
 * @param name 用于存储姓名的缓冲区
 * @param balance 用于存储余额的指针
 * @return 成功返回1，失败返回0
 */
int getCurrentAccountInfo(char* name, double* balance) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            strcpy(name, accounts[i].name);
            *balance = accounts[i].money;
            return 1;
        }
    }
    return 0;
}

/**
 * 获取账户错误尝试次数
 * @param accountID 账户ID
 * @return 错误尝试次数
 */
int getAccountWrongAttempts(char* accountID) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, accountID) == 0) {
            return accounts[i].wrongAttempts;
        }
    }
    return 0;
}
