#include "tools.h"
int main_form()
{
	int choice;
	system("cls");
	printf("��ӭʹ�ò������ϵͳ��\n��ѡ��������ݣ�\n1.�˿�\n2.������Ա\n3.�˳�\n\n�����������룺");
	choice_f('n', &choice, 1, 3);
	return choice;
}