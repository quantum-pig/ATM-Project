#include "gui_common.h"

// 交易界面控件
GtkWidget *transaction_container;
GtkWidget *user_info_label;
GtkWidget *balance_label;
GtkWidget *deposit_button;
GtkWidget *withdraw_button;
GtkWidget *transfer_button;
GtkWidget *query_button;
GtkWidget *change_password_button;
GtkWidget *logout_button;

// 存款界面控件
GtkWidget *deposit_window;
GtkWidget *deposit_entry;
GtkWidget *deposit_confirm_button;
GtkWidget *deposit_cancel_button;

// 取款界面控件
GtkWidget *withdraw_window;
GtkWidget *withdraw_entry;
GtkWidget *withdraw_confirm_button;
GtkWidget *withdraw_cancel_button;

// 转账界面控件
GtkWidget *transfer_window;
GtkWidget *transfer_to_entry;
GtkWidget *transfer_amount_entry;
GtkWidget *transfer_confirm_button;
GtkWidget *transfer_cancel_button;

// 查询界面控件
GtkWidget *query_window;
GtkWidget *query_text_view;
GtkWidget *query_close_button;

// 修改密码界面控件
GtkWidget *change_password_window;
GtkWidget *old_password_entry;
GtkWidget *new_password_entry;
GtkWidget *confirm_password_entry;
GtkWidget *change_password_confirm_button;
GtkWidget *change_password_cancel_button;

/**
 * 创建交易窗口
 */
void create_transaction_window() {
    // 创建交易窗口
    transaction_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(transaction_window), "ATM交易系统");
    gtk_window_set_default_size(GTK_WINDOW(transaction_window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(transaction_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(transaction_window), FALSE);
    
    // 创建主容器
    transaction_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(transaction_window), transaction_container);
    
    // 应用样式
    GtkStyleContext *context = gtk_widget_get_style_context(transaction_container);
    gtk_style_context_add_class(context, "main-container");
    
    // 创建标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "ATM交易系统", "title");
    gtk_box_pack_start(GTK_BOX(transaction_container), title_label, FALSE, FALSE, 0);
    
    // 创建用户信息卡片
    GtkWidget *user_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkStyleContext *user_card_context = gtk_widget_get_style_context(user_card);
    gtk_style_context_add_class(user_card_context, "card");
    gtk_box_pack_start(GTK_BOX(transaction_container), user_card, FALSE, FALSE, 0);
    
    // 用户信息标签
    create_modern_label(&user_info_label, "", NULL);
    gtk_box_pack_start(GTK_BOX(user_card), user_info_label, FALSE, FALSE, 0);
    
    // 余额标签
    create_modern_label(&balance_label, "", NULL);
    gtk_box_pack_start(GTK_BOX(user_card), balance_label, FALSE, FALSE, 0);
    
    // 更新用户信息
    update_user_info();
    
    // 创建功能按钮网格
    GtkWidget *button_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(button_grid), 15);
    gtk_grid_set_row_spacing(GTK_GRID(button_grid), 15);
    gtk_box_pack_start(GTK_BOX(transaction_container), button_grid, TRUE, TRUE, 0);
    
    // 创建功能按钮
    create_modern_button(&deposit_button, "存款", "success");
    gtk_grid_attach(GTK_GRID(button_grid), deposit_button, 0, 0, 1, 1);
    
    create_modern_button(&withdraw_button, "取款", "warning");
    gtk_grid_attach(GTK_GRID(button_grid), withdraw_button, 1, 0, 1, 1);
    
    create_modern_button(&transfer_button, "转账", NULL);
    gtk_grid_attach(GTK_GRID(button_grid), transfer_button, 2, 0, 1, 1);
    
    create_modern_button(&query_button, "查询", NULL);
    gtk_grid_attach(GTK_GRID(button_grid), query_button, 0, 1, 1, 1);
    
    create_modern_button(&change_password_button, "修改密码", NULL);
    gtk_grid_attach(GTK_GRID(button_grid), change_password_button, 1, 1, 1, 1);
    
    create_modern_button(&logout_button, "退出登录", "danger");
    gtk_grid_attach(GTK_GRID(button_grid), logout_button, 2, 1, 1, 1);
    
    // 连接信号
    g_signal_connect(deposit_button, "clicked", G_CALLBACK(on_deposit_clicked), NULL);
    g_signal_connect(withdraw_button, "clicked", G_CALLBACK(on_withdraw_clicked), NULL);
    g_signal_connect(transfer_button, "clicked", G_CALLBACK(on_transfer_clicked), NULL);
    g_signal_connect(query_button, "clicked", G_CALLBACK(on_query_clicked), NULL);
    g_signal_connect(change_password_button, "clicked", G_CALLBACK(on_change_password_clicked), NULL);
    g_signal_connect(logout_button, "clicked", G_CALLBACK(on_logout_clicked), NULL);
    g_signal_connect(transaction_window, "destroy", G_CALLBACK(on_transaction_window_destroy), NULL);
    
    current_window = transaction_window;
}

/**
 * 更新用户信息显示
 */
void update_user_info() {
    // 查找当前用户信息
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index != -1) {
        char info_text[200];
        char balance_text[100];
        
        snprintf(info_text, sizeof(info_text), "欢迎，%s\n卡号：%s", 
                accounts[user_index].name, accounts[user_index].ID);
        gtk_label_set_text(GTK_LABEL(user_info_label), info_text);
        
        snprintf(balance_text, sizeof(balance_text), "当前余额：¥%.2f", 
                accounts[user_index].money);
        gtk_label_set_text(GTK_LABEL(balance_label), balance_text);
    }
}

/**
 * 存款按钮点击事件
 */
void on_deposit_clicked(GtkWidget *widget, gpointer data) {
    create_deposit_window();
    gtk_widget_show_all(deposit_window);
}

/**
 * 取款按钮点击事件
 */
void on_withdraw_clicked(GtkWidget *widget, gpointer data) {
    create_withdraw_window();
    gtk_widget_show_all(withdraw_window);
}

/**
 * 转账按钮点击事件
 */
void on_transfer_clicked(GtkWidget *widget, gpointer data) {
    create_transfer_window();
    gtk_widget_show_all(transfer_window);
}

/**
 * 查询按钮点击事件
 */
void on_query_clicked(GtkWidget *widget, gpointer data) {
    create_query_window();
    gtk_widget_show_all(query_window);
}

/**
 * 修改密码按钮点击事件
 */
