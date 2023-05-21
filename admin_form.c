// 引入头文件
#include "tools.h"
// 预置密码
#define PASSWORD "123456"
// 定义常量
#define max_str_pw_len 15 // 密码最大长度
// 变量声明
char pw[max_str_pw_len] = PASSWORD;
// 部分全局变量
char hot_dish_filename[max_str_name_len] = "menu//hot_dish.txt";
char cold_dish_filename[max_str_name_len] = "menu//cold_dish.txt";
char staple_food_filename[max_str_name_len] = "menu//staple_food.txt";
char drink_filename[max_str_name_len] = "menu//drink.txt";
// 函数声明
int input_password(char pw_input[]);                 // 输入密码
int check_password(char pw_input[]);                 // 密码检测
int admin_menu();                                    //显示管理员菜单界面
void order_check();                                  // 订单确认
void order_complete();                               // 完成订单
void income_check();                                 // 查看营业额
int add_dish();                                      // 添加菜品
int del_dish();                                      // 删除菜品
int price_adjust();                                  // 价格调整

//显示管理员菜单界面
int admin_form()
{
    system("cls");
    printf("----------------------\n·管理员系统打开成功!\n·返回上级菜单请按Esc\n----------------------\n\n·请在这里输入后台密码:\n");
    int choice;
    char pw_input[max_str_pw_len + 1];
    if (input_password(pw_input))
        return 0; // 如果输入密码函数返回1，则返回上级菜单
    int flag;
    do
    {
        flag = check_password(pw_input); // 检查输入的密码是否正确
        if (flag != 0)
        {
            system("cls");
            printf("----------------------\n·管理员系统打开成功!\n·返回上级菜单请按Esc\n----------------------\n\n·后台密码输入错误，请重新输入:");
            if (input_password(pw_input)) // 如果输入密码函数返回1，则返回上级菜单
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
        choice = admin_menu(); // 显示管理员菜单选项并获取用户选择
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
    } while (choice != 7); // 用户选择退出管理员菜单
    return 0;
}

// 输入密码
int input_password(char pw_input[])
{
    memset(pw_input, 0, max_str_pw_len + 1); // 清空字符串
    int x, y;
    x = 0;
    y = 6;
    gotoxy(x, y); // 将光标移动到指定位置
    char ch;
    int cnt = 0;
    do
    {
        ch = getch(); // 获取用户按下的键位
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
            gotoxy(x, y); // 将光标移动到指定位置
            printf(" ");
            gotoxy(x, y); // 将光标移动到指定位置
            if (x == max_str_pw_len - 1)
            {
                printf("\n                                ");
                gotoxy(x, y); // 将光标移动到指定位置
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
                gotoxy(x, y); // 将光标移动到指定位置
            }
        }
    } while (ch != 13); // 用户按下回车键
    pw_input[cnt] = '\0';
    return 0;
}

// 密码检测
int check_password(char pw_input[])
{
    return strcmp(pw_input, pw); // 比较输入的密码与预设密码是否相同
}

// 管理员菜单函数，显示菜单选项并返回用户选择的操作
int admin_menu()
{
    system("cls"); // 清屏
    int choice;
    printf("--------------------------\n·请选择您的操作\n·返回上级菜单请按Esc\n--------------------------\n\n1.确认顾客订单\n2.完成顾客订单\n3.查看今日营业额\n4.添加菜品\n5.删除菜品\n6.修改价格\n\n在这里输入:");
    // printf("7.返回上级菜单\n");
    if (choice_f('y', &choice, 1, 6))//'y'代表可以按ESC返回上级菜单
        return 7; // 如果按下了ESC键，返回上级菜单
    return choice; // 返回用户选择的操作
}

