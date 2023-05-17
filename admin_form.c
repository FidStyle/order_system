#include "tools.h"
// 预置密码
#define PASSWORD "123456"
// 定义常量
#define max_str_pw_len 15 // 密码最大长度
// 变量声明
char pw[max_str_pw_len] = PASSWORD;
// 部分全局变量
char hot_dish_filename[max_str_name_len] = "hot_dish.txt";
char cold_dish_filename[max_str_name_len] = "cold_dish.txt";
char staple_food_filename[max_str_name_len] = "staple_food.txt";
char drink_filename[max_str_name_len] = "drink.txt";
// 函数声明
int input_password(char pw_input[], int wrong_time); // 输入密码
int check_password(char pw_input[]);                 // 密码检测
int admin_menu();                                    // 管理员菜单
int order_check();                                   // 订单确认
int order_complete();                                // 完成订单
void income_check();                                 // 查看营业额
int add_dish();                                      // 添加菜品
int del_dish();                                      // 删除菜品
int price_adjust();                                  // 价格调整

int admin_form()
{
    system("cls");
    printf("----------------------\n·管理员系统打开成功!\n·返回上级菜单请按Esc\n----------------------\n\n");
    int choice;
    char pw_input[max_str_pw_len];
    printf("·请在这里输入后台密码:\n");
    int wrong_time = 0;
    if (input_password(pw_input, wrong_time))
        return 0;
    int flag;
    do
    {
        flag = check_password(pw_input);
        if (flag != 0)
        {
            wrong_time++;
            system("cls");
            printf("----------------------\n·管理员系统打开成功!\n·返回上级菜单请按Esc\n----------------------\n\n");
            if (wrong_time != 0)
                printf("·后台密码输入错误，请重新输入:");
            else
                printf("·请在这里输入后台密码:\n");
            wrong_time = 0;
            if (input_password(pw_input, wrong_time))
                return 0;
        }
        else
        {
            system("cls");
            printf("----------------------\n·管理员系统打开成功!\n·返回上级菜单请按Esc\n----------------------\n\n·输入正确！欢迎管理员！\n");
            for (int i = 0; i < 3; i++)
            {
                Sleep(400);
                printf(".");
            }
        }
    } while (flag != 0); // strcmp运算符在同字符长度会输出-1,0,1
    do
    {
        choice = admin_menu();
        switch (choice)
        {
        case 1:
            order_check();
            break;
        case 2:
            order_complete();
            break;
        case 3:
            income_check();
            break;
        case 4:
            add_dish();
            break;
        case 5:
            del_dish();
            break;
        case 6:
            price_adjust();
            break;
        default:
            break;
        }
    } while (choice != 7);
}

int input_password(char pw_input[], int wrong_time)
{
    memset(pw_input, 0, max_str_pw_len); // 清空字符串
    int x, y;
    x = 0;
    y = 6 + wrong_time;
    gotoxy(x, y);
    char ch;
    int cnt = 0;
    do
    {
        ch = getch();
        if (ch <= 0)
            getch(); // 防止输入del、方向键等键位在Windows的映射成VK_DELETE、VK_LEFT等虚拟键位，使得getch()得到负数ASCII码。
        if (ch == 27)
        {
            gotoxy(x, y);
            system("cls");
            printf("确认退出请按y，或按其余任意键留在此页");
            ch = getch();
            if (ch == 'y' || ch == 'Y')
                return 1; // 返回到if函数，执行if(1)退出密码输入界面，返回上级菜单
            else
                break; // 用户取消退出，重新回到密码输入界面
        }
        else if (ch == 13)
            break; // 回车键
        else if (ch == 8 && x > 0)
        { // 退格键
            cnt--;
            x--;
            gotoxy(x, y);
            printf(" ");
            gotoxy(x, y);
            if (x == max_str_pw_len - 1)
            {
                printf("\n                                ");
                gotoxy(x, y);
            }
        }
        else if (ch >= 32 && ch <= 126)
        { // 普通字符
            if (cnt < max_str_pw_len)
            {
                pw_input[cnt] = ch;
                printf("*");
                x++;
                cnt++;
            }
            else
            {
                printf("\n密码长度超出预设内存，请退格。");
                gotoxy(x, y);
            }
        }
    } while (ch != 13);
    pw_input[cnt] = '\0';
    return 0;
}

int check_password(char pw_input[])
{
    return strcmp(pw_input, pw);
}

