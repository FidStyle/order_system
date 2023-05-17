#include "tools.h"
int main_form()
{
	int choice;
	system("cls");
	printf("欢迎使用餐厅点菜系统！\n请选择您的身份：\n1.顾客\n2.管理人员\n3.退出\n\n请在这里输入：");
	choice_f('n', &choice, 1, 3);
	return choice;
}