// 确认顾客订单函数，遍历所有订单文件，确认顾客订单
void order_check()
{
    system("cls"); // 清屏
    int tn = 1; // 桌号
    int flag = 0; // 标志位，表示是否存在需要确认的订单
    // 根据桌号检索文件，生成文件名
    for (tn = 1; tn <= MAX_STR_TABLE_LEN; tn++)
    {
        char fstr[50] = { '\0' }; // 存放文件名的字符串数组
        sprintf(fstr, "order//%d.txt", tn); // 根据桌号生成文件名
        FILE* fp;
        fp = fopen(fstr, "r"); // 打开订单文件
        if (fp == NULL) // 如果文件打开失败，说明该桌没有订单
            continue;
        else
        {
            int flag_temp;
            fscanf(fp, "%d", &flag_temp); // 读取文件中的标志位
            fclose(fp);
            if (flag_temp == 2) // 如果标志位为2，说明顾客已完成支付
            {
                flag = 1; // 存在需要确认的订单
                printf("桌号:%d 已完成支付！\n是否确认订单？ 1.是 2.否\n", tn);
                int choice;
                choice_f('n', &choice, 1, 2); // 获取用户的选择
                // 如果确定订单则将标志位置为 3
                if (choice == 1)
                {
                    fp = fopen(fstr, "r+"); // 以读写模式打开文件
                    fseek(fp, 0, SEEK_SET); // 将文件指针指向文件开头
                    fprintf(fp, "%d", 3); // 将标志位写入文件
                    fclose(fp);
                    printf("\n桌号:%d的订单已确认成功！\n", tn);
                }
            }
        }
    }
    if (flag == 0) // 如果没有需要确认的订单
        printf("暂无订单需要确认！\n");
    my_pause(); // 暂停程序，等待用户按下任意键继续
}

// 完成顾客订单函数，遍历所有订单文件，确认完成顾客订单
void order_complete()
{
    system("cls"); // 清屏
    int tn = 1; // 桌号
    int flag = 0; // 标志位，表示是否存在需要完成的订单
    // 根据桌号检索文件，生成文件名
    for (tn = 1; tn <= MAX_STR_TABLE_LEN; tn++)
    {
        char fstr[50] = { '\0' }; // 存放文件名的字符串数组
        sprintf(fstr, "order//%d.txt", tn); // 根据桌号生成文件名
        FILE* fp;
        fp = fopen(fstr, "r"); // 打开订单文件
        if (fp == NULL) // 如果文件打开失败，说明该桌没有订单
            continue;
        else
        {
            int flag_temp;
            fscanf(fp, "%d", &flag_temp); // 读取文件中的标志位
            fclose(fp);
            if (flag_temp == 3) // 如果标志位为3，说明顾客已完成确认
            {
                flag = 1; // 存在需要完成的订单
                printf("桌号:%d 已完成确认，出餐结束后可选择完成订单！\n是否确认完成订单？ 1.是 2.否\n", tn);
                int choice;
                choice_f('n', &choice, 1, 2); // 获取用户的选择
                // 如果完成订单则将标志位置为 4
                if (choice == 1)
                {
                    fp = fopen(fstr, "r+"); // 以读写模式打开文件
                    fseek(fp, 0, SEEK_SET); // 将文件指针指向文件开头
                    fprintf(fp, "%d", 4); // 将标志位写入文件
                    fclose(fp);
                    printf("\n桌号:%d的订单已完成！\n", tn);
                }
            }
        }
    }
    if (flag == 0) // 如果没有需要完成的订单
        printf("暂无订单可以完结！\n");
    my_pause(); // 暂停程序，等待用户按下任意键继续
}

