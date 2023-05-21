#include "tools.h"  // 包含自定义的头文件 tools.h

// 函数声明
extern int main_form();  // 显示主菜单，返回用户的选择
extern int customer_form();  // 显示顾客菜单，返回用户的选择
extern int admin_form();  // 显示管理员菜单，返回用户的选择

int main() {
    FILE* fp;  // 定义一个文件指针变量
    // 检查四个菜单文件是否存在
    if ((fp = fopen("menu//hot_dish.txt", "r")) == NULL || (fp = fopen("menu//cold_dish.txt", "r")) == NULL ||
        (fp = fopen("menu//staple_food.txt", "r")) == NULL || (fp = fopen("menu//drink.txt", "r")) == NULL)
    {
        printf("请将四个菜单txt文件放在本程序的下级目录“menu”文件夹中\n");  // 输出提示信息
        my_pause();  // 等待用户按下任意键
        return 0;  // 返回 0，结束程序
    }
    int choice;  // 定义一个整型变量，用于存储用户的选择
    do {
        choice = main_form();  // 显示主菜单，并获取用户的选择
        switch (choice) {
        case 1:system("cls"); customer_form(); break;  // 如果用户选择了 1，显示顾客菜单
        case 2:system("cls"); admin_form(); break;  // 如果用户选择了 2，显示管理员菜单
        }
    } while (choice != 3);  // 如果用户选择了 3，退出循环
    return 0;  // 返回 0，结束程序
}
