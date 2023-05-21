#include "tools.h"  // 包含自定义的头文件 tools.h

// 变量声明
int table_no;  // 定义一个整型变量，用于存储顾客的餐台号
extern char hot_dish_filename[max_str_name_len];  // 引用全局变量 hot_dish_filename
extern char cold_dish_filename[max_str_name_len];  // 引用全局变量 cold_dish_filename
extern char staple_food_filename[max_str_name_len];  // 引用全局变量 staple_food_filename
extern char drink_filename[max_str_name_len];  // 引用全局变量 drink_filename

// 函数声明
int customer_menu();  // 菜单界面
void all_dishmenu(char* fnm);  // 打开菜单
void over_view();  // 总览
int check_bill();  // 支付订单
void order_status();  // 订单状态
void page_controller(dish_menu*, int);  // 菜单分页
int display_menu(dish_menu*, int, int);  // 显示菜单信息
int create_order(dish_menu*, int, int);  // 生成订单

// 显示顾客菜单界面，输入餐台号
int customer_form()
{
    system("cls");  // 清空控制台屏幕
    printf("----------------------\n·顾客系统打开成功!\n·返回上级菜单请按Esc\n----------------------\n\n请输入您的餐台号：");  // 输出提示信息
    int choice;  // 定义一个整型变量，用于存储用户的选择
    // 调用函数获取用户输入的餐台号，并检查是否按下了 ESC 键
    if (choice_f('y', &table_no, 1, 999))//'y'代表可以按ESC返回上级菜单
        return 0;  // 如果用户按下 ESC 键，则返回上级菜单
    // 打开菜单界面
    do
    {
        // 调用函数显示菜单界面并获取用户的选择
        choice = customer_menu();
        switch (choice)
        {
        case 1:
            all_dishmenu(hot_dish_filename);  // 打开热菜菜单
            break;
        case 2:
            all_dishmenu(cold_dish_filename);  // 打开凉菜菜单
            break;
        case 3:
            all_dishmenu(staple_food_filename);  // 打开主食菜单
            break;
        case 4:
            all_dishmenu(drink_filename);  // 打开饮品菜单
            break;
        case 5:
            over_view();  // 显示总览信息
            break;
        case 6:
            check_bill();  // 支付订单
            break;
        case 7:
            order_status();  // 显示订单状态
            break;
        default:
            break;
        }
    } while (choice != 8);  // 如果用户选择的不是退出，则继续循环
    return 0;  // 返回 0 表示正常结束
}

// 顾客菜单，获取用户的选择
int customer_menu()
{
    system("cls");  // 清空控制台屏幕
    int choice;  // 定义一个整型变量，用于存储用户的选择
    printf("--------------------------\n·餐台：%d 请选择您的操作\n·返回上级菜单请按Esc\n--------------------------\n\n1.热菜\n2.凉菜\n3.主食\n4.饮品\n5.总览\n6.结账\n7.订单状态\n\n在这里输入:", table_no);  // 输出提示信息
    // 调用函数获取用户输入的选择，并检查是否按下了 ESC 键
    if (choice_f('y', &choice, 1, 7))//'y'代表可以按ESC返回上级菜单
        return 8;  // 如果用户按下 ESC 键，则返回上级菜单
    return choice;  // 返回用户的选择
}

// 显示所有菜品的菜单
void all_dishmenu(char* fnm)
{
    dish_menu all_dishmenu[MAX_LENGTH];  // 定义一个结构体数组，用于存储菜单信息
    int cnt = 0;  // 定义一个整型变量，用于记录菜品实际数量
    // 打开指定的菜单文件并读取数据
    FILE* fp;
    char filename[max_str_name_len];
    strcpy(filename, fnm);
    fp = fopen(filename, "r");
    while (fscanf(fp, "%d %s %lf %d", &all_dishmenu[cnt].no,
        all_dishmenu[cnt].dish_name, &all_dishmenu[cnt].dish_price,
        &all_dishmenu[cnt].type) == 4)
    {
        cnt++;
    }
    fclose(fp);  // 关闭文件指针
    // 进入菜单分页控制函数
    page_controller(all_dishmenu, cnt);
}

