#include "tools.h" 
//函数声明 
extern int main_form();
extern int customer_form();
extern int admin_form();

int main() {
	FILE* fp;
	if ((fp = fopen("menu//hot_dish.txt", "r")) == NULL|| (fp = fopen("menu//cold_dish.txt", "r")) == NULL || 
		(fp = fopen("menu//staple_food.txt", "r")) == NULL || (fp = fopen("menu//drink.txt", "r")) == NULL)
	{
		printf("请将四个菜单txt文件放在本程序的下级目录“menu”文件夹中\n");
		my_pause();
		return 0;
	}
	int choice;
	do {
		choice = main_form();
		switch (choice) {
		case 1:system("cls"); customer_form(); break;
		case 2:system("cls"); admin_form(); break;
		}
	} while (choice != 3);
	return 0;
}
