#ifndef TOOL_H
#define TOOL_H

#include <stdio.h>              // 标准输入输出函数库
#include <stdlib.h>             // 标准库函数库
#include <math.h>               // 数学函数库
#include <windows.h>            //  Windows API 函数库
#include <io.h>                 // 输入输出函数库
#include <string.h>             // 字符串处理函数库
#include <conio.h>              // 控制台输入输出函数库

#define RECORD_NUM 8                                // 每页显示的菜品数量
#define MAX_LENGTH 100                              // 最大结构体数组宽度
#define MAX_NUM_LEN 6                               // 最大数字输入长度
#define MAX_STR_LEN 20                              // 最大字符串输入长度
#define max_str_name_len 30                         // 菜品名字最大长度
#define input_len 3                                 // 输入长度
#define MAX_STR_TABLE_LEN (pow(10, input_len))      // 最大桌子数量

// 菜单数据结构
typedef struct a
{
    int no;  // 编号
    char dish_name[20];  // 菜品名字
    double dish_price;  // 菜品价格
    int type;  // 种类 1-热菜 2-凉菜  3-主食 4- 饮品
} dish_menu;

typedef struct b
{
    int no;  // 编号
    char dish_name[20];  // 菜品名字
    double dish_price;  // 菜品价格
    int type;  // 种类 1-热菜 2-凉菜  3-主食 4- 饮品
    int nums;  // 点菜时的数量
} dish_order;

// 函数声明
void gotoxy(int x, int y);  // 将光标移动到指定的坐标位置
void getxy(int* x, int* y);  // 获取光标当前位置的坐标
int my_num_input(char esc, int tmp_str_len, double* outputf, int* outputi);  // 获取用户输入的数字，并判断是否输入了 ESC 键
int my_str_input(char esc, char* output);  // 获取用户输入的字符串，并判断是否输入了 ESC 键
int choice_f(char choice_c, int* choice, int min, int max);  // 自动判断输入长度的选择函数
void my_pause(void);  // 输出提示信息，等待用户按下任意键
void fnm_switch(int type, char* filename);  // 根据 type 的值选择不同的文件名

#endif  // 结束条件编译指令
