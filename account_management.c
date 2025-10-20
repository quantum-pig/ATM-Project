#include "atm_system.h"

/**
 * 用户登录功能
 * @return 成功返回1，失败返回0
 */
int login() {
    char inputID[20];
    int inputPassword[6];
    int encryptedPassword[6];
    
    printf("\n=== ATM 登录系统 ===\n");
    printf("请输入卡号: ");
    scanf("%s", inputID);
    
    // 检查账户是否被锁定
    if (isAccountLocked(inputID)) {
        printf("账户已被锁定，请联系银行客服！\n");
        pause();
        return 0;
    }
    
    printf("请输入6位密码: ");
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        inputPassword[i] = getchar();
        if (inputPassword[i] == '\n') {
            i--;
            continue;
        }
        inputPassword[i] -= '0';  // 转换为数字
    }
    
    // 查找账户
    int accountIndex = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, inputID) == 0) {
            accountIndex = i;
            break;
        }
    }
    
    if (accountIndex == -1) {
        printf("账户不存在！\n");
        pause();
        return 0;
    }
    
    // 加密输入的密码进行比较
    encryptPassword(inputPassword, encryptedPassword);
    
    // 验证密码
    int passwordMatch = 1;
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        if (encryptedPassword[i] != accounts[accountIndex].password[i]) {
            passwordMatch = 0;
            break;
        }
    }
    
    if (passwordMatch) {
        strcpy(currentAccount, inputID);
        accounts[accountIndex].wrongAttempts = 0;  // 重置错误次数
        printf("登录成功！欢迎 %s\n", accounts[accountIndex].name);
        pause();
        return 1;
    } else {
        accounts[accountIndex].wrongAttempts++;
        printf("密码错误！剩余尝试次数: %d\n", MAX_ATTEMPTS - accounts[accountIndex].wrongAttempts);
        
        if (accounts[accountIndex].wrongAttempts >= MAX_ATTEMPTS) {
            lockAccount(inputID);
            printf("连续输入错误3次，账户已被锁定！\n");
        }
        pause();
        return 0;
    }
}

/**
 * 修改密码功能
 */
void changePassword() {
    int newPassword[6];
    int encryptedNewPassword[6];
    int confirmPassword[6];
    
    printf("\n=== 修改密码 ===\n");
    printf("请输入新密码（6位数字）: ");
    
    // 输入新密码
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        newPassword[i] = getchar();
        if (newPassword[i] == '\n') {
            i--;
            continue;
        }
        newPassword[i] -= '0';
    }
    
    printf("请再次输入新密码确认: ");
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        confirmPassword[i] = getchar();
        if (confirmPassword[i] == '\n') {
            i--;
            continue;
        }
        confirmPassword[i] -= '0';
    }
    
    // 验证两次输入的密码是否一致
    int passwordMatch = 1;
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        if (newPassword[i] != confirmPassword[i]) {
            passwordMatch = 0;
            break;
        }
    }
    
    if (!passwordMatch) {
        printf("两次输入的密码不一致，修改失败！\n");
        pause();
        return;
    }
    
    // 找到当前账户并更新密码
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            encryptPassword(newPassword, encryptedNewPassword);
            for (int j = 0; j < PASSWORD_LENGTH; j++) {
                accounts[i].password[j] = encryptedNewPassword[j];
            }
            printf("密码修改成功！\n");
            saveAccounts();
            pause();
            return;
        }
    }
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