void on_change_password_clicked(GtkWidget *widget, gpointer data) {
    create_change_password_window();
    gtk_widget_show_all(change_password_window);
}

/**
 * 退出登录按钮点击事件
 */
void on_logout_clicked(GtkWidget *widget, gpointer data) {
    // 显示确认对话框
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(transaction_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "确定要退出登录吗？"
    );
    
    gtk_window_set_title(GTK_WINDOW(dialog), "确认退出");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        gtk_widget_hide(transaction_window);
        gtk_widget_show_all(main_window);
        current_window = main_window;
        strcpy(currentAccount, "");
        show_info_dialog("已退出登录，请保存好银行卡！");
    }
}

/**
 * 交易窗口销毁事件
 */
void on_transaction_window_destroy(GtkWidget *widget, gpointer data) {
    gtk_widget_show_all(main_window);
    current_window = main_window;
    strcpy(currentAccount, "");
}

/**
 * 创建存款窗口
 */
void create_deposit_window() {
    deposit_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(deposit_window), "存款");
    gtk_window_set_default_size(GTK_WINDOW(deposit_window), 500, 400);
    gtk_window_set_position(GTK_WINDOW(deposit_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(deposit_window), TRUE);
    
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(deposit_window), container);
    
    GtkStyleContext *context = gtk_widget_get_style_context(container);
    gtk_style_context_add_class(context, "main-container");
    
    // 标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "存款", "title");
    gtk_box_pack_start(GTK_BOX(container), title_label, FALSE, FALSE, 0);
    
    // 当前余额显示
    GtkWidget *balance_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkStyleContext *balance_card_context = gtk_widget_get_style_context(balance_card);
    gtk_style_context_add_class(balance_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), balance_card, FALSE, FALSE, 0);
    
    GtkWidget *current_balance_label;
    create_modern_label(&current_balance_label, "", NULL);
    gtk_box_pack_start(GTK_BOX(balance_card), current_balance_label, FALSE, FALSE, 0);
    
    // 更新当前余额显示
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index != -1) {
        char balance_text[100];
        snprintf(balance_text, sizeof(balance_text), "当前余额：¥%.2f", accounts[user_index].money);
        gtk_label_set_text(GTK_LABEL(current_balance_label), balance_text);
    }
    
    // 存款输入卡片
    GtkWidget *input_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *input_card_context = gtk_widget_get_style_context(input_card);
    gtk_style_context_add_class(input_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), input_card, TRUE, TRUE, 0);
    
    // 金额输入
    GtkWidget *amount_label;
    create_modern_label(&amount_label, "请输入存款金额：", NULL);
    gtk_box_pack_start(GTK_BOX(input_card), amount_label, FALSE, FALSE, 0);
    
    create_modern_entry(&deposit_entry, "例如：1000.00");
    gtk_box_pack_start(GTK_BOX(input_card), deposit_entry, FALSE, FALSE, 0);
    
    // 快速金额按钮
    GtkWidget *quick_amounts_label;
    create_modern_label(&quick_amounts_label, "快速选择金额：", NULL);
    gtk_box_pack_start(GTK_BOX(input_card), quick_amounts_label, FALSE, FALSE, 0);
    
    GtkWidget *quick_buttons_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(quick_buttons_grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(quick_buttons_grid), 10);
    gtk_box_pack_start(GTK_BOX(input_card), quick_buttons_grid, FALSE, FALSE, 0);
    
    // 快速金额按钮
    GtkWidget *quick_100, *quick_500, *quick_1000, *quick_2000;
    create_modern_button(&quick_100, "100", NULL);
    create_modern_button(&quick_500, "500", NULL);
    create_modern_button(&quick_1000, "1000", NULL);
    create_modern_button(&quick_2000, "2000", NULL);
    
    gtk_grid_attach(GTK_GRID(quick_buttons_grid), quick_100, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(quick_buttons_grid), quick_500, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(quick_buttons_grid), quick_1000, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(quick_buttons_grid), quick_2000, 1, 1, 1, 1);
    
    // 按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(input_card), button_container, TRUE, TRUE, 0);
    
    create_modern_button(&deposit_confirm_button, "确认存款", "success");
    gtk_box_pack_start(GTK_BOX(button_container), deposit_confirm_button, TRUE, TRUE, 0);
    
    create_modern_button(&deposit_cancel_button, "取消", NULL);
    gtk_box_pack_start(GTK_BOX(button_container), deposit_cancel_button, TRUE, TRUE, 0);
    
    // 连接信号
    g_signal_connect(deposit_confirm_button, "clicked", G_CALLBACK(on_deposit_confirm_clicked), NULL);
    g_signal_connect(deposit_cancel_button, "clicked", G_CALLBACK(on_deposit_cancel_clicked), NULL);
    g_signal_connect(deposit_window, "destroy", G_CALLBACK(on_deposit_cancel_clicked), NULL);
    g_signal_connect(quick_100, "clicked", G_CALLBACK(on_quick_amount_clicked), (gpointer)"100");
    g_signal_connect(quick_500, "clicked", G_CALLBACK(on_quick_amount_clicked), (gpointer)"500");
    g_signal_connect(quick_1000, "clicked", G_CALLBACK(on_quick_amount_clicked), (gpointer)"1000");
    g_signal_connect(quick_2000, "clicked", G_CALLBACK(on_quick_amount_clicked), (gpointer)"2000");
}

/**
 * 快速金额选择事件
 */
void on_quick_amount_clicked(GtkWidget *widget, gpointer data) {
    const char *amount = (const char *)data;
    gtk_entry_set_text(GTK_ENTRY(deposit_entry), amount);
}

/**
 * 存款确认按钮点击事件
 */
