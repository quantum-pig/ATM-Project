#include "gui_common.h"

// GUI全局变量定义
GtkWidget *main_window = NULL;
GtkWidget *login_window = NULL;
GtkWidget *transaction_window = NULL;
GtkWidget *current_window = NULL;

/**
 * 初始化GUI系统
 */
void gui_init() {
    // 初始化GTK
    gtk_init(NULL, NULL);
    
    // 设置CSS样式
    GtkCssProvider *css_provider = gtk_css_provider_new();
    const char *css = 
        "* {"
        "    font-family: 'Microsoft YaHei', 'PingFang SC', 'Helvetica Neue', Arial, sans-serif;"
        "}"
        ".main-container {"
        "    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);"
        "    border-radius: 15px;"
        "    padding: 20px;"
        "    margin: 10px;"
        "}"
        ".card {"
        "    background: rgba(255, 255, 255, 0.95);"
        "    border-radius: 12px;"
        "    box-shadow: 0 8px 32px rgba(0, 0, 0, 0.1);"
        "    padding: 20px;"
        "    margin: 10px;"
        "}"
        ".title {"
        "    font-size: 28px;"
        "    font-weight: bold;"
        "    color: #2c3e50;"
        "    text-align: center;"
        "    margin-bottom: 20px;"
        "}"
        ".subtitle {"
        "    font-size: 18px;"
        "    color: #34495e;"
        "    text-align: center;"
        "    margin-bottom: 15px;"
        "}"
        ".modern-button {"
        "    background: linear-gradient(45deg, #667eea, #764ba2);"
        "    border: none;"
        "    border-radius: 8px;"
        "    color: white;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    padding: 12px 24px;"
        "    margin: 5px;"
        "    transition: all 0.3s ease;"
        "    box-shadow: 0 4px 15px rgba(0, 0, 0, 0.2);"
        "}"
        ".modern-button:hover {"
        "    transform: translateY(-2px);"
        "    box-shadow: 0 6px 20px rgba(0, 0, 0, 0.3);"
        "}"
        ".modern-button:active {"
        "    transform: translateY(0);"
        "}"
        ".success-button {"
        "    background: linear-gradient(45deg, #4CAF50, #45a049);"
        "}"
        ".warning-button {"
        "    background: linear-gradient(45deg, #FF9800, #f57c00);"
        "}"
        ".danger-button {"
        "    background: linear-gradient(45deg, #F44336, #d32f2f);"
        "}"
        ".modern-entry {"
        "    border: 2px solid #e0e0e0;"
        "    border-radius: 8px;"
        "    padding: 12px 16px;"
        "    font-size: 16px;"
        "    background: white;"
        "    transition: border-color 0.3s ease;"
        "}"
        ".modern-entry:focus {"
        "    border-color: #667eea;"
        "    box-shadow: 0 0 0 3px rgba(102, 126, 234, 0.1);"
        "}"
        ".modern-label {"
        "    color: #2c3e50;"
        "    font-weight: 500;"
        "    margin: 5px 0;"
        "}"
        ".info-text {"
        "    color: #7f8c8d;"
        "    font-size: 14px;"
        "    text-align: center;"
        "    margin: 10px 0;"
        "}";
    
    gtk_css_provider_load_from_data(css_provider, css, -1, NULL);
    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
}

/**
 * 清理GUI资源
 */
void gui_cleanup() {
    if (main_window) {
        gtk_widget_destroy(main_window);
    }
    if (login_window) {
        gtk_widget_destroy(login_window);
    }
    if (transaction_window) {
        gtk_widget_destroy(transaction_window);
    }
}

/**
 * 显示错误对话框
 */
void show_error_dialog(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(current_window ? current_window : main_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        "%s", message
    );
    
    gtk_window_set_title(GTK_WINDOW(dialog), "错误");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/**
 * 显示成功对话框
 */
void show_success_dialog(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(current_window ? current_window : main_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "%s", message
    );
    
    gtk_window_set_title(GTK_WINDOW(dialog), "成功");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/**
 * 显示信息对话框
 */
void show_info_dialog(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(current_window ? current_window : main_window),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "%s", message
    );
    
    gtk_window_set_title(GTK_WINDOW(dialog), "信息");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/**
 * 应用现代化样式
 */
void apply_modern_style(GtkWidget *widget) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, "modern-widget");
}

/**
 * 创建现代化按钮
 */
void create_modern_button(GtkWidget **button, const char *text, const char *color) {
    *button = gtk_button_new_with_label(text);
    
    GtkStyleContext *context = gtk_widget_get_style_context(*button);
    gtk_style_context_add_class(context, "modern-button");
    
    if (color) {
        if (strcmp(color, "success") == 0) {
            gtk_style_context_add_class(context, "success-button");
        } else if (strcmp(color, "warning") == 0) {
            gtk_style_context_add_class(context, "warning-button");
        } else if (strcmp(color, "danger") == 0) {
            gtk_style_context_add_class(context, "danger-button");
        }
    }
    
    gtk_widget_set_size_request(*button, 120, 40);
}

/**
 * 创建现代化输入框
 */
void create_modern_entry(GtkWidget **entry, const char *placeholder) {
    *entry = gtk_entry_new();
    
    GtkStyleContext *context = gtk_widget_get_style_context(*entry);
    gtk_style_context_add_class(context, "modern-entry");
    
    if (placeholder) {
        gtk_entry_set_placeholder_text(GTK_ENTRY(*entry), placeholder);
    }
    
    gtk_widget_set_size_request(*entry, 200, 35);
}

/**
 * 创建现代化标签
 */
void create_modern_label(GtkWidget **label, const char *text, const char *size) {
    *label = gtk_label_new(text);
    
    GtkStyleContext *context = gtk_widget_get_style_context(*label);
    gtk_style_context_add_class(context, "modern-label");
    
    if (size) {
        if (strcmp(size, "title") == 0) {
            gtk_style_context_add_class(context, "title");
        } else if (strcmp(size, "subtitle") == 0) {
            gtk_style_context_add_class(context, "subtitle");
        }
    }
    
    gtk_label_set_xalign(GTK_LABEL(*label), 0.5);
}