// 显示订单总览信息
void over_view()
{
    system("cls");  // 清空控制台屏幕
    int cnt = 0;  // 定义一个整型变量，用于记录订单中的菜品数量
    dish_order my_order[MAX_LENGTH];  // 定义一个结构体数组，用于存储订单信息
    char fstr[50] = { '\0' };  // 定义一个字符串数组，用于存储订单文件名
    sprintf(fstr, "order//%d.txt", table_no);  // 根据餐台号生成订单文件名
    // 判断订单文件是否存在，如果不存在则提示用户还未下单
    FILE* fp;
    fp = fopen(fstr, "r");
    if (fp == NULL)
    {
        printf("您还没有下单！\n");
        my_pause();  // 暂停程序运行，等待用户操作
        return;
    }
    else
    {   // 从文件中获取订单内容
        int flag_0; // 提取标志位，防止误读
        fscanf(fp, "%d", &flag_0);
        // 读出文件信息
        while (fscanf(fp, "%d %s %lf %d %d", &my_order[cnt].no,
            my_order[cnt].dish_name, &my_order[cnt].dish_price,
            &my_order[cnt].type, &my_order[cnt].nums) == 5)
        {
            cnt++;
        }
    }
    fclose(fp);  // 关闭文件指针
    // 订单信息读取结束后显示
    printf("序号 菜品编号     菜品名称       单价   数量     小计\n");
    for (int i = 0; i < cnt; i++)
        printf("%d\t %d\t  %s\t %.2lf\t %d\t %.2lf\n", i + 1, my_order[i].no, my_order[i].dish_name, my_order[i].dish_price, my_order[i].nums, my_order[i].dish_price * my_order[i].nums);
    my_pause();  // 暂停程序运行，等待用户操作
}

// 检查订单并支付
int check_bill()
{
    system("cls");  //清屏
    double account = 0;  //总价
    int cnt = 0;  //菜品数量
    dish_order my_order[MAX_LENGTH];  //定义订单结构体数组
    char fstr[50] = { '\0' };  //定义文件名
    sprintf(fstr, "order//%d.txt", table_no);  //根据桌号生成订单文件名
    FILE* fp;  //定义文件指针
    fp = fopen(fstr, "r");  //以只读方式打开文件
    if (fp == NULL)  //如果文件不存在
    {
        printf("您还没有下单！\n");
        my_pause();  //暂停，等待用户操作
        return 0;
    }
    else
    {
        int flag_0;  //定义标志位，用于判断订单状态
        fscanf(fp, "%d", &flag_0);  //从文件中读取标志位
        if (flag_0 != 1)  //如果标志位不为1，即订单已经支付完成
        {
            printf("您已完成支付，请稍候为您上餐\n");
            my_pause();  //暂停，等待用户操作
            return 0;
        }
        // 读出文件信息
        while (fscanf(fp, "%d %s %lf %d %d", &my_order[cnt].no,
            my_order[cnt].dish_name, &my_order[cnt].dish_price,
            &my_order[cnt].type, &my_order[cnt].nums) == 5)  //从文件中读取订单信息
        {
            account += my_order[cnt].dish_price * my_order[cnt].nums;  //计算总价
            cnt++;  //统计菜品数量
        }
    }
    fclose(fp);
    printf("---------------------\n·返回上级菜单请按Esc\n·您需要支付：%.2lf元\n---------------------\n·请支付:", account);
    double pay;  //定义付款金额
    if (my_num_input('y', MAX_NUM_LEN, &pay, NULL))//'y'代表可以按ESC返回上级菜单
        return 0;
    printf("\n");
    while (pay < account)  //如果付款金额不足
    {
        printf("客官，钱还不够！\n客官再给点：");
        if (my_num_input('y', MAX_NUM_LEN, &pay, NULL))//'y'代表可以按ESC返回上级菜单
            return 0;
    }
    if (pay > account)  //如果付款金额超过总价
        printf("\n客官大气，找您%.2lf元\n", pay - account);
    printf("客官请稍等，小的这就通知老板给您上菜\n");
    fp = fopen(fstr, "w");  //以写入方式打开文件
    fprintf(fp, "%d\n", 2); // 设置标志位为2，为支付完成，重新录入文件
    for (int i = 0; i < cnt; i++)
        fprintf(fp, "%d %s %lf %d %d\n", my_order[i].no, my_order[i].dish_name, my_order[i].dish_price, my_order[i].type, my_order[i].nums);  //将订单信息写入文件
    fclose(fp);
    my_pause();  //暂停，等待用户操作
    return 0;
}