void on_deposit_confirm_clicked(GtkWidget *widget, gpointer data) {
    const char *amount_text = gtk_entry_get_text(GTK_ENTRY(deposit_entry));
    double amount = atof(amount_text);
    
    // 验证输入
    if (strlen(amount_text) == 0) {
        show_error_dialog("请输入存款金额！");
        return;
    }
    
    if (amount <= 0) {
        show_error_dialog("存款金额必须大于0！");
        return;
    }
    
    if (amount > 50000) {
        show_error_dialog("单次存款金额不能超过50,000元！");
        return;
    }
    
    // 显示确认对话框
    char confirm_message[200];
    snprintf(confirm_message, sizeof(confirm_message), 
             "确认存款 ¥%.2f 元？\n\n存款后余额将更新。", amount);
    
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(deposit_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "%s", confirm_message
    );
    
    gtk_window_set_title(GTK_WINDOW(dialog), "确认存款");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        // 执行存款操作
        if (perform_deposit(amount)) {
            // 显示存款成功和回单选择对话框
            char success_message[300];
            snprintf(success_message, sizeof(success_message), 
                     "存款成功！\n\n存款金额：¥%.2f\n\n是否打印回单？", amount);
            
            GtkWidget *receipt_dialog = gtk_message_dialog_new(
                GTK_WINDOW(deposit_window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "%s", success_message
            );
            
            gtk_window_set_title(GTK_WINDOW(receipt_dialog), "存款成功");
            
            gint receipt_response = gtk_dialog_run(GTK_DIALOG(receipt_dialog));
            gtk_widget_destroy(receipt_dialog);
            
            if (receipt_response == GTK_RESPONSE_YES) {
                // 打印回单
                print_deposit_receipt(amount);
            }
            
            update_user_info();
            gtk_widget_hide(deposit_window);
        } else {
            show_error_dialog("存款失败，请重试！");
        }
    }
}

/**
 * 存款取消按钮点击事件
 */
void on_deposit_cancel_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(deposit_window);
}

/**
 * 执行存款操作
 */
int perform_deposit(double amount) {
    // 查找当前用户
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index == -1) {
        return 0;
    }
    
    // 更新余额
    accounts[user_index].money += amount;
    
    // 保存账户信息
    saveAccounts();
    
    // 创建流水记录
    Statement new_statement;
    generateStatementID(new_statement.ID);
    strcpy(new_statement.accountID, currentAccount);
    getCurrentTime(new_statement.time);
    new_statement.type = DEPOSIT;
    new_statement.money = amount;
    strcpy(new_statement.toAccount, "");
    
    statements[statementCount] = new_statement;
    statementCount++;
    saveStatements();
    
    return 1;
}

/**
 * 创建取款窗口
 */
void create_withdraw_window() {
    withdraw_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(withdraw_window), "取款");
    gtk_window_set_default_size(GTK_WINDOW(withdraw_window), 500, 400);
    gtk_window_set_position(GTK_WINDOW(withdraw_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(withdraw_window), TRUE);
    
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(withdraw_window), container);
    
    GtkStyleContext *context = gtk_widget_get_style_context(container);
    gtk_style_context_add_class(context, "main-container");
    
    // 标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "取款", "title");
    gtk_box_pack_start(GTK_BOX(container), title_label, FALSE, FALSE, 0);
    
    // 当前余额显示
    GtkWidget *balance_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkStyleContext *balance_card_context = gtk_widget_get_style_context(balance_card);
    gtk_style_context_add_class(balance_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), balance_card, FALSE, FALSE, 0);
    
    GtkWidget *current_balance_label;
    create_modern_label(&current_balance_label, "", NULL);
    gtk_box_pack_start(GTK_BOX(balance_card), current_balance_label, FALSE, FALSE, 0);
    
    // 更新当前余额显示
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index != -1) {
        char balance_text[100];
        snprintf(balance_text, sizeof(balance_text), "当前余额：¥%.2f", accounts[user_index].money);
        gtk_label_set_text(GTK_LABEL(current_balance_label), balance_text);
    }
    
    // 取款输入卡片
    GtkWidget *input_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *input_card_context = gtk_widget_get_style_context(input_card);
    gtk_style_context_add_class(input_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), input_card, TRUE, TRUE, 0);
    
    // 金额输入
    GtkWidget *amount_label;
    create_modern_label(&amount_label, "请输入取款金额：", NULL);
    gtk_box_pack_start(GTK_BOX(input_card), amount_label, FALSE, FALSE, 0);
    
    create_modern_entry(&withdraw_entry, "例如：500.00");
    gtk_box_pack_start(GTK_BOX(input_card), withdraw_entry, FALSE, FALSE, 0);
    
    // 快速金额按钮
    GtkWidget *quick_amounts_label;
    create_modern_label(&quick_amounts_label, "快速选择金额：", NULL);
    gtk_box_pack_start(GTK_BOX(input_card), quick_amounts_label, FALSE, FALSE, 0);
    
    GtkWidget *quick_buttons_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(quick_buttons_grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(quick_buttons_grid), 10);
    gtk_box_pack_start(GTK_BOX(input_card), quick_buttons_grid, FALSE, FALSE, 0);
    
    // 快速金额按钮
    GtkWidget *quick_100, *quick_500, *quick_1000, *quick_2000;
    create_modern_button(&quick_100, "100", NULL);
    create_modern_button(&quick_500, "500", NULL);
    create_modern_button(&quick_1000, "1000", NULL);
    create_modern_button(&quick_2000, "2000", NULL);
    
    gtk_grid_attach(GTK_GRID(quick_buttons_grid), quick_100, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(quick_buttons_grid), quick_500, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(quick_buttons_grid), quick_1000, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(quick_buttons_grid), quick_2000, 1, 1, 1, 1);
    
    // 按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(input_card), button_container, TRUE, TRUE, 0);
    
    create_modern_button(&withdraw_confirm_button, "确认取款", "warning");
    gtk_box_pack_start(GTK_BOX(button_container), withdraw_confirm_button, TRUE, TRUE, 0);
    
    create_modern_button(&withdraw_cancel_button, "取消", NULL);
    gtk_box_pack_start(GTK_BOX(button_container), withdraw_cancel_button, TRUE, TRUE, 0);
    
    // 连接信号
    g_signal_connect(withdraw_confirm_button, "clicked", G_CALLBACK(on_withdraw_confirm_clicked), NULL);
    g_signal_connect(withdraw_cancel_button, "clicked", G_CALLBACK(on_withdraw_cancel_clicked), NULL);
    g_signal_connect(withdraw_window, "destroy", G_CALLBACK(on_withdraw_cancel_clicked), NULL);
    g_signal_connect(quick_100, "clicked", G_CALLBACK(on_quick_withdraw_clicked), (gpointer)"100");
    g_signal_connect(quick_500, "clicked", G_CALLBACK(on_quick_withdraw_clicked), (gpointer)"500");
    g_signal_connect(quick_1000, "clicked", G_CALLBACK(on_quick_withdraw_clicked), (gpointer)"1000");
    g_signal_connect(quick_2000, "clicked", G_CALLBACK(on_quick_withdraw_clicked), (gpointer)"2000");
}

/**
 * 快速取款金额选择事件
 */
