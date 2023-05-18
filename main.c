#include "tools.h" 
//函数声明 
extern int main_form();
extern int customer_form();
extern int admin_form();

int main() {
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