int admin_menu()
{
    system("cls");
    int choice;
    printf("--------------------------\n·请选择您的操作\n·返回上级菜单请按Esc\n--------------------------\n\n1.确认顾客订单\n2.完成顾客订单\n3.查看今日营业额\n4.添加菜品\n5.删除菜品\n6.修改价格\n\n在这里输入:");
    // printf("7.返回上级菜单\n");
    if (choice_f('y', &choice, 1, 6))
        return 7;
    return choice;
}

int order_check()
{
    system("cls");
    int tn = 1;
    int flag = 0;
    // 根据桌号检索文件，生成文件名
    for (tn = 1; tn <= MAX_STR_TABLE_LEN; tn++)
    {
        char fstr[50] = {'\0'};
        sprintf(fstr, "order//%d.txt", tn);
        FILE *fp;
        fp = fopen(fstr, "r");
        if (fp == NULL)
            continue;
        else
        {
            int flag_temp;
            fscanf(fp, "%d", &flag_temp);
            fclose(fp);
            if (flag_temp == 2)
            {
                flag = 1;
                printf("\n桌号:%d 已完成支付！\n是否确认订单？ 1.是 2.否\n", tn);
                int choice;
                choice_f('n', &choice, 1, 2);
                // 如果确定订单则置标志位为 3
                if (choice == 1)
                {
                    fp = fopen(fstr, "r+");
                    fseek(fp, 0, SEEK_SET);
                    fprintf(fp, "%d", 3);
                    fclose(fp);
                    printf("桌号:%d的订单已确认成功！\n", tn);
                }
            }
        }
    }
    if (flag == 0)
        printf("暂无订单需要确认！\n");
    my_pause();
}

int order_complete()
{
    system("cls");
    int tn = 1;
    int flag = 0;
    // 根据桌号检索文件，生成文件名
    for (tn = 1; tn <= MAX_STR_TABLE_LEN; tn++)
    {
        char fstr[50] = {'\0'};
        sprintf(fstr, "order//%d.txt", tn);
        FILE *fp;
        fp = fopen(fstr, "r");
        if (fp == NULL)
            continue;
        else
        {
            int flag_temp;
            fscanf(fp, "%d", &flag_temp);
            fclose(fp);
            if (flag_temp == 3)
            {
                flag = 1;
                printf("桌号:%d 已完成确认，出餐结束后可选择完成订单！\n是否确认完成订单？ 1.是 2.否\n", tn);
                int choice;
                choice_f('n', &choice, 1, 2);
                // 如果完成订单则置标志位为 4
                if (choice == 1)
                {
                    fp = fopen(fstr, "r+");
                    fseek(fp, 0, SEEK_SET);
                    fprintf(fp, "%d", 4);
                    fclose(fp);

                    printf("桌号:%d的订单已完成！\n", tn);
                }
            }
        }
    }
    if (flag == 0)
        printf("暂无订单可以完结！\n");
    my_pause();
}

void income_check()
{
    // 打开所有订单文件，计算所有完结订单的收入
    system("cls");
    int tn = 1;
    double account = 0;
    double account_hot_dish = 0;
    double account_cold_dish = 0;
    double account_staple_food = 0;
    double account_drink = 0;
    // 根据桌号检索文件，生成文件名
    for (tn = 1; tn <= MAX_STR_TABLE_LEN; tn++)
    {
        char str[5];
        char fstr[50] = {'\0'};
        sprintf(fstr, "order//%d.txt", tn);
        FILE *fp;
        fp = fopen(fstr, "r");
        if (fp == NULL)
            continue;
        else
        {
            int flag_temp;
            fscanf(fp, "%d", &flag_temp);
            if (flag_temp == 4)
            {
                // 读取该文件的信息，并计算营业额
                int no;
                int type;
                char dish_name[max_str_name_len];
                int nums;
                double price;
                while (!feof(fp))
                {
                    fscanf(fp, "%d %s %lf %d %d", &no, dish_name, &price, &type, &nums);
                    account += price * nums;
                    switch (type)
                    {
                    case 1:
                        account_hot_dish += price * nums;
                        break;
                    case 2:
                        account_cold_dish += price * nums;
                        break;
                    case 3:
                        account_staple_food += price * nums;
                        break;
                    case 4:
                        account_drink += price * nums;
                        break;
                    }
                }
            }
        }
        fclose(fp);
    }
    printf("总收入:%.2lf\n热菜收入:%.2lf\n凉菜收入:%.2lf\n主食收入:%.2lf\n饮品收入:%.2lf\n", account, account_hot_dish, account_cold_dish, account_staple_food, account_drink);
    my_pause();
}

