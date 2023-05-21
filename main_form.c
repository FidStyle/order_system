#include "tools.h"  // 包含自定义的头文件 tools.h

int main_form()
{
    int choice;  // 定义一个整型变量，用于存储用户的选择
    system("cls");  // 清空控制台屏幕
    printf("欢迎使用餐厅点菜系统！\n请选择您的身份：\n1.顾客\n2.管理人员\n3.退出\n\n请在这里输入：");  // 输出提示信息
    choice_f('n', &choice, 1, 3);  // 调用自定义的选择函数，获取用户的选择
    return choice;  // 返回用户的选择
}
