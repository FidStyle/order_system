#include "tools.h"
void gotoxy(int x, int y)
{
	COORD pos = {x, y};												// ���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // ��ȡ��׼����豸��������������ֱ�ָ���ĸ����壬����λ��
}

void getxy(int *x, int *y)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &info);
	*x = info.dwCursorPosition.X;
	*y = info.dwCursorPosition.Y; // �� x��y ��ֵ��Ϊ��ǰ���ĺ�������
}

// �Ӽ����������ݣ��س��������룬�������������
int my_num_input(char esc, int tmp_str_len, double *outputf, int *outputi)
{
	// ԭ������
	char c_input[MAX_NUM_LEN];
	int over_flag = 0;
	int max_str_len = MAX_NUM_LEN;
	max_str_len = tmp_str_len;
	memset(c_input, 0, MAX_NUM_LEN);
	int x, y;
	getxy(&x, &y);
	int x0 = x, y0 = y;
	char ch;
	int cnt = 0;
	do
	{
	start1:
		ch = getch();
		if (ch <= 0)
			getch(); // ��ֹ����del��������ȼ�λ��Windows��ӳ���VK_DELETE��VK_LEFT�������λ��ʹ��getch()�õ�����ASCII�롣
		if (ch == 27 && esc == 'y')
		{
			gotoxy(x, y);
			return 1;
		}
		else if (ch == 13)
		{ // �س���
			if (c_input[0] == '\0')
				goto start1;
			if (over_flag == 1)
			{
				gotoxy(x, y);
				printf("\n                        ");
				gotoxy(x, y);
			}
			break;
		}
		else if (ch == 8 && x > x0)
		{ // �˸��
			cnt--;
			x--;
			gotoxy(x, y);
			printf(" ");
			gotoxy(x, y);
			if (over_flag == 1)
			{
				printf("\n                        ");
				gotoxy(x, y);
			}
		}
		else if (ch == 46 || ch >= 48 && ch <= 57)
		{ // ����
			if (cnt < max_str_len)
			{
				c_input[cnt] = ch;
				printf("%c", ch);
				x++;
				cnt++;
				if (over_flag == 1)
				{
					gotoxy(x, y);
					printf("\n                        ");
					gotoxy(x, y);
				}
			}
			else
			{
				printf("\n���볤�Ȳ��ܳ���Ԥ��ֵ��");
				over_flag = 1;
				gotoxy(x, y);
			}
		}
	} while (ch != 13);
	c_input[cnt] = '\0';
	if (outputi != NULL)
	{
		int tmp;
		tmp = atoi(c_input);
		*outputi = tmp;
	}
	else if (outputf != NULL)
	{
		double tmp;
		tmp = atof(c_input);
		*outputf = tmp;
	}
	return 0;
}

int my_str_input(char esc, char *output)
{
	// ԭ������
	char c_input[MAX_STR_LEN];
	int max_str_len = MAX_STR_LEN;
	memset(c_input, 0, MAX_STR_LEN);
	int x, y;
	getxy(&x, &y);
	int x0 = x, y0 = y;
	char ch;
	int cnt = 0;
	do
	{
	start1:
		ch = getch();
		if (ch <= 0)
			getch(); // ��ֹ����del��������ȼ�λ��Windows��ӳ���VK_DELETE��VK_LEFT�������λ��ʹ��getch()�õ�����ASCII�롣
		if (ch == 27 && esc == 'y')
		{
			gotoxy(x, y);
			return 1;
		}
		else if (ch == 13)
		{ // �س���
			if (c_input[0] == '\0')
				goto start1;
			break;
		}
		else if (ch == 8 && x > x0)
		{ // �˸��
			cnt--;
			x--;
			gotoxy(x, y);
			printf(" ");
			gotoxy(x, y);
			if (x == x0 + max_str_len - 1)
			{
				printf("\n                                ");
				gotoxy(x, y);
			}
		}
		else if (ch != 8)
		{
			if (cnt < max_str_len)
			{
				c_input[cnt] = ch;
				printf("%c", ch);
				x++;
				cnt++;
			}
			else
			{
				printf("\n���볤�Ȳ��ܳ���Ԥ��ֵ��");
				gotoxy(x, y);
			}
		}
	} while (ch != 13);
	c_input[cnt] = '\0';
	strcpy(output, c_input);
	return 0;
}

int choice_f(char choice_c, int *choice, int min, int max)
{
	// �Զ��ж����볤�ȵ�ѡ����
	int tmp_len = 0, tmp_max = max;
	while (tmp_max != 0)
	{
		tmp_len++;
		tmp_max /= 10;
	}
	if (my_num_input(choice_c, tmp_len, NULL, choice))
		return 1;
	int a, a0, b, b0;
	getxy(&a0, &b0);
	int tmp_flag = 0;
	while (*choice < min || *choice > max)
	{
		if (tmp_flag == 0)
		{
			gotoxy(a0, b0);
			printf("\n����������������� : ");
			getxy(&a, &b);
			tmp_flag = 1;
		}
		gotoxy(a, b);
		for (int i = 0; i < MAX_STR_LEN; i++)
			printf(" ");
		gotoxy(a, b);
		if (my_num_input(choice_c, tmp_len, NULL, choice))
			return 1;
	}
	return 0;
}

void my_pause(void)
{
	printf("\n��������ص��ϼ��˵�");
	system("pause 1>nul 2>nul");
}