int add_dish()
{
    FILE *fp;
    int choice;
    do
    {
        dish_menu new_dish;
        system("cls");
        printf("-------------------------\n·添加菜品界面打开成功!\n·返回上级菜单请按Esc\n-------------------------\n\n");
        printf("\n请输入菜品编号：");
        if (my_num_input('y', 2, NULL, &new_dish.no))
            return 0;
        printf("\n请输入菜品名称：");
        int aa, bb;
        getxy(&aa, &bb);
        printf("                   ");
        gotoxy(aa, bb);
        if (my_str_input('y', new_dish.dish_name))
            return 0;
        printf("\n请输入菜品价格：");
        if (my_num_input('y', MAX_STR_LEN, NULL, &new_dish.dish_price))
            return 0;
        printf("\n请输入菜品种类：");
        if (my_num_input('y', 1, NULL, &new_dish.type))
            return 0;
        char filename[max_str_name_len] = {'\0'};
        switch (new_dish.type)
        {
        case 1:
            strcpy(filename, hot_dish_filename);
            break;
        case 2:
            strcpy(filename, cold_dish_filename);
            break;
        case 3:
            strcpy(filename, staple_food_filename);
            break;
        case 4:
            strcpy(filename, drink_filename);
            break;
        }
        fp = fopen(filename, "a");
        fprintf(fp, "%d\n", new_dish.no);
        fprintf(fp, "%s\n", new_dish.dish_name);
        fprintf(fp, "%lf\n", new_dish.dish_price);
        fprintf(fp, "%d\n", new_dish.type);
        fclose(fp);
        printf("\n\n是否继续添加菜品：\n");
        printf("1.是\n");
        printf("2.否\n");
        if (choice_f('y', &choice, 1, 2))
            return 0;
    } while (choice != 2);
}

int del_dish()
{
    int choice;
    int pos = 0;
    do
    {
        system("cls");
        printf("--------------------------\n·请选择您的操作\n·返回上级菜单请按Esc\n--------------------------\n\n1.热菜\n2.凉菜\n3.主食\n4.饮品\n\n请选择删除菜品的类型:");
        int type;
        if (choice_f('y', &type, 1, 4))
            return 0;
        // 依据菜品类型打开对应文件
        char filename[max_str_name_len] = {'\0'};
        switch (type)
        {
        case 1:
            strcpy(filename, hot_dish_filename);
            break;
        case 2:
            strcpy(filename, cold_dish_filename);
            break;
        case 3:
            strcpy(filename, staple_food_filename);
            break;
        case 4:
            strcpy(filename, drink_filename);
            break;
        }
        FILE *fp;
        dish_menu dm[MAX_LENGTH];
        memset(dm, 0, sizeof(dm));
        dish_menu dm_new[MAX_LENGTH];
        int cnt = 0;
        fp = fopen(filename, "r");
        while (!feof(fp))
        {
            fscanf(fp, "%d", &dm[cnt].no);
            fscanf(fp, "%s", dm[cnt].dish_name);
            fscanf(fp, "%lf", &dm[cnt].dish_price);
            fscanf(fp, "%d", &dm[cnt].type);
            cnt++;
        }
        fclose(fp);
        int del_no;
        int a, a0, b, b0;
        getxy(&a0, &b0);
        printf("\n请输入需要删除的菜品编号:");
        if (my_num_input('y', 2, NULL, &del_no))
            return 0;
        // 检索文件 该菜品是否存在
        int flag = 0;
        do
        {
            for (int i = 0; i < cnt - 1; i++)
            {
                if (dm[i].no == del_no)
                {
                    flag = 1;
                    pos = i;
                }
            }
            if (flag == 0)
            {
                gotoxy(a0, b0);
                printf("\n没有该菜品!                            \n请重新输入 : ");
                getxy(&a, &b);
                if (my_num_input('y', 2, NULL, &del_no))
                    return 0;
                gotoxy(a, b);
                for (int i = 0; i < MAX_STR_LEN; i++)
                    printf(" ");
                gotoxy(a, b);
            }
        } while (flag == 0);
        printf("\n是否确认删除<%s>菜品？1.是 2.否\n", dm[pos].dish_name);
        int del_choice;
        if (choice_f('y', &del_choice, 1, 2))
            return 0;
        // 删除菜品
        if (del_choice == 1)
        {
            int i;
            int j = 0;
            for (i = 0; i < cnt - 1; i++)
            {
                if (i == pos)
                    continue; // 跳过该菜品
                else
                {
                    dm_new[j].no = dm[i].no;
                    strcpy(dm_new[j].dish_name, dm[i].dish_name);
                    dm_new[j].dish_price = dm[i].dish_price;
                    dm_new[j].type = dm[i].type;
                    j++;
                }
            }
            // 将 dm_new 重新覆盖录入到菜单文件中
            fp = fopen(filename, "w");
            for (i = 0; i < cnt - 2; i++)
            {
                fprintf(fp, "%d\n", dm_new[i].no);
                fprintf(fp, "%s\n", dm_new[i].dish_name);
                fprintf(fp, "%lf\n", dm_new[i].dish_price);
                fprintf(fp, "%d\n", dm_new[i].type);
            }
            fclose(fp);
            printf("删除成功！\n");
        }
        printf("\n是否继续删除？1.是，2否？\n");
        if (choice_f('y', &choice, 1, 2))
            return 0;
    } while (choice != 2);
}

