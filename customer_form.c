#include "tools.h"
// 变量声明
int table_no; // 餐台号
extern char hot_dish_filename[max_str_name_len];
extern char cold_dish_filename[max_str_name_len];
extern char staple_food_filename[max_str_name_len];
extern char drink_filename[max_str_name_len];
// 函数声明
int customer_menu();                     // 菜单界面
void all_dishmenu(char* fnm);            // 打开菜单
void over_view();                        // 总览
int check_bill();                        // 支付订单
void order_status();                     // 订单状态
void page_controller(dish_menu*, int);  // 菜单分页
int display_menu(dish_menu*, int, int); // 显示菜单信息
int create_order(dish_menu*, int, int); // 生成订单

int customer_form()
{
    system("cls");
    printf("----------------------\n·顾客系统打开成功!\n·返回上级菜单请按Esc\n----------------------\n\n请输入您的餐台号：");
    int choice; // 输入餐台号
    if (choice_f('y', &table_no, 1, 999))
        return 0;
    // 打开菜单界面
    do
    {
        choice = customer_menu();
        switch (choice)
        {
        case 1:
            all_dishmenu(hot_dish_filename);
            break;
        case 2:
            all_dishmenu(cold_dish_filename);
            break;
        case 3:
            all_dishmenu(staple_food_filename);
            break;
        case 4:
            all_dishmenu(drink_filename);
            break;
        case 5:
            over_view();
            break;
        case 6:
            check_bill();
            break;
        case 7:
            order_status();
            break;
        case 8:
            break;
        default:
            continue;
        }
    } while (choice > 8 || choice < 1);
}

int customer_menu()
{
    system("cls");
    int choice;
    printf("--------------------------\n·餐台：%d 请选择您的操作\n·返回上级菜单请按Esc\n--------------------------\n\n1.热菜\n2.凉菜\n3.主食\n4.饮品\n5.总览\n6.结账\n7.订单状态\n\n在这里输入:", table_no);
    // printf("8.退出\n");
    if (choice_f('y', &choice, 1, 7))
        return 8;
    return choice;
}

void all_dishmenu(char* fnm)
{
    dish_menu all_dishmenu[MAX_LENGTH]; // 采用结构体数组保存读取到的菜单品信息
    int cnt = 0;                        // 设置一个计数器保存菜品实际数量
    // 打开 cold_dish.txt 并读取数据进行显示
    FILE* fp;
    char filename[20];
    strcpy(filename, fnm);
    fp = fopen(filename, "r");
    while (fscanf(fp, "%d %s %lf %d", &all_dishmenu[cnt].no,
        all_dishmenu[cnt].dish_name, &all_dishmenu[cnt].dish_price,
        &all_dishmenu[cnt].type) == 4)
    {
        cnt++;
    }
    fclose(fp);
    page_controller(all_dishmenu, cnt); // 采用分页控制显示菜单并执行点菜操作
}

