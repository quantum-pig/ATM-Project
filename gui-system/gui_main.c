#include "gui_common.h"

// 全局变量
GtkWidget *main_container;
GtkWidget *welcome_label;
GtkWidget *login_button;
GtkWidget *exit_button;

/**
 * 创建主窗口
 */
void create_main_window() {
    // 创建主窗口
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "ATM仿真系统");
    gtk_window_set_default_size(GTK_WINDOW(main_window), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(main_window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(main_window), FALSE);
    
    // 创建主容器
    main_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(main_window), main_container);
    
    // 应用样式
    GtkStyleContext *context = gtk_widget_get_style_context(main_container);
    gtk_style_context_add_class(context, "main-container");
    
    // 创建欢迎标题
    create_modern_label(&welcome_label, "欢迎使用ATM仿真系统", "title");
    gtk_box_pack_start(GTK_BOX(main_container), welcome_label, FALSE, FALSE, 0);
    
    // 创建副标题
    GtkWidget *subtitle_label;
    create_modern_label(&subtitle_label, "现代化银行服务体验", "subtitle");
    gtk_box_pack_start(GTK_BOX(main_container), subtitle_label, FALSE, FALSE, 0);
    
    // 创建卡片容器
    GtkWidget *card_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    GtkStyleContext *card_context = gtk_widget_get_style_context(card_container);
    gtk_style_context_add_class(card_context, "card");
    gtk_box_pack_start(GTK_BOX(main_container), card_container, TRUE, TRUE, 0);
    
    // 创建功能说明
    GtkWidget *info_label;
    create_modern_label(&info_label, "请选择您要进行的操作", NULL);
    gtk_box_pack_start(GTK_BOX(card_container), info_label, FALSE, FALSE, 0);
    
    // 创建按钮容器
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_box_pack_start(GTK_BOX(card_container), button_container, TRUE, TRUE, 0);
    
    // 创建登录按钮
    create_modern_button(&login_button, "登录系统", NULL);
    gtk_box_pack_start(GTK_BOX(button_container), login_button, TRUE, TRUE, 0);
    
    // 创建退出按钮
    create_modern_button(&exit_button, "退出系统", "danger");
    gtk_box_pack_start(GTK_BOX(button_container), exit_button, TRUE, TRUE, 0);
    
    // 创建底部信息
    GtkWidget *footer_label;
    create_modern_label(&footer_label, "安全 · 便捷 · 高效", NULL);
    GtkStyleContext *footer_context = gtk_widget_get_style_context(footer_label);
    gtk_style_context_add_class(footer_context, "info-text");
    gtk_box_pack_start(GTK_BOX(main_container), footer_label, FALSE, FALSE, 0);
    
    // 连接信号
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), NULL);
    g_signal_connect(exit_button, "clicked", G_CALLBACK(on_exit_clicked), NULL);
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    current_window = main_window;
}

/**
 * 登录按钮点击事件
 */
void on_login_clicked(GtkWidget *widget, gpointer data) {
    // 隐藏主窗口
    gtk_widget_hide(main_window);
    
    // 显示登录窗口
    create_login_window();
    gtk_widget_show_all(login_window);
}

/**
 * 退出按钮点击事件
 */
void on_exit_clicked(GtkWidget *widget, gpointer data) {
    // 显示确认对话框
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(main_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "确定要退出ATM系统吗？"
    );
    
    gtk_window_set_title(GTK_WINDOW(dialog), "确认退出");
    
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    if (response == GTK_RESPONSE_YES) {
        // 显示退出信息
        show_info_dialog("感谢使用ATM仿真系统！");
        gtk_main_quit();
    }
}

/**
 * 显示主窗口
 */
void show_main_window() {
    if (!main_window) {
        create_main_window();
    }
    gtk_widget_show_all(main_window);
    current_window = main_window;
}