void on_quick_withdraw_clicked(GtkWidget *widget, gpointer data) {
    const char *amount = (const char *)data;
    gtk_entry_set_text(GTK_ENTRY(withdraw_entry), amount);
}

/**
 * 取款确认按钮点击事件
 */
void on_withdraw_confirm_clicked(GtkWidget *widget, gpointer data) {
    const char *amount_text = gtk_entry_get_text(GTK_ENTRY(withdraw_entry));
    double amount = atof(amount_text);
    
    // 验证输入
    if (strlen(amount_text) == 0) {
        show_error_dialog("请输入取款金额！");
        return;
    }
    
    if (amount <= 0) {
        show_error_dialog("取款金额必须大于0！");
        return;
    }
    
    if (amount > 10000) {
        show_error_dialog("单次取款金额不能超过10,000元！");
        return;
    }
    
    // 检查余额
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index == -1) {
        show_error_dialog("账户信息错误！");
        return;
    }
    
    if (accounts[user_index].money < amount) {
        char error_message[200];
        snprintf(error_message, sizeof(error_message), 
                 "余额不足！\n\n当前余额：¥%.2f\n取款金额：¥%.2f", 
                 accounts[user_index].money, amount);
        show_error_dialog(error_message);
        return;
    }
    
    // 显示确认对话框
    char confirm_message[200];
    snprintf(confirm_message, sizeof(confirm_message), 
             "确认取款 ¥%.2f 元？\n\n取款后余额：¥%.2f", 
             amount, accounts[user_index].money - amount);
    
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(withdraw_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "%s", confirm_message
    );
    
    gtk_window_set_title(GTK_WINDOW(dialog), "确认取款");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        // 执行取款操作
        if (perform_withdraw(amount)) {
            // 显示取款成功和回单选择对话框
            char success_message[300];
            snprintf(success_message, sizeof(success_message), 
                     "取款成功！\n\n取款金额：¥%.2f\n\n请收好现金。\n\n是否打印回单？", amount);
            
            GtkWidget *receipt_dialog = gtk_message_dialog_new(
                GTK_WINDOW(withdraw_window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "%s", success_message
            );
            
            gtk_window_set_title(GTK_WINDOW(receipt_dialog), "取款成功");
            
            gint receipt_response = gtk_dialog_run(GTK_DIALOG(receipt_dialog));
            gtk_widget_destroy(receipt_dialog);
            
            if (receipt_response == GTK_RESPONSE_YES) {
                // 打印回单
                print_withdraw_receipt(amount);
            }
            
            update_user_info();
            gtk_widget_hide(withdraw_window);
        } else {
            show_error_dialog("取款失败，请重试！");
        }
    }
}

/**
 * 取款取消按钮点击事件
 */
void on_withdraw_cancel_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(withdraw_window);
}

/**
 * 打印存款回单
 */
void print_deposit_receipt(double amount) {
    // 创建回单窗口
    GtkWidget *receipt_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(receipt_window), "存款回单");
    gtk_window_set_default_size(GTK_WINDOW(receipt_window), 500, 600);
    gtk_window_set_position(GTK_WINDOW(receipt_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(receipt_window), TRUE);
    
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(receipt_window), container);
    
    GtkStyleContext *context = gtk_widget_get_style_context(container);
    gtk_style_context_add_class(context, "main-container");
    
    // 标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "ATM存款回单", "title");
    gtk_box_pack_start(GTK_BOX(container), title_label, FALSE, FALSE, 0);
    
    // 回单内容
    GtkWidget *receipt_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *receipt_card_context = gtk_widget_get_style_context(receipt_card);
    gtk_style_context_add_class(receipt_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), receipt_card, TRUE, TRUE, 0);
    
    // 获取当前用户信息
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index != -1) {
        // 获取当前时间
        char current_time[50];
        getCurrentTime(current_time);
        
        // 构建回单内容
        char receipt_content[1000];
        snprintf(receipt_content, sizeof(receipt_content), 
                 "========================================\n"
                 "            ATM存款回单\n"
                 "========================================\n"
                 "交易时间：%s\n"
                 "卡号：%s\n"
                 "户名：%s\n"
                 "交易类型：存款\n"
                 "存款金额：¥%.2f\n"
                 "账户余额：¥%.2f\n"
                 "========================================\n"
                 "请妥善保管此回单\n"
                 "如有疑问，请联系银行客服\n"
                 "========================================",
                 current_time,
                 accounts[user_index].ID,
                 accounts[user_index].name,
                 amount,
                 accounts[user_index].money);
        
        // 创建文本视图显示回单
        GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), 
                                       GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_box_pack_start(GTK_BOX(receipt_card), scrolled_window, TRUE, TRUE, 0);
        
        GtkWidget *text_view = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
        gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
        
        // 设置回单内容
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        gtk_text_buffer_set_text(buffer, receipt_content, -1);
        
        // 设置字体为等宽字体，模拟打印效果
        PangoFontDescription *font_desc = pango_font_description_from_string("Monospace 12");
        gtk_widget_override_font(text_view, font_desc);
        pango_font_description_free(font_desc);
    }
    
    // 按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(container), button_container, FALSE, FALSE, 0);
    
    GtkWidget *print_button, *close_button;
    create_modern_button(&print_button, "打印回单", "success");
    create_modern_button(&close_button, "关闭", NULL);
    
    gtk_box_pack_start(GTK_BOX(button_container), print_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_container), close_button, TRUE, TRUE, 0);
    
    // 连接信号
    g_signal_connect(print_button, "clicked", G_CALLBACK(on_print_receipt_clicked), receipt_window);
    g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_receipt_clicked), receipt_window);
    g_signal_connect(receipt_window, "destroy", G_CALLBACK(on_close_receipt_clicked), receipt_window);
    
    gtk_widget_show_all(receipt_window);
}

/**
 * 打印转账回单
 */
