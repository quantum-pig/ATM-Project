#include "gui_common.h"

// 登录界面控件
GtkWidget *login_container;
GtkWidget *card_entry;
GtkWidget *password_entry;
GtkWidget *login_confirm_button;
GtkWidget *back_button;
GtkWidget *status_label;

/**
 * 创建登录窗口
 */
void create_login_window() {
    // 创建登录窗口
    login_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(login_window), "ATM登录");
    gtk_window_set_default_size(GTK_WINDOW(login_window), LOGIN_WIDTH, LOGIN_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(login_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(login_window), FALSE);
    gtk_window_set_modal(GTK_WINDOW(login_window), TRUE);
    
    // 创建主容器
    login_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(login_window), login_container);
    
    // 应用样式
    GtkStyleContext *context = gtk_widget_get_style_context(login_container);
    gtk_style_context_add_class(context, "main-container");
    
    // 创建标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "ATM登录", "title");
    gtk_box_pack_start(GTK_BOX(login_container), title_label, FALSE, FALSE, 0);
    
    // 创建卡片容器
    GtkWidget *card_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *card_context = gtk_widget_get_style_context(card_container);
    gtk_style_context_add_class(card_context, "card");
    gtk_box_pack_start(GTK_BOX(login_container), card_container, TRUE, TRUE, 0);
    
    // 创建卡号输入区域
    GtkWidget *card_label;
    create_modern_label(&card_label, "请输入银行卡号：", NULL);
    gtk_box_pack_start(GTK_BOX(card_container), card_label, FALSE, FALSE, 0);
    
    create_modern_entry(&card_entry, "例如：622202000001");
    gtk_box_pack_start(GTK_BOX(card_container), card_entry, FALSE, FALSE, 0);
    
    // 创建密码输入区域
    GtkWidget *password_label;
    create_modern_label(&password_label, "请输入6位密码：", NULL);
    gtk_box_pack_start(GTK_BOX(card_container), password_label, FALSE, FALSE, 0);
    
    create_modern_entry(&password_entry, "请输入6位数字密码");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE); // 隐藏密码
    gtk_box_pack_start(GTK_BOX(card_container), password_entry, FALSE, FALSE, 0);
    
    // 创建状态标签
    create_modern_label(&status_label, "", NULL);
    GtkStyleContext *status_context = gtk_widget_get_style_context(status_label);
    gtk_style_context_add_class(status_context, "info-text");
    gtk_box_pack_start(GTK_BOX(card_container), status_label, FALSE, FALSE, 0);
    
    // 创建按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(card_container), button_container, TRUE, TRUE, 0);
    
    // 创建登录按钮
    create_modern_button(&login_confirm_button, "登录", "success");
    gtk_box_pack_start(GTK_BOX(button_container), login_confirm_button, TRUE, TRUE, 0);
    
    // 创建返回按钮
    create_modern_button(&back_button, "返回", NULL);
    gtk_box_pack_start(GTK_BOX(button_container), back_button, TRUE, TRUE, 0);
    
    // 创建帮助信息
    GtkWidget *help_label;
    create_modern_label(&help_label, "测试账户：622202000001-622202000025\n默认密码：123456", NULL);
    GtkStyleContext *help_context = gtk_widget_get_style_context(help_label);
    gtk_style_context_add_class(help_context, "info-text");
    gtk_box_pack_start(GTK_BOX(login_container), help_label, FALSE, FALSE, 0);
    
    // 连接信号
    g_signal_connect(login_confirm_button, "clicked", G_CALLBACK(on_login_confirm_clicked), NULL);
    g_signal_connect(back_button, "clicked", G_CALLBACK(on_login_back_clicked), NULL);
    g_signal_connect(login_window, "destroy", G_CALLBACK(on_login_window_destroy), NULL);
    g_signal_connect(password_entry, "activate", G_CALLBACK(on_login_confirm_clicked), NULL);
    
    current_window = login_window;
}

