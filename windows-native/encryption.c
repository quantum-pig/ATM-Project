#include "atm_system.h"

/**
 * 密码加密函数
 * @param password 原始密码数组
 * @param encrypted 加密后的密码数组
 */
void encryptPassword(int* password, int* encrypted) {
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        encrypted[i] = (password[i] + ENCRYPT_KEY) % 10;
    }
}

/**
 * 密码解密函数
 * @param encrypted 加密的密码数组
 * @param password 解密后的密码数组
 */
void decryptPassword(int* encrypted, int* password) {
    for (int i = 0; i < PASSWORD_LENGTH; i++) {
        password[i] = (encrypted[i] - ENCRYPT_KEY + 10) % 10;
    }
}