// 查看今日营业额函数，遍历所有订单文件，计算今日营业额
void income_check()
{
    system("cls"); // 清屏
    int tn = 1; // 桌号
    double account = 0; // 总收入
    double account_hot_dish = 0; // 热菜收入
    double account_cold_dish = 0; // 凉菜收入
    double account_staple_food = 0; // 主食收入
    double account_drink = 0; // 饮品收入
    // 根据桌号检索文件，生成文件名
    for (tn = 1; tn <= MAX_STR_TABLE_LEN; tn++)
    {
        char fstr[50] = { '\0' }; // 存放文件名的字符串数组
        sprintf(fstr, "order//%d.txt", tn); // 根据桌号生成文件名
        FILE* fp;
        fp = fopen(fstr, "r"); // 打开订单文件
        if (fp == NULL) // 如果文件打开失败，说明该桌没有订单
            continue;
        else
        {
            int flag_temp;
            fscanf(fp, "%d", &flag_temp); // 读取文件中的标志位
            if (flag_temp == 4) // 如果标志位为4，说明该订单已完成
            {
                // 读取该文件的信息，并计算营业额
                int no;
                int type;
                char dish_name[max_str_name_len];
                int nums;
                double price;
                while (fscanf(fp, "%d %s %lf %d %d", &no, dish_name, &price, &type, &nums) == 5)
                {
                    account += price * nums; // 计算总收入
                    switch (type) // 根据菜品类型计算不同种类的收入
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
                    default:
                        break;
                    }
                }
            }
        }
        fclose(fp);
    }
    printf("总收入:%.2lf\n热菜收入:%.2lf\n凉菜收入:%.2lf\n主食收入:%.2lf\n饮品收入:%.2lf\n", account, account_hot_dish, account_cold_dish, account_staple_food, account_drink);
    my_pause(); // 暂停程序，等待用户按下任意键继续
}

// 添加菜品函数
int add_dish()
{
    FILE* fp;
    int choice;

    do
    {
        // 新建一个菜品结构体
        dish_menu new_dish;

        // 清屏并打印菜品种类选择界面
        system("cls");
        printf("-------------------------\n·添加菜品界面打开成功!\n·返回上级菜单请按Esc\n-------------------------\n\n1.热菜\n2.凉菜\n3.主食\n4.饮品\n\n请输入菜品种类：");

        // 判断选择的菜品种类，并存储到新建的菜品结构体中
        if (choice_f('y', &new_dish.type, 1, 4))//'y'代表可以按ESC返回上级菜单
            return 0;

        // 根据菜品种类确定存储菜品信息的文件名
        char filename[max_str_name_len] = { '\0' };
        fnm_switch(new_dish.type, filename);

        // 要求输入菜品编号，并检查编号是否已存在
        printf("\n请输入菜品编号：");
        FILE* chk_fp;
        int tmp_flag = 0;
        int a, a0, b, b0, no_exist;
    chk_no: // 检查菜品编号是否已存在
        if (my_num_input('y', 2, NULL, &new_dish.no))//'y'代表可以按ESC返回上级菜单
            return 0;
        getxy(&a0, &b0);
        chk_fp = fopen(filename, "r");
        dish_menu chk_dish;
        no_exist = 1;
        while (fscanf(chk_fp, "%d %*s %*lf %*d", &chk_dish.no) == 1)
        {
            if (new_dish.no == chk_dish.no)
            {
                no_exist = 0;
                break;
            }
        }
        if (!no_exist)
        {
            if (tmp_flag == 0)
            {
                gotoxy(a0, b0);
                printf("\n菜品编号已存在，请重新输入：");
                getxy(&a, &b);
                tmp_flag = 1;
            }
            gotoxy(a, b);
            for (int i = 0; i < MAX_STR_LEN; i++)
                printf(" ");
            gotoxy(a, b);
            goto chk_no;
        }

        // 要求输入菜品名称，并存储到新建的菜品结构体中
        printf("\n请输入菜品名称：");
        if (my_str_input('y', new_dish.dish_name))//'y'代表可以按ESC返回上级菜单
            return 0;

        // 要求输入菜品价格，并存储到新建的菜品结构体中
        printf("\n请输入菜品价格：");
        if (my_num_input('y', MAX_NUM_LEN, &new_dish.dish_price, NULL))//'y'代表可以按ESC返回上级菜单
            return 0;

        // 将新建的菜品信息存储到相应的文件中
        fp = fopen(filename, "a");
        fprintf(fp, "%d\n%s\n%lf\n%d\n", new_dish.no, new_dish.dish_name, new_dish.dish_price, new_dish.type);
        fclose(fp);

        // 询问是否继续添加菜品
        printf("\n\n是否继续添加菜品：\n1.是\n2.否\n");
        if (choice_f('y', &choice, 1, 2))//'y'代表可以按ESC返回上级菜单
            return 0;

    } while (choice != 2);

    return 0;
}