// 查询订单状态
void order_status()
{
    system("cls");  //清屏
    char fstr[50] = { '\0' };  //定义文件名
    sprintf(fstr, "order//%d.txt", table_no); // 根据桌号生成订单文件名
    FILE* fp;  //定义文件指针
    fp = fopen(fstr, "r");  //以只读方式打开文件
    if (fp == NULL)  //如果文件不存在
    {
        printf("您还没有下单！\n");
        my_pause();  //暂停，等待用户操作
        return;
    }
    int flag_0;  //定义标志位，用于判断订单状态
    fscanf(fp, "%d", &flag_0);  //从文件中读取标志位
    fclose(fp);
    switch (flag_0)  //根据标志位输出订单状态
    {
    case 1:
        printf("您已点菜，可以移步去支付哟！\n");
        break;
    case 2:
        printf("您已支付完成，老板大大正在确认中！\n");
        break;
    case 3:
        printf("正在为您出餐，稍等！\n");
        break;
    case 4:
        printf("祝您用餐愉快，欢迎下次光临！\n");
        break;
    default:
        break;
    }
    my_pause();  //暂停，等待用户操作
}

// 创建订单
int create_order(dish_menu* dm, int mode, int count)
{
    int cnt = 0;  //菜品数量
    dish_order new_order[MAX_LENGTH];  //定义订单结构体数组
    char filename[max_str_name_len];  //定义文件名
    fnm_switch(mode, filename);  //根据mode生成文件名
    FILE* fp;  //定义文件指针
    fp = fopen(filename, "r");  //以只读方式打开文件
    int choice;  //定义选项
    int temp_no;  //定义临时变量，存储菜品编号
    int temp_num;  //定义临时变量，存储菜品数量
    do
    {
        printf("\n请输入菜品编号：");
        if (my_num_input('y', MAX_NUM_LEN, NULL, &temp_no))//'y'代表可以按ESC返回上级菜单
            return 0;
        // 检测菜品编号是否存在
        int flag = 0;  //定义标志位，用于判断菜品编号是否存在
        do
        {
            int i;
            for (i = 0; i < count; i++)
            {
                if (dm[i].no == temp_no)
                {
                    flag = 1;  //菜品编号存在
                    new_order[cnt].no = dm[i].no;
                    strcpy(new_order[cnt].dish_name, dm[i].dish_name);
                    new_order[cnt].dish_price = dm[i].dish_price;
                    new_order[cnt].type = dm[i].type;
                    break;
                }
            }

            if (flag == 0)  //菜品编号不存在
            {
                printf("\n输入的菜品编号不存在，请输入正确的菜品编号：");
                if (my_num_input('y', MAX_NUM_LEN, NULL, &temp_no))//'y'代表可以按ESC返回上级菜单
                    return 0;
            }
        } while (flag == 0);
        // 菜品编号存在时输入点菜数量
        printf("\n请输入点菜数量：");
        if (choice_f('y', &temp_num, 1, 999))//'y'代表可以按ESC返回上级菜单
            return 0;
        new_order[cnt].nums = temp_num;  //将菜品数量存入订单结构体中
        cnt++;  //统计菜品数量
        // 判断是否继续点菜
        printf("\n是否继续点菜？ 1.是 2.否 ：\n");
        if (choice_f('y', &choice, 1, 2))//'y'代表可以按ESC返回上级菜单
            return 0;
    } while (choice != 2);
    fclose(fp);
    char fstr[50] = { '\0' };  //定义文件名
    sprintf(fstr, "order//%d.txt", table_no);  //根据桌号生成订单文件名
    fp = fopen(fstr, "r");  //以只读方式打开文件
    if (fp == NULL)  //如果文件不存在
    {
        fp = fopen(fstr, "w");  //以写入方式创建文件
        fprintf(fp, "%d\n", 1);  //设置标志位为1
    }
    fclose(fp);
    fp = fopen(fstr, "a");  //以追加方式打开文件
    int i = 0;
    for (i = 0; i < cnt; i++)
        fprintf(fp, "%d %s %lf %d %d\n", new_order[i].no, new_order[i].dish_name, new_order[i].dish_price, new_order[i].type, new_order[i].nums);//将订单信息写入文件
    fclose(fp);
    return 0;
}