/**
 * 登录确认按钮点击事件
 */
void on_login_confirm_clicked(GtkWidget *widget, gpointer data) {
    const char *card_text = gtk_entry_get_text(GTK_ENTRY(card_entry));
    const char *password_text = gtk_entry_get_text(GTK_ENTRY(password_entry));
    
    // 验证输入
    if (strlen(card_text) == 0) {
        gtk_label_set_text(GTK_LABEL(status_label), "请输入银行卡号！");
        gtk_widget_grab_focus(card_entry);
        return;
    }
    
    if (strlen(password_text) == 0) {
        gtk_label_set_text(GTK_LABEL(status_label), "请输入密码！");
        gtk_widget_grab_focus(password_entry);
        return;
    }
    
    // 验证密码格式
    if (strlen(password_text) != 6) {
        gtk_label_set_text(GTK_LABEL(status_label), "密码必须为6位数字！");
        gtk_widget_grab_focus(password_entry);
        return;
    }
    
    // 检查是否全为数字
    for (int i = 0; i < 6; i++) {
        if (!isdigit(password_text[i])) {
            gtk_label_set_text(GTK_LABEL(status_label), "密码必须为6位数字！");
            gtk_widget_grab_focus(password_entry);
            return;
        }
    }
    
    // 尝试登录
    gtk_label_set_text(GTK_LABEL(status_label), "正在验证登录信息...");
    gtk_widget_set_sensitive(login_confirm_button, FALSE);
    
    // 模拟登录验证（这里需要集成原有的登录逻辑）
    if (verify_login(card_text, password_text)) {
        // 登录成功
        gtk_widget_hide(login_window);
        create_transaction_window();
        gtk_widget_show_all(transaction_window);
        show_success_dialog("登录成功！欢迎使用ATM系统！");
    } else {
        // 登录失败
        gtk_label_set_text(GTK_LABEL(status_label), "卡号或密码错误，请重新输入！");
        gtk_widget_grab_focus(password_entry);
        gtk_entry_set_text(GTK_ENTRY(password_entry), "");
    }
    
    gtk_widget_set_sensitive(login_confirm_button, TRUE);
}

/**
 * 返回按钮点击事件
 */
void on_login_back_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(login_window);
    gtk_widget_show_all(main_window);
    current_window = main_window;
}

/**
 * 登录窗口销毁事件
 */
void on_login_window_destroy(GtkWidget *widget, gpointer data) {
    gtk_widget_show_all(main_window);
    current_window = main_window;
}

/**
 * 验证登录信息
 */
int verify_login(const char *card_id, const char *password) {
    // 查找账户
    int account_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, card_id) == 0) {
            account_index = i;
            break;
        }
    }
    
    if (account_index == -1) {
        return 0; // 账户不存在
    }
    
    // 检查账户是否被锁定
    if (accounts[account_index].isLocked) {
        gtk_label_set_text(GTK_LABEL(status_label), "账户已被锁定，请联系银行！");
        return 0;
    }
    
    // 验证密码
    int input_password[6];
    for (int i = 0; i < 6; i++) {
        input_password[i] = password[i] - '0';
    }
    
    int decrypted_password[6];
    decryptPassword(accounts[account_index].password, decrypted_password);
    
    for (int i = 0; i < 6; i++) {
        if (input_password[i] != decrypted_password[i]) {
            // 密码错误，增加错误次数
            accounts[account_index].wrongAttempts++;
            if (accounts[account_index].wrongAttempts >= MAX_ATTEMPTS) {
                lockAccount(accounts[account_index].ID);
                gtk_label_set_text(GTK_LABEL(status_label), "密码错误次数过多，账户已被锁定！");
            }
            return 0;
        }
    }
    
    // 登录成功，重置错误次数
    accounts[account_index].wrongAttempts = 0;
    strcpy(currentAccount, card_id);
    saveAccounts();
    
    return 1;
}