// 删除菜品函数
int del_dish()
{
    int choice;
    int pos = 0;
    do
    {
        system("cls"); // 清屏
        printf("--------------------------\n·请选择您的操作\n·返回上级菜单请按Esc\n--------------------------\n\n1.热菜\n2.凉菜\n3.主食\n4.饮品\n\n请选择删除菜品的类型:");
        int type;
        if (choice_f('y', &type, 1, 4))//'y'代表可以按ESC返回上级菜单
            return 0; // 如果按下了ESC键，则直接返回
        // 依据菜品类型打开对应文件
        char filename[max_str_name_len] = { '\0' };
        fnm_switch(type, filename); // 根据菜品类型选择对应的文件
        FILE* fp;
        dish_menu dm[MAX_LENGTH]; // 定义一个结构体数组
        memset(dm, 0, sizeof(dm)); // 初始化结构体数组
        dish_menu dm_new[MAX_LENGTH];
        memset(dm_new, 0, sizeof(dm_new));
        int cnt = 0;
        fp = fopen(filename, "r"); // 以只读方式打开文件
        while (fscanf(fp, "%d %s %lf %d", &dm[cnt].no, dm[cnt].dish_name, &dm[cnt].dish_price, &dm[cnt].type) == 4)
        {
            cnt++; // 读取文件，将菜品信息存储到结构体数组中
        }
        fclose(fp); // 关闭文件
        int del_no;
        int a, a0, b, b0;
        getxy(&a0, &b0); // 获取光标所在位置
        printf("\n请输入需要删除的菜品编号:");
        if (my_num_input('y', 2, NULL, &del_no))//'y'代表可以按ESC返回上级菜单
            return 0; // 如果按下了ESC键，则直接返回
        // 检索文件 该菜品是否存在
        int flag = 0;
        do
        {
            for (int i = 0; i < cnt - 1; i++)
            {
                if (dm[i].no == del_no)
                {
                    flag = 1; // 如果存在该菜品，则将flag置为1
                    pos = i; // 将该菜品的位置保存
                }
            }
            if (flag == 0)
            {
                gotoxy(a0, b0);
                printf("\n没有该菜品!                            \n请重新输入 : ");
                getxy(&a, &b);
                if (my_num_input('y', 2, NULL, &del_no))//'y'代表可以按ESC返回上级菜单
                    return 0; // 如果按下了ESC键，则直接返回
                gotoxy(a, b);
                for (int i = 0; i < MAX_STR_LEN; i++)
                    printf(" ");
                gotoxy(a, b);
            }
        } while (flag == 0); // 如果没有找到该菜品，则重新输入
        printf("\n是否确认删除<%s>菜品？1.是 2.否\n", dm[pos].dish_name);
        int del_choice;
        if (choice_f('y', &del_choice, 1, 2))//'y'代表可以按ESC返回上级菜单
            return 0; // 如果按下了ESC键，则直接返回
        // 删除菜品
        if (del_choice == 1) // 如果选择确认删除
        {
            int i;
            int j = 0;
            for (i = 0; i < cnt - 1; i++) // 将除了需要删除的菜品外的其他菜品保存到新的结构体数组中
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
            fp = fopen(filename, "w"); // 以只写方式打开文件
            for (i = 0; i < cnt - 2; i++) // 将新的结构体数组中的菜品信息写入文件中
            {
                fprintf(fp, "%d\n%s\n%lf\n%d\n", dm_new[i].no, dm_new[i].dish_name, dm_new[i].dish_price, dm_new[i].type);
            }
            fclose(fp); // 关闭文件
            printf("删除成功！\n");
        }
        printf("\n是否继续删除？1.是，2否？\n");
        if (choice_f('y', &choice, 1, 2))//'y'代表可以按ESC返回上级菜单
            return 0; // 如果按下了ESC键，则直接返回
    } while (choice != 2); // 如果选择不是2，则继续删除
    return 0;
}