void print_transfer_receipt(const char *to_account, double amount) {
    // 创建回单窗口
    GtkWidget *receipt_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(receipt_window), "转账回单");
    gtk_window_set_default_size(GTK_WINDOW(receipt_window), 500, 600);
    gtk_window_set_position(GTK_WINDOW(receipt_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(receipt_window), TRUE);
    
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(receipt_window), container);
    
    GtkStyleContext *context = gtk_widget_get_style_context(container);
    gtk_style_context_add_class(context, "main-container");
    
    // 标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "ATM转账回单", "title");
    gtk_box_pack_start(GTK_BOX(container), title_label, FALSE, FALSE, 0);
    
    // 回单内容
    GtkWidget *receipt_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *receipt_card_context = gtk_widget_get_style_context(receipt_card);
    gtk_style_context_add_class(receipt_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), receipt_card, TRUE, TRUE, 0);
    
    // 获取当前用户信息
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index != -1) {
        // 获取当前时间
        char current_time[50];
        getCurrentTime(current_time);
        
        // 构建回单内容
        char receipt_content[1000];
        snprintf(receipt_content, sizeof(receipt_content), 
                 "========================================\n"
                 "            ATM转账回单\n"
                 "========================================\n"
                 "交易时间：%s\n"
                 "转出账户：%s\n"
                 "户名：%s\n"
                 "转入账户：%s\n"
                 "交易类型：转账\n"
                 "转账金额：¥%.2f\n"
                 "账户余额：¥%.2f\n"
                 "========================================\n"
                 "请妥善保管此回单\n"
                 "如有疑问，请联系银行客服\n"
                 "========================================",
                 current_time,
                 currentAccount,
                 accounts[user_index].name,
                 to_account,
                 amount,
                 accounts[user_index].money);
        
        // 创建文本视图显示回单
        GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), 
                                       GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_box_pack_start(GTK_BOX(receipt_card), scrolled_window, TRUE, TRUE, 0);
        
        GtkWidget *text_view = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
        gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
        
        // 设置回单内容
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        gtk_text_buffer_set_text(buffer, receipt_content, -1);
        
        // 设置字体为等宽字体，模拟打印效果
        PangoFontDescription *font_desc = pango_font_description_from_string("Monospace 12");
        gtk_widget_override_font(text_view, font_desc);
        pango_font_description_free(font_desc);
    }
    
    // 按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(container), button_container, FALSE, FALSE, 0);
    
    GtkWidget *print_button, *close_button;
    create_modern_button(&print_button, "打印回单", "success");
    create_modern_button(&close_button, "关闭", NULL);
    
    gtk_box_pack_start(GTK_BOX(button_container), print_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_container), close_button, TRUE, TRUE, 0);
    
    // 连接信号
    g_signal_connect(print_button, "clicked", G_CALLBACK(on_print_receipt_clicked), receipt_window);
    g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_receipt_clicked), receipt_window);
    g_signal_connect(receipt_window, "destroy", G_CALLBACK(on_close_receipt_clicked), receipt_window);
    
    gtk_widget_show_all(receipt_window);
}

/**
 * 打印取款回单
 */
void print_withdraw_receipt(double amount) {
    // 创建回单窗口
    GtkWidget *receipt_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(receipt_window), "取款回单");
    gtk_window_set_default_size(GTK_WINDOW(receipt_window), 500, 600);
    gtk_window_set_position(GTK_WINDOW(receipt_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(receipt_window), TRUE);
    
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(receipt_window), container);
    
    GtkStyleContext *context = gtk_widget_get_style_context(container);
    gtk_style_context_add_class(context, "main-container");
    
    // 标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "ATM取款回单", "title");
    gtk_box_pack_start(GTK_BOX(container), title_label, FALSE, FALSE, 0);
    
    // 回单内容
    GtkWidget *receipt_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *receipt_card_context = gtk_widget_get_style_context(receipt_card);
    gtk_style_context_add_class(receipt_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), receipt_card, TRUE, TRUE, 0);
    
    // 获取当前用户信息
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index != -1) {
        // 获取当前时间
        char current_time[50];
        getCurrentTime(current_time);
        
        // 构建回单内容
        char receipt_content[1000];
        snprintf(receipt_content, sizeof(receipt_content), 
                 "========================================\n"
                 "            ATM取款回单\n"
                 "========================================\n"
                 "交易时间：%s\n"
                 "卡号：%s\n"
                 "户名：%s\n"
                 "交易类型：取款\n"
                 "取款金额：¥%.2f\n"
                 "账户余额：¥%.2f\n"
                 "========================================\n"
                 "请妥善保管此回单\n"
                 "如有疑问，请联系银行客服\n"
                 "========================================",
                 current_time,
                 accounts[user_index].ID,
                 accounts[user_index].name,
                 amount,
                 accounts[user_index].money);
        
        // 创建文本视图显示回单
        GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), 
                                       GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_box_pack_start(GTK_BOX(receipt_card), scrolled_window, TRUE, TRUE, 0);
        
        GtkWidget *text_view = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
        gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
        
        // 设置回单内容
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
        gtk_text_buffer_set_text(buffer, receipt_content, -1);
        
        // 设置字体为等宽字体，模拟打印效果
        PangoFontDescription *font_desc = pango_font_description_from_string("Monospace 12");
        gtk_widget_override_font(text_view, font_desc);
        pango_font_description_free(font_desc);
    }
    
    // 按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(container), button_container, FALSE, FALSE, 0);
    
    GtkWidget *print_button, *close_button;
    create_modern_button(&print_button, "打印回单", "success");
    create_modern_button(&close_button, "关闭", NULL);
    
    gtk_box_pack_start(GTK_BOX(button_container), print_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_container), close_button, TRUE, TRUE, 0);
    
    // 连接信号
    g_signal_connect(print_button, "clicked", G_CALLBACK(on_print_receipt_clicked), receipt_window);
    g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_receipt_clicked), receipt_window);
    g_signal_connect(receipt_window, "destroy", G_CALLBACK(on_close_receipt_clicked), receipt_window);
    
    gtk_widget_show_all(receipt_window);
}

/**
 * 打印回单按钮点击事件
 */
void on_print_receipt_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *receipt_window = (GtkWidget *)data;
    
    // 显示打印成功消息
    show_success_dialog("回单已发送到打印机！\n\n请取走回单。");
    
    // 关闭回单窗口
    gtk_widget_destroy(receipt_window);
}

/**
 * 关闭回单按钮点击事件
 */
void on_close_receipt_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *receipt_window = (GtkWidget *)data;
    gtk_widget_destroy(receipt_window);
}

/**
 * 执行取款操作
 */
int perform_withdraw(double amount) {
    // 查找当前用户
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index == -1) {
        return 0;
    }
    
    // 检查余额
    if (accounts[user_index].money < amount) {
        return 0;
    }
    
    // 更新余额
    accounts[user_index].money -= amount;
    
    // 保存账户信息
    saveAccounts();
    
    // 创建流水记录
    Statement new_statement;
    generateStatementID(new_statement.ID);
    strcpy(new_statement.accountID, currentAccount);
    getCurrentTime(new_statement.time);
    new_statement.type = WITHDRAW;
    new_statement.money = amount;
    strcpy(new_statement.toAccount, "");
    
    statements[statementCount] = new_statement;
    statementCount++;
    saveStatements();
    
    return 1;
}