int price_adjust()
{
    int choice;
    int pos = 0;
    do
    {
        system("cls");
        printf("--------------------------\n·请选择您的操作\n·返回上级菜单请按Esc\n--------------------------\n\n1.热菜\n2.凉菜\n3.主食\n4.饮品\n\n请选择修改菜品的类型:");
        int type;
        if (choice_f('y', &type, 1, 4))
            return 0;
        // 依据菜品类型打开对应文件
        char filename[max_str_name_len];
        switch (type)
        {
        case 1:
            strcpy(filename, hot_dish_filename);
            break;
        case 2:
            strcpy(filename, cold_dish_filename);
            break;
        case 3:
            strcpy(filename, staple_food_filename);
            break;
        case 4:
            strcpy(filename, drink_filename);
            break;
        }
        FILE *fp;
        dish_menu dm[MAX_LENGTH];
        memset(dm, 0, sizeof(dm));
        int cnt = 0;
        fp = fopen(filename, "r");
        while (!feof(fp))
        {
            fscanf(fp, "%d", &dm[cnt].no);
            fscanf(fp, "%s", dm[cnt].dish_name);
            fscanf(fp, "%lf", &dm[cnt].dish_price);
            fscanf(fp, "%d", &dm[cnt].type);
            cnt++;
        }
        fclose(fp);
        printf("\n请输入需要修改价格的菜品编号：");
        int adjust_no;
        if (my_num_input('y', 2, NULL, &adjust_no))
            return 0;
        int a, a0, b, b0, tmp_flag = 0;
        getxy(&a0, &b0);
        // 检索文件 该菜品是否存在
        int flag = 0;
        while (flag == 0)
        {
            for (int i = 0; i < cnt - 1; i++)
            {
                if (dm[i].no == adjust_no)
                {
                    flag = 1;
                    pos = i;
                }
            }
            if (flag == 0)
            {
                if (tmp_flag == 0)
                {
                    gotoxy(a0, b0);
                    printf("\n没有该菜品!                            \n请重新输入 : ");
                    getxy(&a, &b);
                    tmp_flag = 1;
                }
                gotoxy(a, b);
                for (int i = 0; i < MAX_STR_LEN; i++)
                    printf(" ");
                gotoxy(a, b);
                if (my_num_input('y', 2, NULL, &adjust_no))
                    return 0;
            }
        }
        // 修改菜品
        printf("\n是否确认修改<%s>菜品的价格？1.是 2.否\n", dm[pos].dish_name);
        int adjust_choice;
        if (choice_f('y', &adjust_choice, 1, 6))
            break;
        if (adjust_choice == 1)
        {
            printf("\n请输入修改菜品后的价格：");
            double re_price;
            my_num_input('n', MAX_NUM_LEN, &re_price, NULL);
            int i;
            int j = 0;
            for (i = 0; i < cnt - 1; i++)
                if (i == pos)
                    dm[i].dish_price = re_price; // 修改价格
            // 将 dm重新覆盖录入到菜单文件中
            fp = fopen(filename, "w");
            for (i = 0; i < cnt - 1; i++)
            {
                fprintf(fp, "%d\n", dm[i].no);
                fprintf(fp, "%s\n", dm[i].dish_name);
                fprintf(fp, "%lf\n", dm[i].dish_price);
                fprintf(fp, "%d\n", dm[i].type);
            }
            fclose(fp);
            printf("\n修改成功！\n");
        }
        printf("\n是否继续修改？1.是，2否？\n");
        if (choice_f('y', &choice, 1, 2))
            return 0;
    } while (choice != 2);
}