// 定义了一个显示菜单的函数，传入菜单指针和显示范围的起始和结束位置
int display_menu(dish_menu* dm, int start, int end)
{
    int i;
    int choice;
    system("cls"); // 清屏
    // 显示菜单选项
    printf("----------------------------------------------------------\n·点餐页面打开成功，请选择选项\n·返回上级菜单请按Esc\n----------------------------------------------------------\n序号  菜品编号    菜品名称      价格\n");
    for (i = start; i < end; i++)
        printf(" %d\t %d\t  %s\t%.2lf\n", i + 1, dm[i].no, dm[i].dish_name, dm[i].dish_price);
    printf("----------------------------------------------------------\n");
    // 添加控制逻辑，防止误判
    if (start == 0 && end - start < RECORD_NUM)
    {
        // 显示选项：点菜和退出
        printf("3.点菜\n");
        printf("4.退出\n");
        if (choice_f('y', &choice, 3, 4))//'y'代表可以按ESC返回上级菜单
            return 4;
    }
    else if (start == 0)
    {
        // 显示选项：下一页、点菜和退出
        printf("2.下一页\n");
        printf("3.点菜\n");
        printf("4.退出\n");
        if (choice_f('y', &choice, 2, 4))//'y'代表可以按ESC返回上级菜单
            return 4;
    }
    else if (end - start != RECORD_NUM)
    {
        // 显示选项：上一页、点菜和退出
        printf("1.上一页\n");
        printf("3.点菜\n");
        printf("4.退出\n");
        if (my_num_input('y', 1, NULL, &choice))//'y'代表可以按ESC返回上级菜单
            return 1;
        int a, a0, b, b0;
        getxy(&a0, &b0);
        int tmp_flag = 0;
        while (choice < 1 || choice > 4 || choice == 2)
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
            if (my_num_input('y', 1, NULL, &choice))//'y'代表可以按ESC返回上级菜单
                return 4;
        }
    }
    else
    { // 正常显示
        // 显示选项：上一页、下一页、点菜和退出
        printf("1.上一页\n");
        printf("2.下一页\n");
        printf("3.点菜\n");
        printf("4.退出\n");
        if (choice_f('y', &choice, 1, 4))//'y'代表可以按ESC返回上级菜单
            return 4;
    }
    return choice; // 返回用户选择的菜单项编号
}

// 定义了一个分页控制函数，传入菜单指针和菜单项数量
void page_controller(dish_menu* dm, int cnt)
{
    int record_num = RECORD_NUM; // 设置每页显示的菜品数量
    // 设定部分显示相关变量
    int base = 0;
    int start, end;
    start = base;
    end = start + record_num > cnt ? cnt : start + record_num;
    int choice;
    do
    {
        choice = display_menu(dm, start, end); // 显示菜单，并获取用户选择的菜单项
        switch (choice)
        {
        case 1:
        {
            if (end - start < record_num) // 如果当前页不足每页显示数量
                end = end - (end - start); // 直接返回上一页
            else
                end -= record_num; // 否则显示上一页
            start -= record_num;
            break;
        }
        case 2:
        {
            start += record_num; // 显示下一页
            end = start + record_num > cnt ? cnt : start + record_num; // 判断是否已到最后一页
            break;
        }
        case 3:
        {
            int mode = dm[0].type;
            create_order(dm, mode, cnt); // 创建订单
            break;
        }
        case 4:
            break;
        }
    } while (choice != 4); // 如果用户选择退出，则结束循环
}