/**
 * 创建转账窗口
 */
void create_transfer_window() {
    transfer_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(transfer_window), "转账");
    gtk_window_set_default_size(GTK_WINDOW(transfer_window), 500, 450);
    gtk_window_set_position(GTK_WINDOW(transfer_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(transfer_window), TRUE);
    
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(transfer_window), container);
    
    GtkStyleContext *context = gtk_widget_get_style_context(container);
    gtk_style_context_add_class(context, "main-container");
    
    // 标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "转账", "title");
    gtk_box_pack_start(GTK_BOX(container), title_label, FALSE, FALSE, 0);
    
    // 当前余额显示
    GtkWidget *balance_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkStyleContext *balance_card_context = gtk_widget_get_style_context(balance_card);
    gtk_style_context_add_class(balance_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), balance_card, FALSE, FALSE, 0);
    
    GtkWidget *current_balance_label;
    create_modern_label(&current_balance_label, "", NULL);
    gtk_box_pack_start(GTK_BOX(balance_card), current_balance_label, FALSE, FALSE, 0);
    
    // 更新当前余额显示
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index != -1) {
        char balance_text[100];
        snprintf(balance_text, sizeof(balance_text), "当前余额：¥%.2f", accounts[user_index].money);
        gtk_label_set_text(GTK_LABEL(current_balance_label), balance_text);
    }
    
    // 转账输入卡片
    GtkWidget *input_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *input_card_context = gtk_widget_get_style_context(input_card);
    gtk_style_context_add_class(input_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), input_card, TRUE, TRUE, 0);
    
    // 对方账户输入
    GtkWidget *to_account_label;
    create_modern_label(&to_account_label, "请输入对方账户：", NULL);
    gtk_box_pack_start(GTK_BOX(input_card), to_account_label, FALSE, FALSE, 0);
    
    create_modern_entry(&transfer_to_entry, "例如：622202000002");
    gtk_box_pack_start(GTK_BOX(input_card), transfer_to_entry, FALSE, FALSE, 0);
    
    // 转账金额输入
    GtkWidget *amount_label;
    create_modern_label(&amount_label, "请输入转账金额：", NULL);
    gtk_box_pack_start(GTK_BOX(input_card), amount_label, FALSE, FALSE, 0);
    
    create_modern_entry(&transfer_amount_entry, "例如：1000.00");
    gtk_box_pack_start(GTK_BOX(input_card), transfer_amount_entry, FALSE, FALSE, 0);
    
    // 按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(input_card), button_container, TRUE, TRUE, 0);
    
    create_modern_button(&transfer_confirm_button, "确认转账", NULL);
    gtk_box_pack_start(GTK_BOX(button_container), transfer_confirm_button, TRUE, TRUE, 0);
    
    create_modern_button(&transfer_cancel_button, "取消", NULL);
    gtk_box_pack_start(GTK_BOX(button_container), transfer_cancel_button, TRUE, TRUE, 0);
    
    // 连接信号
    g_signal_connect(transfer_confirm_button, "clicked", G_CALLBACK(on_transfer_confirm_clicked), NULL);
    g_signal_connect(transfer_cancel_button, "clicked", G_CALLBACK(on_transfer_cancel_clicked), NULL);
    g_signal_connect(transfer_window, "destroy", G_CALLBACK(on_transfer_cancel_clicked), NULL);
}

/**
 * 转账确认按钮点击事件
 */
void on_transfer_confirm_clicked(GtkWidget *widget, gpointer data) {
    const char *to_account_text = gtk_entry_get_text(GTK_ENTRY(transfer_to_entry));
    const char *amount_text = gtk_entry_get_text(GTK_ENTRY(transfer_amount_entry));
    double amount = atof(amount_text);
    
    // 验证输入
    if (strlen(to_account_text) == 0) {
        show_error_dialog("请输入对方账户！");
        return;
    }
    
    if (strlen(amount_text) == 0) {
        show_error_dialog("请输入转账金额！");
        return;
    }
    
    if (amount <= 0) {
        show_error_dialog("转账金额必须大于0！");
        return;
    }
    
    if (amount > 50000) {
        show_error_dialog("单次转账金额不能超过50,000元！");
        return;
    }
    
    // 检查不能转给自己
    if (strcmp(to_account_text, currentAccount) == 0) {
        show_error_dialog("不能转账给自己！");
        return;
    }
    
    // 检查对方账户是否存在
    int to_account_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, to_account_text) == 0) {
            to_account_index = i;
            break;
        }
    }
    
    if (to_account_index == -1) {
        show_error_dialog("对方账户不存在！");
        return;
    }
    
    // 检查余额
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index == -1) {
        show_error_dialog("账户信息错误！");
        return;
    }
    
    if (accounts[user_index].money < amount) {
        char error_message[200];
        snprintf(error_message, sizeof(error_message), 
                 "余额不足！\n\n当前余额：¥%.2f\n转账金额：¥%.2f", 
                 accounts[user_index].money, amount);
        show_error_dialog(error_message);
        return;
    }
    
    // 显示确认对话框
    char confirm_message[300];
    snprintf(confirm_message, sizeof(confirm_message), 
             "确认转账？\n\n转出账户：%s\n转入账户：%s\n转账金额：¥%.2f\n\n转账后余额：¥%.2f", 
             currentAccount, to_account_text, amount, accounts[user_index].money - amount);
    
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(transfer_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "%s", confirm_message
    );
    
    gtk_window_set_title(GTK_WINDOW(dialog), "确认转账");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        // 执行转账操作
        if (perform_transfer(to_account_text, amount)) {
            // 显示转账成功和回单选择对话框
            char success_message[300];
            snprintf(success_message, sizeof(success_message), 
                     "转账成功！\n\n转账金额：¥%.2f\n对方账户：%s\n\n是否打印回单？", amount, to_account_text);
            
            GtkWidget *receipt_dialog = gtk_message_dialog_new(
                GTK_WINDOW(transfer_window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_QUESTION,
                GTK_BUTTONS_YES_NO,
                "%s", success_message
            );
            
            gtk_window_set_title(GTK_WINDOW(receipt_dialog), "转账成功");
            
            gint receipt_response = gtk_dialog_run(GTK_DIALOG(receipt_dialog));
            gtk_widget_destroy(receipt_dialog);
            
            if (receipt_response == GTK_RESPONSE_YES) {
                // 打印回单
                print_transfer_receipt(to_account_text, amount);
            }
            
            update_user_info();
            gtk_widget_hide(transfer_window);
        } else {
            show_error_dialog("转账失败，请重试！");
        }
    }
}

