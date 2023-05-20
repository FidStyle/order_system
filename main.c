#include "tools.h" 
//函数声明 
extern int main_form();
extern int customer_form();
extern int admin_form();

int main() {
	FILE* fp;
	if ((fp = fopen("hot_dish.txt", "r")) == NULL|| (fp = fopen("cold_dish.txt", "r")) == NULL || 
		(fp = fopen("staple_food.txt", "r")) == NULL || (fp = fopen("drink.txt", "r")) == NULL)
	{
		printf("请将四个菜单txt文件与本程序放在同一目录\n");
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
