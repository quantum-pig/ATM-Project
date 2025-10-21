#include "atm_system.h"

/**
 * 从文件加载账户信息
 * @return 成功返回1，失败返回0
 */
int loadAccounts() {
    FILE* file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("账户文件不存在，将创建新文件\n");
        return 0;
    }
    
    accountCount = 0;
    while (fread(&accounts[accountCount], sizeof(Account), 1, file) == 1) {
        accountCount++;
        if (accountCount >= MAX_ACCOUNTS) break;
    }
    
    fclose(file);
    printf("成功加载 %d 个账户信息\n", accountCount);
    return 1;
}

/**
 * 保存账户信息到文件
 * @return 成功返回1，失败返回0
 */
int saveAccounts() {
    FILE* file = fopen("accounts.dat", "wb");
    if (file == NULL) {
        printf("无法创建账户文件\n");
        return 0;
    }
    
    for (int i = 0; i < accountCount; i++) {
        fwrite(&accounts[i], sizeof(Account), 1, file);
    }
    
    fclose(file);
    return 1;
}

/**
 * 从文件加载流水记录
 * @return 成功返回1，失败返回0
 */
int loadStatements() {
    FILE* file = fopen("statements.dat", "rb");
    if (file == NULL) {
        printf("流水文件不存在，将创建新文件\n");
        return 0;
    }
    
    statementCount = 0;
    while (fread(&statements[statementCount], sizeof(Statement), 1, file) == 1) {
        statementCount++;
        if (statementCount >= MAX_STATEMENTS) break;
    }
    
    fclose(file);
    printf("成功加载 %d 条流水记录\n", statementCount);
    return 1;
}

/**
 * 保存流水记录到文件
 * @return 成功返回1，失败返回0
 */
int saveStatements() {
    FILE* file = fopen("statements.dat", "wb");
    if (file == NULL) {
        printf("无法创建流水文件\n");
        return 0;
    }
    
    for (int i = 0; i < statementCount; i++) {
        fwrite(&statements[i], sizeof(Statement), 1, file);
    }
    
    fclose(file);
    return 1;
}

/**
 * 生成流水记录编号
 * @param id 用于存储生成的ID
 */
void generateStatementID(char* id) {
    sprintf(id, "ST%06d", statementCount + 1);
}