/**
 * 转账取消按钮点击事件
 */
void on_transfer_cancel_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(transfer_window);
}

/**
 * 执行转账操作
 */
int perform_transfer(const char *to_account, double amount) {
    // 查找当前用户
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    // 查找对方账户
    int to_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, to_account) == 0) {
            to_index = i;
            break;
        }
    }
    
    if (user_index == -1 || to_index == -1) {
        return 0;
    }
    
    // 检查余额
    if (accounts[user_index].money < amount) {
        return 0;
    }
    
    // 更新余额
    accounts[user_index].money -= amount;
    accounts[to_index].money += amount;
    
    // 保存账户信息
    saveAccounts();
    
    // 创建流水记录（转出）
    Statement out_statement;
    generateStatementID(out_statement.ID);
    strcpy(out_statement.accountID, currentAccount);
    getCurrentTime(out_statement.time);
    out_statement.type = TRANSFER;
    out_statement.money = amount;
    strcpy(out_statement.toAccount, to_account);
    
    statements[statementCount] = out_statement;
    statementCount++;
    
    // 创建流水记录（转入）
    Statement in_statement;
    generateStatementID(in_statement.ID);
    strcpy(in_statement.accountID, to_account);
    getCurrentTime(in_statement.time);
    in_statement.type = TRANSFER;
    in_statement.money = amount;
    strcpy(in_statement.toAccount, currentAccount);
    
    statements[statementCount] = in_statement;
    statementCount++;
    
    saveStatements();
    
    return 1;
}

/**
 * 创建查询窗口
 */
void create_query_window() {
    query_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(query_window), "账户查询");
    gtk_window_set_default_size(GTK_WINDOW(query_window), 600, 500);
    gtk_window_set_position(GTK_WINDOW(query_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(query_window), TRUE);
    
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(query_window), container);
    
    GtkStyleContext *context = gtk_widget_get_style_context(container);
    gtk_style_context_add_class(context, "main-container");
    
    // 标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "账户查询", "title");
    gtk_box_pack_start(GTK_BOX(container), title_label, FALSE, FALSE, 0);
    
    // 账户信息卡片
    GtkWidget *account_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *account_card_context = gtk_widget_get_style_context(account_card);
    gtk_style_context_add_class(account_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), account_card, FALSE, FALSE, 0);
    
    // 显示账户信息
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index != -1) {
        char account_info[500];
        snprintf(account_info, sizeof(account_info), 
                 "账户信息\n\n"
                 "卡号：%s\n"
                 "姓名：%s\n"
                 "余额：¥%.2f\n"
                 "状态：%s", 
                 accounts[user_index].ID,
                 accounts[user_index].name,
                 accounts[user_index].money,
                 accounts[user_index].isLocked ? "已锁定" : "正常");
        
        GtkWidget *account_info_label;
        create_modern_label(&account_info_label, account_info, NULL);
        gtk_box_pack_start(GTK_BOX(account_card), account_info_label, FALSE, FALSE, 0);
    }
    
    // 交易历史
    GtkWidget *history_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *history_card_context = gtk_widget_get_style_context(history_card);
    gtk_style_context_add_class(history_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), history_card, TRUE, TRUE, 0);
    
    GtkWidget *history_label;
    create_modern_label(&history_label, "最近交易记录", NULL);
    gtk_box_pack_start(GTK_BOX(history_card), history_label, FALSE, FALSE, 0);
    
    // 创建滚动窗口和文本视图
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), 
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(history_card), scrolled_window, TRUE, TRUE, 0);
    
    query_text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(query_text_view), FALSE);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), query_text_view);
    
    // 显示交易历史
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(query_text_view));
    GtkTextIter iter;
    gtk_text_buffer_get_start_iter(buffer, &iter);
    
    // 查找并显示最近10笔交易
    int transaction_count = 0;
    for (int i = statementCount - 1; i >= 0 && transaction_count < 10; i--) {
        if (strcmp(statements[i].accountID, currentAccount) == 0) {
            char transaction_text[200];
            const char *type_name = "";
            switch (statements[i].type) {
                case DEPOSIT: type_name = "存款"; break;
                case WITHDRAW: type_name = "取款"; break;
                case TRANSFER: type_name = "转账"; break;
                default: type_name = "其他"; break;
            }
            
            snprintf(transaction_text, sizeof(transaction_text), 
                     "%s - %s - ¥%.2f - %s\n", 
                     statements[i].time, type_name, statements[i].money, 
                     strlen(statements[i].toAccount) > 0 ? statements[i].toAccount : "");
            
            gtk_text_buffer_insert(buffer, &iter, transaction_text, -1);
            transaction_count++;
        }
    }
    
    if (transaction_count == 0) {
        gtk_text_buffer_insert(buffer, &iter, "暂无交易记录", -1);
    }
    
    // 按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(container), button_container, FALSE, FALSE, 0);
    
    create_modern_button(&query_close_button, "关闭", NULL);
    gtk_box_pack_start(GTK_BOX(button_container), query_close_button, TRUE, TRUE, 0);
    
    // 连接信号
    g_signal_connect(query_close_button, "clicked", G_CALLBACK(on_query_close_clicked), NULL);
    g_signal_connect(query_window, "destroy", G_CALLBACK(on_query_close_clicked), NULL);
}

/**
 * 查询关闭按钮点击事件
 */
void on_query_close_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(query_window);
}

/**
 * 创建修改密码窗口
 */