void over_view()
{
    system("cls");
    int cnt = 0;
    dish_order my_order[MAX_LENGTH]; // 根据桌号生成订单文件名
    char fstr[50] = { '\0' };
    sprintf(fstr, "order//%d.txt", table_no);
    // 判断是否存在该文件，若不存在，则该订单不存在
    FILE* fp;
    fp = fopen(fstr, "r");
    if (fp == NULL)
    {
        printf("您还没有下单！\n");
        my_pause();
        return 0;
    }
    else
    {               // 从文件中获取订单内容
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
    fclose(fp);
    // 订单信息读取结束后显示
    printf("序号 菜品编号     菜品名称       单价   数量     小计\n");
    for (int i = 0; i < cnt; i++)
        printf("%d\t %d\t  %s\t %.2lf\t %d\t %.2lf\n", i + 1, my_order[i].no, my_order[i].dish_name, my_order[i].dish_price, my_order[i].nums, my_order[i].dish_price * my_order[i].nums);
    my_pause();
}

int check_bill()
{
    system("cls");
    double account = 0;
    int cnt = 0;
    dish_order my_order[MAX_LENGTH]; // 根据桌号生成订单文件名
    char fstr[50] = { '\0' };
    sprintf(fstr, "order//%d.txt", table_no);
    // 判断是否存在该文件，若不存在，则该订单不存在
    FILE* fp;
    fp = fopen(fstr, "r");
    if (fp == NULL)
    {
        printf("您还没有下单！\n");
        my_pause();
        return 0;
    }
    else
    {
        int flag_0; // 从文件中获取订单内容, 提取标志位，防止误读
        fscanf(fp, "%d", &flag_0);
        if (flag_0 != 1)
        {
            printf("您已完成支付，请稍候为您上餐\n");
            my_pause();
            return 0;
        }
        // 读出文件信息
        while (fscanf(fp, "%d %s %lf %d %d", &my_order[cnt].no,
            my_order[cnt].dish_name, &my_order[cnt].dish_price,
            &my_order[cnt].type, &my_order[cnt].nums) == 5)
        {
            account += my_order[cnt].dish_price * my_order[cnt].nums;
            cnt++;
        }
    }
    fclose(fp);
    printf("---------------------\n·返回上级菜单请按Esc\n·您需要支付：%.2lf元\n---------------------\n·请支付:", account);
    double pay;
    if (my_num_input('y', MAX_STR_LEN, &pay, NULL))
        return 0;
    printf("\n");
    while (pay < account)
    {
        printf("客官，钱还不够！\n客官再给点：");
        if (my_num_input('y', MAX_STR_LEN, &pay, NULL))
            return 0;
    }
    if (pay > account)
        printf("\n客官大气，找您%.2lf元\n", pay - account);
    printf("客官请稍等，小的这就通知老板给您上菜\n");
    fp = fopen(fstr, "w");
    fprintf(fp, "%d\n", 2); // 设置标志位为2，为支付完成，重新录入文件
    for (int i = 0; i < cnt; i++)
        fprintf(fp, "%d %s %lf %d %d\n", my_order[i].no, my_order[i].dish_name, my_order[i].dish_price, my_order[i].type, my_order[i].nums);
    fclose(fp);
    my_pause();
}

void order_status()
{
    system("cls");
    char fstr[50] = { '\0' };
    sprintf(fstr, "order//%d.txt", table_no); // 根据桌号生成订单文件名
    // 判断是否存在该文件，若不存在，则该订单不存在
    FILE* fp;
    fp = fopen(fstr, "r");
    if (fp == NULL)
    {
        printf("您还没有下单！\n");
        my_pause();
        return 0;
    }
    int flag_0;
    fscanf(fp, "%d", &flag_0);
    fclose(fp);
    switch (flag_0)
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
    my_pause();
}

int create_order(dish_menu* dm, int mode, int count)
{
    int cnt = 0;
    dish_order new_order[MAX_LENGTH];
    // 根据mode打开文件
    char filename[20];
    switch (mode)
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
    FILE* fp;
    fp = fopen(filename, "r");
    int choice;
    int temp_no;
    int temp_num;
    do
    {
        printf("\n请输入菜品编号：");
        if (my_num_input('y', MAX_STR_LEN, NULL, &temp_no))
            return 0;
        // 检测菜品编号是否存在
        int flag = 0;
        do
        {
            int i;
            for (i = 0; i < count; i++)
            {
                if (dm[i].no == temp_no)
                {
                    flag = 1;
                    new_order[cnt].no = dm[i].no;
                    strcpy(new_order[cnt].dish_name, dm[i].dish_name);
                    new_order[cnt].dish_price = dm[i].dish_price;
                    new_order[cnt].type = dm[i].type;
                    break;
                }
            }

            if (flag == 0)
            {
                printf("\n输入的菜品编号不存在，请输入正确的菜品编号：");
                if (my_num_input('y', MAX_STR_LEN, NULL, &temp_no))
                    return 0;
            }
        } while (flag == 0);
        // 菜品编号存在时输入点菜数量
        printf("\n请输入点菜数量：");
        if (choice_f('y', &temp_num, 1, 999))
            return 0;
        new_order[cnt].nums = temp_num;
        cnt++;
        // 判断是否继续点菜
        printf("\n是否继续点菜？ 1.是 2.否 ：\n");
        if (choice_f('y', &choice, 1, 2))
            return 0;
    } while (choice != 2);
    fclose(fp);
    // 根据桌号生成订单文件名
    char fstr[50] = { '\0' };
    sprintf(fstr, "order//%d.txt", table_no);
    // 首先判断该文件是否存在，如不存在则创建一个，并设置标志位为1
    fp = fopen(fstr, "r");
    if (fp == NULL)
    {
        fp = fopen(fstr, "w");
        fprintf(fp, "%d\n", 1);
    }
    fclose(fp);
    // 而后以追加模式重新打开文件，将订单信息添加进去
    fp = fopen(fstr, "a");
    int i = 0;
    for (i = 0; i < cnt; i++)
        fprintf(fp, "%d %s %lf %d %d\n", new_order[i].no, new_order[i].dish_name, new_order[i].dish_price, new_order[i].type, new_order[i].nums);
    fclose(fp);
}

int display_menu(dish_menu* dm, int start, int end)
{
    int i;
    int choice;
    system("cls");
    printf("----------------------------------------------------------\n·点餐页面打开成功，请选择选项\n·返回上级菜单请按Esc\n----------------------------------------------------------\n序号  菜品编号    菜品名称      价格\n");
    for (i = start; i < end; i++)
        printf(" %d\t %d\t  %s\t%.2lf\n", i + 1, dm[i].no, dm[i].dish_name, dm[i].dish_price);
    printf("----------------------------------------------------------\n");
    // 添加控制逻辑，防止误判
    if (start == 0 && end - start < RECORD_NUM)
    {
        printf("3.点菜\n");
        printf("4.退出\n");
        if (choice_f('y', &choice, 3, 4))
            return 4;
    }
    else if (start == 0)
    {
        // 无上一页选项
        printf("2.下一页\n");
        printf("3.点菜\n");
        printf("4.退出\n");
        if (choice_f('y', &choice, 2, 4))
            return 4;
    }
    else if (end - start != RECORD_NUM)
    {
        // 无下一页选项
        printf("1.上一页\n");
        printf("3.点菜\n");
        printf("4.退出\n");
        if (my_num_input('y', 1, NULL, &choice))
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
            if (my_num_input('y', 1, NULL, &choice))
                return 4;
        }
    }
    else
    { // 正常显示
        printf("1.上一页\n");
        printf("2.下一页\n");
        printf("3.点菜\n");
        printf("4.退出\n");
        if (choice_f('y', &choice, 1, 4))
            return 4;
    }
    return choice;
}

void page_controller(dish_menu* dm, int cnt)
{
    int record_num = RECORD_NUM;
    // 设定部分显示相关变量
    int base = 0;
    int start, end;
    start = base;
    end = start + record_num > cnt ? cnt : start + record_num;
    int choice;
    do
    {
        choice = display_menu(dm, start, end);
        switch (choice)
        {
        case 1:
        {
            if (end - start < record_num)
                end = end - (end - start);
            else
                end -= record_num;
            start -= record_num;
            break;
        }
        case 2:
        {
            start += record_num;
            end = start + record_num > cnt ? cnt : start + record_num;
            break;
        }
        case 3:
        {
            int mode = dm[0].type;
            create_order(dm, mode, cnt);
            break;
        }
        case 4:
            break;
        }
    } while (choice != 4);
}
