#include "tools.h"
void gotoxy(int x, int y)
{
	COORD pos = { x, y };												// 设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // 获取标准输出设备句柄，两个参数分别指定哪个窗体，具体位置
}

void getxy(int* x, int* y)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hOutput;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &info);
	*x = info.dwCursorPosition.X;
	*y = info.dwCursorPosition.Y; // 将 x、y 的值改为当前光标的横纵坐标
}

// 从键盘输入内容，回车结束输入，返回输入的内容
int my_num_input(char esc, int tmp_str_len, double* outputf, int* outputi)
{
	// 原创函数
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
			getch(); // 防止输入del、方向键等键位在Windows的映射成VK_DELETE、VK_LEFT等虚拟键位，使得getch()得到负数ASCII码。
		if (ch == 27 && esc == 'y')
		{
			gotoxy(x, y);
			return 1;
		}
		else if (ch == 13)
		{ // 回车键
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
		{ // 退格键
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
		{ // 数字
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
				printf("\n输入长度不能超出预设值！");
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

int my_str_input(char esc, char* output)
{
	// 原创函数
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
			getch(); // 防止输入del、方向键等键位在Windows的映射成VK_DELETE、VK_LEFT等虚拟键位，使得getch()得到负数ASCII码。
		if (ch == 27 && esc == 'y')
		{
			gotoxy(x, y);
			return 1;
		}
		else if (ch == 13)
		{ // 回车键
			if (c_input[0] == '\0')
				goto start1;
			break;
		}
		else if (ch == 8 && x > x0)
		{ // 退格键
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
				printf("\n输入长度不能超出预设值！");
				gotoxy(x, y);
			}
		}
	} while (ch != 13);
	c_input[cnt] = '\0';
	strcpy(output, c_input);
	return 0;
}

int choice_f(char choice_c, int* choice, int min, int max)
{
	// 自动判断输入长度的选择函数
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
			printf("\n输入错误，请重新输入 : ");
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
	printf("\n按任意键回到上级菜单");
	system("pause 1>nul 2>nul");
}