void create_change_password_window() {
    change_password_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(change_password_window), "修改密码");
    gtk_window_set_default_size(GTK_WINDOW(change_password_window), 450, 400);
    gtk_window_set_position(GTK_WINDOW(change_password_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(change_password_window), TRUE);
    
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(change_password_window), container);
    
    GtkStyleContext *context = gtk_widget_get_style_context(container);
    gtk_style_context_add_class(context, "main-container");
    
    // 标题
    GtkWidget *title_label;
    create_modern_label(&title_label, "修改密码", "title");
    gtk_box_pack_start(GTK_BOX(container), title_label, FALSE, FALSE, 0);
    
    // 密码输入卡片
    GtkWidget *input_card = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *input_card_context = gtk_widget_get_style_context(input_card);
    gtk_style_context_add_class(input_card_context, "card");
    gtk_box_pack_start(GTK_BOX(container), input_card, TRUE, TRUE, 0);
    
    // 原密码输入
    GtkWidget *old_password_label;
    create_modern_label(&old_password_label, "请输入原密码：", NULL);
    gtk_box_pack_start(GTK_BOX(input_card), old_password_label, FALSE, FALSE, 0);
    
    create_modern_entry(&old_password_entry, "请输入6位原密码");
    gtk_entry_set_visibility(GTK_ENTRY(old_password_entry), FALSE);
    gtk_box_pack_start(GTK_BOX(input_card), old_password_entry, FALSE, FALSE, 0);
    
    // 新密码输入
    GtkWidget *new_password_label;
    create_modern_label(&new_password_label, "请输入新密码：", NULL);
    gtk_box_pack_start(GTK_BOX(input_card), new_password_label, FALSE, FALSE, 0);
    
    create_modern_entry(&new_password_entry, "请输入6位新密码");
    gtk_entry_set_visibility(GTK_ENTRY(new_password_entry), FALSE);
    gtk_box_pack_start(GTK_BOX(input_card), new_password_entry, FALSE, FALSE, 0);
    
    // 确认新密码输入
    GtkWidget *confirm_password_label;
    create_modern_label(&confirm_password_label, "请确认新密码：", NULL);
    gtk_box_pack_start(GTK_BOX(input_card), confirm_password_label, FALSE, FALSE, 0);
    
    create_modern_entry(&confirm_password_entry, "请再次输入6位新密码");
    gtk_entry_set_visibility(GTK_ENTRY(confirm_password_entry), FALSE);
    gtk_box_pack_start(GTK_BOX(input_card), confirm_password_entry, FALSE, FALSE, 0);
    
    // 密码要求说明
    GtkWidget *password_help_label;
    create_modern_label(&password_help_label, "密码要求：6位数字", NULL);
    GtkStyleContext *help_context = gtk_widget_get_style_context(password_help_label);
    gtk_style_context_add_class(help_context, "info-text");
    gtk_box_pack_start(GTK_BOX(input_card), password_help_label, FALSE, FALSE, 0);
    
    // 按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    gtk_box_pack_start(GTK_BOX(input_card), button_container, TRUE, TRUE, 0);
    
    create_modern_button(&change_password_confirm_button, "确认修改", "success");
    gtk_box_pack_start(GTK_BOX(button_container), change_password_confirm_button, TRUE, TRUE, 0);
    
    create_modern_button(&change_password_cancel_button, "取消", NULL);
    gtk_box_pack_start(GTK_BOX(button_container), change_password_cancel_button, TRUE, TRUE, 0);
    
    // 连接信号
    g_signal_connect(change_password_confirm_button, "clicked", G_CALLBACK(on_change_password_confirm_clicked), NULL);
    g_signal_connect(change_password_cancel_button, "clicked", G_CALLBACK(on_change_password_cancel_clicked), NULL);
    g_signal_connect(change_password_window, "destroy", G_CALLBACK(on_change_password_cancel_clicked), NULL);
}

/**
 * 修改密码确认按钮点击事件
 */
void on_change_password_confirm_clicked(GtkWidget *widget, gpointer data) {
    const char *old_password_text = gtk_entry_get_text(GTK_ENTRY(old_password_entry));
    const char *new_password_text = gtk_entry_get_text(GTK_ENTRY(new_password_entry));
    const char *confirm_password_text = gtk_entry_get_text(GTK_ENTRY(confirm_password_entry));
    
    // 验证输入
    if (strlen(old_password_text) == 0) {
        show_error_dialog("请输入原密码！");
        return;
    }
    
    if (strlen(new_password_text) == 0) {
        show_error_dialog("请输入新密码！");
        return;
    }
    
    if (strlen(confirm_password_text) == 0) {
        show_error_dialog("请确认新密码！");
        return;
    }
    
    // 验证密码格式
    if (strlen(old_password_text) != 6 || strlen(new_password_text) != 6 || strlen(confirm_password_text) != 6) {
        show_error_dialog("密码必须为6位数字！");
        return;
    }
    
    // 检查是否全为数字
    for (int i = 0; i < 6; i++) {
        if (!isdigit(old_password_text[i]) || !isdigit(new_password_text[i]) || !isdigit(confirm_password_text[i])) {
            show_error_dialog("密码只能包含数字！");
            return;
        }
    }
    
    // 检查新密码和确认密码是否一致
    if (strcmp(new_password_text, confirm_password_text) != 0) {
        show_error_dialog("新密码和确认密码不一致！");
        return;
    }
    
    // 检查新密码不能与原密码相同
    if (strcmp(old_password_text, new_password_text) == 0) {
        show_error_dialog("新密码不能与原密码相同！");
        return;
    }
    
    // 验证原密码
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index == -1) {
        show_error_dialog("账户信息错误！");
        return;
    }
    
    // 验证原密码
    int old_password[6];
    for (int i = 0; i < 6; i++) {
        old_password[i] = old_password_text[i] - '0';
    }
    
    int decrypted_password[6];
    decryptPassword(accounts[user_index].password, decrypted_password);
    
    for (int i = 0; i < 6; i++) {
        if (old_password[i] != decrypted_password[i]) {
            show_error_dialog("原密码错误！");
            return;
        }
    }
    
    // 显示确认对话框
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(change_password_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "确认修改密码？\n\n新密码：%s", new_password_text
    );
    
    gtk_window_set_title(GTK_WINDOW(dialog), "确认修改密码");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        // 执行密码修改
        if (perform_change_password(new_password_text)) {
            show_success_dialog("密码修改成功！\n\n请妥善保管新密码。");
            gtk_widget_hide(change_password_window);
        } else {
            show_error_dialog("密码修改失败，请重试！");
        }
    }
}

/**
 * 修改密码取消按钮点击事件
 */
void on_change_password_cancel_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(change_password_window);
}

/**
 * 执行密码修改操作
 */
int perform_change_password(const char *new_password) {
    // 查找当前用户
    int user_index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].ID, currentAccount) == 0) {
            user_index = i;
            break;
        }
    }
    
    if (user_index == -1) {
        return 0;
    }
    
    // 加密新密码
    int new_password_array[6];
    for (int i = 0; i < 6; i++) {
        new_password_array[i] = new_password[i] - '0';
    }
    
    encryptPassword(new_password_array, accounts[user_index].password);
    
    // 保存账户信息
    saveAccounts();
    
    return 1;
}
