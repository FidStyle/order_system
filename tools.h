#ifndef TOOL_H
#define TOOL_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <io.h>
#include <string.h>
#include <conio.h>

#define RECORD_NUM 8						   // 在这里设定每页显示的菜品数量
#define MAX_LENGTH 100						   // 最大结构体数组宽度
#define MAX_NUM_LEN 6						   // 最大数字输入长度
#define MAX_STR_LEN 20						   // 最大字符串输入长度
#define max_str_name_len 30					   // 菜品名字最大长度
#define input_len 3							   // 假设有999张桌子
#define MAX_STR_TABLE_LEN (pow(10, input_len)) // 假设有999张桌子

// 菜单数据结构
typedef struct a
{
	int no; // 编号
	char dish_name[20];
	double dish_price;
	int type; // 种类 1-热菜 2-凉菜  3-主食 4- 饮品
} dish_menu;

typedef struct b
{
	int no;
	char dish_name[20];
	double dish_price;
	int type;
	int nums; // 点菜时的数量
} dish_order;

// 函数声明
void gotoxy(int x, int y);
void getxy(int* x, int* y);
int my_num_input(char esc, int tmp_str_len, double* outputf, int* outputi);
int my_str_input(char esc, char* output);
int choice_f(char choice_c, int* choice, int min, int max); // 自动判断输入长度的选择函数
void my_pause(void);
#endif
