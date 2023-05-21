// 该文件为工具函数文件，包含了一些通用的函数

#include "tools.h" // 包含头文件

// 设置光标位置
void gotoxy(int x, int y)
{
	COORD pos = { x, y }; // 定义 COORD 结构体变量，表示光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); // 设置光标位置，使用 Windows API 函数
}

// 获取光标位置
void getxy(int* x, int* y)
{
	CONSOLE_SCREEN_BUFFER_INFO info; // 定义 CONSOLE_SCREEN_BUFFER_INFO 结构体变量，表示控制台屏幕缓冲区信息
	HANDLE hOutput; // 定义 HANDLE 类型变量，表示标准输出设备句柄
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
	GetConsoleScreenBufferInfo(hOutput, &info); // 获取控制台屏幕缓冲区信息，使用 Windows API 函数
	*x = info.dwCursorPosition.X; // 获取光标的横坐标
	*y = info.dwCursorPosition.Y; // 获取光标的纵坐标
}

// 从键盘输入数字，回车结束输入，返回输入的内容
int my_num_input(char esc, int tmp_str_len, double* outputf, int* outputi)
{
	// 自定义函数
	char c_input[MAX_NUM_LEN + 1];
	int over_flag = 0;
	int max_str_len = MAX_NUM_LEN;
	max_str_len = tmp_str_len;
	memset(c_input, 0, MAX_NUM_LEN + 1); // 将 c_input 数组清零
	int x, y;
	getxy(&x, &y); // 获取光标位置
	int x0 = x, y0 = y;
	char ch;
	int cnt = 0;
	do
	{
	start1:
		ch = getch(); // 使用 getch() 函数获取用户输入的字符
		if (ch <= 0)
			getch(); // 防止输入 del、方向键等键位在 Windows 的映射成 VK_DELETE、VK_LEFT 等虚拟键位，使得 getch() 得到负数 ASCII 码。
		if (ch == 27 && esc == 'y') // 如果输入了 ESC 键，并且 esc 参数为 'y'，则退出输入
		{
			gotoxy(x, y);
			return 1;
		}
		else if (ch == 13)
		{ // 回车键
			if (c_input[0] == '\0') // 如果输入为空，则重新输入
				goto start1;
			if (over_flag == 1) // 如果已经超出最大输入长度，则清空多余的字符
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
	} while (ch != 13); // 当输入回车时结束输入
	c_input[cnt] = '\0'; // 将 c_input 数组最后一位设置为 '\0'，表示字符串结束
	if (outputi != NULL) // 如果 outputi 不为 NULL，则将输入的字符串转换成整型，并赋值给 outputi
	{
		int tmp;
		tmp = atoi(c_input);
		*outputi = tmp;
	}
	else if (outputf != NULL) // 如果 outputf 不为 NULL，则将输入的字符串转换成浮点型，并赋值给 outputf
	{
		double tmp;
		tmp = atof(c_input);
		*outputf = tmp;
	}
	return 0;
}

// 从键盘输入字符串，回车结束输入，返回输入的内容
int my_str_input(char esc, char* output)
{
	// 自定义函数
	char c_input[MAX_STR_LEN + 2];
	int over_flag = 0;
	int max_str_len = MAX_STR_LEN;
	memset(c_input, 0, MAX_STR_LEN + 2); // 将 c_input 数组清零
	int x, y;
	getxy(&x, &y); // 获取光标位置
	int x0 = x, y0 = y;
	char ch, ch_tmp;
	int cnt = 0, tmp_chinese = 0;
	do
	{
	start1:
		tmp_chinese = 0;
		ch = getch(); // 使用 getch() 函数获取用户输入的字符
		if (ch <= 0) {
			ch_tmp = getch(); // 检测是 VK_DELETE、VK_LEFT 等虚拟键位，还是中文。
			if (ch_tmp < 0) {
				tmp_chinese = 1; // 确认输入的是中文，连续两个字节最高位均为 1
				if (cnt < max_str_len)
				{
					c_input[cnt] = ch;
					cnt++;
					c_input[cnt] = ch_tmp;
					printf("%c%c", ch, ch_tmp);
					x++;
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
		}

		if (ch == 27 && esc == 'y') // 如果输入了 ESC 键，并且 esc 参数为 'y'，则退出输入
		{
			gotoxy(x, y);
			return 1;
		}
		else if (ch == 13)
		{ // 回车键
			if (c_input[0] == '\0') // 如果输入为空，则重新输入
				goto start1;
			if (over_flag == 1) // 如果已经超出最大输入长度，则清空多余的字符
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
			if (c_input[cnt] < 0) {
				cnt--;
				x--;
			}
			gotoxy(x, y);
			printf(" ");
			if (c_input[cnt] < 0)printf(" ");
			gotoxy(x, y);
			if (over_flag == 1)
			{
				printf("\n                        ");
				gotoxy(x, y);
			}
		}
		else if (ch > 0 && ch != 8 && tmp_chinese == 0) // 输入非中文
		{
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
	} while (ch != 13); // 当输入回车时结束输入
	c_input[cnt] = '\0'; // 将 c_input 数组最后一位设置为 '\0'，表示字符串结束
	strcpy(output, c_input); // 将输入的字符串复制到 output 中
	return 0;
}

int choice_f(char choice_c, int* choice, int min, int max)
{
	// 自动判断输入长度的选择函数
	int tmp_len = 0, tmp_max = max;  // 定义变量，并初始化
	while (tmp_max != 0)  // 循环计算 max 的位数
	{
		tmp_len++;
		tmp_max /= 10;
	}
	if (my_num_input(choice_c, tmp_len, NULL, choice))  // 获取用户输入的数字，并判断是否输入了 ESC 键
		return 1;  // 如果输入了 ESC 键，返回 1
	int a, a0, b, b0;
	getxy(&a0, &b0);  // 获取光标当前位置的坐标
	int tmp_flag = 0;  // 定义变量，表示是否需要重新输入
	while (*choice < min || *choice > max)  // 输错则循环，直到用户输入的数字在 min 和 max 之间
	{
		if (tmp_flag == 0)  // 如果需要重新输入
		{
			gotoxy(a0, b0);  // 将光标移动到输入错误的提示信息的位置
			printf("\n输入错误，请重新输入 : ");
			getxy(&a, &b);
			tmp_flag = 1;  // 置标志位为 1，表示已经重新输入过一次
		}
		gotoxy(a, b);  // 将光标移动到用户输入的数字的位置
		for (int i = 0; i < MAX_STR_LEN; i++)  // 循环清空该位置上的字符
			printf(" ");
		gotoxy(a, b);  // 再将光标移动到用户输入的数字的位置
		if (my_num_input(choice_c, tmp_len, NULL, choice))  // 获取用户输入的数字，并判断是否输入了 ESC 键
			return 1;  // 如果输入了 ESC 键，返回 1
	}
	return 0;  // 返回 0，表示输入正确
}

void my_pause(void)
{
	printf("\n按任意键返回");  // 输出提示信息
	system("pause 1>nul 2>nul");  // 等待用户按下任意键
}

void fnm_switch(int type, char* filename)
{
	extern char hot_dish_filename[max_str_name_len];  // 引用外部变量
	extern char cold_dish_filename[max_str_name_len];  // 引用外部变量
	extern char staple_food_filename[max_str_name_len];  // 引用外部变量
	extern char drink_filename[max_str_name_len];  // 引用外部变量
	switch (type)  // 根据 type 的值进行不同的操作
	{
	case 1:
		strcpy(filename, hot_dish_filename);  // 将 hot_dish_filename 的值复制到 filename 中
		break;
	case 2:
		strcpy(filename, cold_dish_filename);  // 将 cold_dish_filename 的值复制到 filename 中
		break;
	case 3:
		strcpy(filename, staple_food_filename);  // 将 staple_food_filename 的值复制到 filename 中
		break;
	case 4:
		strcpy(filename, drink_filename);  // 将 drink_filename 的值复制到 filename 中
		break;
	}
}