// 修改菜品函数
int price_adjust()
{
    int choice; // 定义变量choice，用于记录用户选择的操作
    int pos = 0; // 定义变量pos，用于记录修改的菜品在数组中的位置
    do
    {
        system("cls"); // 清屏
        // 输出菜单类型选择界面
        printf("--------------------------\n·请选择您的操作\n·返回上级菜单请按Esc\n--------------------------\n\n1.热菜\n2.凉菜\n3.主食\n4.饮品\n\n请选择修改菜品的类型:");
        int type;
        // 调用choice_f函数获取用户输入的菜品类型
        if (choice_f('y', &type, 1, 4))//'y'代表可以按ESC返回上级菜单
            return 0;
        // 根据菜品类型打开对应文件
        char filename[max_str_name_len];
        fnm_switch(type, filename);
        FILE* fp;
        dish_menu dm[MAX_LENGTH];
        memset(dm, 0, sizeof(dm)); // 将数组dm全部清零
        int cnt = 0; // 定义变量cnt，用于记录菜品数量
        fp = fopen(filename, "r"); // 打开菜单文件
        // 读取菜品信息
        while (fscanf(fp, "%d %s %lf %d", &dm[cnt].no, dm[cnt].dish_name, &dm[cnt].dish_price, &dm[cnt].type) == 4)
        {
            cnt++;
        }
        fclose(fp); // 关闭文件
        printf("\n请输入需要修改价格的菜品编号：");
        int adjust_no;
        // 调用my_num_input函数获取用户输入的菜品编号
        if (my_num_input('y', 2, NULL, &adjust_no))//'y'代表可以按ESC返回上级菜单
            return 0;
        int a, a0, b, b0, tmp_flag = 0;
        getxy(&a0, &b0); // 获取光标位置
        // 检索文件，查找需要修改的菜品是否存在
        int flag = 0;
        while (flag == 0)
        {
            for (int i = 0; i < cnt - 1; i++)
            {
                if (dm[i].no == adjust_no) // 找到需要修改的菜品
                {
                    flag = 1; // 标记找到
                    pos = i; // 记录该菜品在数组中的位置
                }
            }
            if (flag == 0)
            {
                if (tmp_flag == 0)
                {
                    gotoxy(a0, b0);
                    printf("\n没有该菜品! \n请重新输入 : ");
                    getxy(&a, &b);
                    tmp_flag = 1;
                }
                gotoxy(a, b);
                for (int i = 0; i < MAX_STR_LEN; i++)
                    printf(" ");
                gotoxy(a, b);
                if (my_num_input('y', 2, NULL, &adjust_no))//'y'代表可以按ESC返回上级菜单
                    return 0;
            }
        }
        // 修改菜品价格
        printf("\n是否确认修改<%s>菜品的价格？1.是 2.否\n", dm[pos].dish_name);
        int adjust_choice;
        // 调用choice_f函数获取用户是否确认修改的选择
        if (choice_f('y', &adjust_choice, 1, 2))//'y'代表可以按ESC返回上级菜单
            break;
        if (adjust_choice == 1) // 用户确认修改
        {
            printf("\n请输入修改菜品后的价格：");
            double re_price;
            // 调用my_num_input函数获取用户输入的新价格
            my_num_input('n', MAX_NUM_LEN, &re_price, NULL);
            int i;
            int j = 0;
            for (i = 0; i < cnt - 1; i++)
                if (i == pos)
                    dm[i].dish_price = re_price; // 修改价格
            // 将修改后的菜单重新写入到文件中
            fp = fopen(filename, "w");
            for (i = 0; i < cnt - 1; i++) {
                fprintf(fp, "%d\n%s\n%lf\n%d\n", dm[i].no, dm[i].dish_name, dm[i].dish_price, dm[i].type);
            }
            fclose(fp); // 关闭文件
            printf("\n修改成功！\n");
        }
        printf("\n是否继续修改？1.是，2否？\n");
        // 调用choice_f函数获取用户是否继续修改的选择
        if (choice_f('y', &choice, 1, 2))//'y'代表可以按ESC返回上级菜单
            return 0;
    } while (choice != 2); // 直到用户选择退出
    return 0; // 返回0，表示函数执行完毕
}
