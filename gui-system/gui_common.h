#ifndef GUI_COMMON_H
#define GUI_COMMON_H

#include <gtk/gtk.h>
#include "atm_system.h"

// GUI全局变量
extern GtkWidget *main_window;
extern GtkWidget *login_window;
extern GtkWidget *transaction_window;
extern GtkWidget *current_window;

// 样式常量
#define PRIMARY_COLOR "#2E86AB"
#define SECONDARY_COLOR "#A23B72"
#define SUCCESS_COLOR "#4CAF50"
#define ERROR_COLOR "#F44336"
#define WARNING_COLOR "#FF9800"
#define BACKGROUND_COLOR "#F5F5F5"
#define CARD_COLOR "#FFFFFF"

// 字体大小
#define TITLE_FONT_SIZE 24
#define HEADER_FONT_SIZE 18
#define BODY_FONT_SIZE 14
#define SMALL_FONT_SIZE 12

// 窗口尺寸
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define LOGIN_WIDTH 400
#define LOGIN_HEIGHT 500

// 函数声明
void gui_init();
void gui_cleanup();
void show_error_dialog(const char *message);
void show_success_dialog(const char *message);
void show_info_dialog(const char *message);
void apply_modern_style(GtkWidget *widget);
void create_modern_button(GtkWidget **button, const char *text, const char *color);
void create_modern_entry(GtkWidget **entry, const char *placeholder);
void create_modern_label(GtkWidget **label, const char *text, const char *size);
void show_main_window();
void create_login_window();
void create_transaction_window();
void on_login_clicked(GtkWidget *widget, gpointer data);
void on_exit_clicked(GtkWidget *widget, gpointer data);
void on_login_confirm_clicked(GtkWidget *widget, gpointer data);
void on_login_back_clicked(GtkWidget *widget, gpointer data);
void on_login_window_destroy(GtkWidget *widget, gpointer data);
void on_deposit_clicked(GtkWidget *widget, gpointer data);
void on_withdraw_clicked(GtkWidget *widget, gpointer data);
void on_transfer_clicked(GtkWidget *widget, gpointer data);
void on_query_clicked(GtkWidget *widget, gpointer data);
void on_change_password_clicked(GtkWidget *widget, gpointer data);
void on_logout_clicked(GtkWidget *widget, gpointer data);
void on_transaction_window_destroy(GtkWidget *widget, gpointer data);
void create_deposit_window();
void create_withdraw_window();
void create_transfer_window();
void create_query_window();
void create_change_password_window();
void on_deposit_confirm_clicked(GtkWidget *widget, gpointer data);
void on_deposit_cancel_clicked(GtkWidget *widget, gpointer data);
void on_quick_amount_clicked(GtkWidget *widget, gpointer data);
void on_quick_withdraw_clicked(GtkWidget *widget, gpointer data);
void on_withdraw_confirm_clicked(GtkWidget *widget, gpointer data);
void on_withdraw_cancel_clicked(GtkWidget *widget, gpointer data);
void on_transfer_confirm_clicked(GtkWidget *widget, gpointer data);
void on_transfer_cancel_clicked(GtkWidget *widget, gpointer data);
void on_query_close_clicked(GtkWidget *widget, gpointer data);
void on_change_password_confirm_clicked(GtkWidget *widget, gpointer data);
void on_change_password_cancel_clicked(GtkWidget *widget, gpointer data);
void update_user_info();
int verify_login(const char *card_id, const char *password);
int perform_deposit(double amount);
int perform_withdraw(double amount);
int perform_transfer(const char *to_account, double amount);
int perform_change_password(const char *new_password);
void print_deposit_receipt(double amount);
void print_withdraw_receipt(double amount);
void print_transfer_receipt(const char *to_account, double amount);
void on_print_receipt_clicked(GtkWidget *widget, gpointer data);
void on_close_receipt_clicked(GtkWidget *widget, gpointer data);

#endif
