#include "tools.h"
// Ԥ������
#define PASSWORD "123456"
// ���峣��
#define max_str_pw_len 15 // ������󳤶�
// ��������
char pw[max_str_pw_len] = PASSWORD;
// ����ȫ�ֱ���
char hot_dish_filename[max_str_name_len] = "hot_dish.txt";
char cold_dish_filename[max_str_name_len] = "cold_dish.txt";
char staple_food_filename[max_str_name_len] = "staple_food.txt";
char drink_filename[max_str_name_len] = "drink.txt";
// ��������
int input_password(char pw_input[], int wrong_time); // ��������
int check_password(char pw_input[]);                 // ������
int admin_menu();                                    // ����Ա�˵�
int order_check();                                   // ����ȷ��
int order_complete();                                // ��ɶ���
void income_check();                                 // �鿴Ӫҵ��
int add_dish();                                      // ��Ӳ�Ʒ
int del_dish();                                      // ɾ����Ʒ
int price_adjust();                                  // �۸����

int admin_form()
{
    system("cls");
    printf("----------------------\n������Աϵͳ�򿪳ɹ�!\n�������ϼ��˵��밴Esc\n----------------------\n\n");
    int choice;
    char pw_input[max_str_pw_len];
    printf("���������������̨����:\n");
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
            printf("----------------------\n������Աϵͳ�򿪳ɹ�!\n�������ϼ��˵��밴Esc\n----------------------\n\n");
            if (wrong_time != 0)
                printf("����̨���������������������:");
            else
                printf("���������������̨����:\n");
            wrong_time = 0;
            if (input_password(pw_input, wrong_time))
                return 0;
        }
        else
        {
            system("cls");
            printf("----------------------\n������Աϵͳ�򿪳ɹ�!\n�������ϼ��˵��밴Esc\n----------------------\n\n��������ȷ����ӭ����Ա��\n");
            for (int i = 0; i < 3; i++)
            {
                Sleep(400);
                printf(".");
            }
        }
    } while (flag != 0); // strcmp�������ͬ�ַ����Ȼ����-1,0,1
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
    memset(pw_input, 0, max_str_pw_len); // ����ַ���
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
            getch(); // ��ֹ����del��������ȼ�λ��Windows��ӳ���VK_DELETE��VK_LEFT�������λ��ʹ��getch()�õ�����ASCII�롣
        if (ch == 27)
        {
            gotoxy(x, y);
            system("cls");
            printf("ȷ���˳��밴y����������������ڴ�ҳ");
            ch = getch();
            if (ch == 'y' || ch == 'Y')
                return 1; // ���ص�if������ִ��if(1)�˳�����������棬�����ϼ��˵�
            else
                break; // �û�ȡ���˳������»ص������������
        }
        else if (ch == 13)
            break; // �س���
        else if (ch == 8 && x > 0)
        { // �˸��
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
        { // ��ͨ�ַ�
            if (cnt < max_str_pw_len)
            {
                pw_input[cnt] = ch;
                printf("*");
                x++;
                cnt++;
            }
            else
            {
                printf("\n���볤�ȳ���Ԥ���ڴ棬���˸�");
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
    printf("--------------------------\n����ѡ�����Ĳ���\n�������ϼ��˵��밴Esc\n--------------------------\n\n1.ȷ�Ϲ˿Ͷ���\n2.��ɹ˿Ͷ���\n3.�鿴����Ӫҵ��\n4.��Ӳ�Ʒ\n5.ɾ����Ʒ\n6.�޸ļ۸�\n\n����������:");
    // printf("7.�����ϼ��˵�\n");
    if (choice_f('y', &choice, 1, 6))
        return 7;
    return choice;
}

int order_check()
{
    system("cls");
    int tn = 1;
    int flag = 0;
    // �������ż����ļ��������ļ���
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
                printf("\n����:%d �����֧����\n�Ƿ�ȷ�϶����� 1.�� 2.��\n", tn);
                int choice;
                choice_f('n', &choice, 1, 2);
                // ���ȷ���������ñ�־λΪ 3
                if (choice == 1)
                {
                    fp = fopen(fstr, "r+");
                    fseek(fp, 0, SEEK_SET);
                    fprintf(fp, "%d", 3);
                    fclose(fp);
                    printf("����:%d�Ķ�����ȷ�ϳɹ���\n", tn);
                }
            }
        }
    }
    if (flag == 0)
        printf("���޶�����Ҫȷ�ϣ�\n");
    my_pause();
}

int order_complete()
{
    system("cls");
    int tn = 1;
    int flag = 0;
    // �������ż����ļ��������ļ���
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
                printf("����:%d �����ȷ�ϣ����ͽ������ѡ����ɶ�����\n�Ƿ�ȷ����ɶ����� 1.�� 2.��\n", tn);
                int choice;
                choice_f('n', &choice, 1, 2);
                // �����ɶ������ñ�־λΪ 4
                if (choice == 1)
                {
                    fp = fopen(fstr, "r+");
                    fseek(fp, 0, SEEK_SET);
                    fprintf(fp, "%d", 4);
                    fclose(fp);

                    printf("����:%d�Ķ�������ɣ�\n", tn);
                }
            }
        }
    }
    if (flag == 0)
        printf("���޶���������ᣡ\n");
    my_pause();
}

void income_check()
{
    // �����ж����ļ�������������ᶩ��������
    system("cls");
    int tn = 1;
    double account = 0;
    double account_hot_dish = 0;
    double account_cold_dish = 0;
    double account_staple_food = 0;
    double account_drink = 0;
    // �������ż����ļ��������ļ���
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
                // ��ȡ���ļ�����Ϣ��������Ӫҵ��
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
    printf("������:%.2lf\n�Ȳ�����:%.2lf\n��������:%.2lf\n��ʳ����:%.2lf\n��Ʒ����:%.2lf\n", account, account_hot_dish, account_cold_dish, account_staple_food, account_drink);
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
        printf("-------------------------\n����Ӳ�Ʒ����򿪳ɹ�!\n�������ϼ��˵��밴Esc\n-------------------------\n\n");
        printf("\n�������Ʒ��ţ�");
        if (my_num_input('y', 2, NULL, &new_dish.no))
            return 0;
        printf("\n�������Ʒ���ƣ�");
        int aa, bb;
        getxy(&aa, &bb);
        printf("                   ");
        gotoxy(aa, bb);
        if (my_str_input('y', new_dish.dish_name))
            return 0;
        printf("\n�������Ʒ�۸�");
        if (my_num_input('y', MAX_STR_LEN, NULL, &new_dish.dish_price))
            return 0;
        printf("\n�������Ʒ���ࣺ");
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
        printf("\n\n�Ƿ������Ӳ�Ʒ��\n");
        printf("1.��\n");
        printf("2.��\n");
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
        printf("--------------------------\n����ѡ�����Ĳ���\n�������ϼ��˵��밴Esc\n--------------------------\n\n1.�Ȳ�\n2.����\n3.��ʳ\n4.��Ʒ\n\n��ѡ��ɾ����Ʒ������:");
        int type;
        if (choice_f('y', &type, 1, 4))
            return 0;
        // ���ݲ�Ʒ���ʹ򿪶�Ӧ�ļ�
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
        printf("\n��������Ҫɾ���Ĳ�Ʒ���:");
        if (my_num_input('y', 2, NULL, &del_no))
            return 0;
        // �����ļ� �ò�Ʒ�Ƿ����
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
                printf("\nû�иò�Ʒ!                            \n���������� : ");
                getxy(&a, &b);
                if (my_num_input('y', 2, NULL, &del_no))
                    return 0;
                gotoxy(a, b);
                for (int i = 0; i < MAX_STR_LEN; i++)
                    printf(" ");
                gotoxy(a, b);
            }
        } while (flag == 0);
        printf("\n�Ƿ�ȷ��ɾ��<%s>��Ʒ��1.�� 2.��\n", dm[pos].dish_name);
        int del_choice;
        if (choice_f('y', &del_choice, 1, 2))
            return 0;
        // ɾ����Ʒ
        if (del_choice == 1)
        {
            int i;
            int j = 0;
            for (i = 0; i < cnt - 1; i++)
            {
                if (i == pos)
                    continue; // �����ò�Ʒ
                else
                {
                    dm_new[j].no = dm[i].no;
                    strcpy(dm_new[j].dish_name, dm[i].dish_name);
                    dm_new[j].dish_price = dm[i].dish_price;
                    dm_new[j].type = dm[i].type;
                    j++;
                }
            }
            // �� dm_new ���¸���¼�뵽�˵��ļ���
            fp = fopen(filename, "w");
            for (i = 0; i < cnt - 2; i++)
            {
                fprintf(fp, "%d\n", dm_new[i].no);
                fprintf(fp, "%s\n", dm_new[i].dish_name);
                fprintf(fp, "%lf\n", dm_new[i].dish_price);
                fprintf(fp, "%d\n", dm_new[i].type);
            }
            fclose(fp);
            printf("ɾ���ɹ���\n");
        }
        printf("\n�Ƿ����ɾ����1.�ǣ�2��\n");
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
        printf("--------------------------\n����ѡ�����Ĳ���\n�������ϼ��˵��밴Esc\n--------------------------\n\n1.�Ȳ�\n2.����\n3.��ʳ\n4.��Ʒ\n\n��ѡ���޸Ĳ�Ʒ������:");
        int type;
        if (choice_f('y', &type, 1, 4))
            return 0;
        // ���ݲ�Ʒ���ʹ򿪶�Ӧ�ļ�
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
        printf("\n��������Ҫ�޸ļ۸�Ĳ�Ʒ��ţ�");
        int adjust_no;
        if (my_num_input('y', 2, NULL, &adjust_no))
            return 0;
        int a, a0, b, b0, tmp_flag = 0;
        getxy(&a0, &b0);
        // �����ļ� �ò�Ʒ�Ƿ����
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
                    printf("\nû�иò�Ʒ!                            \n���������� : ");
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
        // �޸Ĳ�Ʒ
        printf("\n�Ƿ�ȷ���޸�<%s>��Ʒ�ļ۸�1.�� 2.��\n", dm[pos].dish_name);
        int adjust_choice;
        if (choice_f('y', &adjust_choice, 1, 6))
            break;
        if (adjust_choice == 1)
        {
            printf("\n�������޸Ĳ�Ʒ��ļ۸�");
            double re_price;
            my_num_input('n', MAX_NUM_LEN, &re_price, NULL);
            int i;
            int j = 0;
            for (i = 0; i < cnt - 1; i++)
                if (i == pos)
                    dm[i].dish_price = re_price; // �޸ļ۸�
            // �� dm���¸���¼�뵽�˵��ļ���
            fp = fopen(filename, "w");
            for (i = 0; i < cnt - 1; i++)
            {
                fprintf(fp, "%d\n", dm[i].no);
                fprintf(fp, "%s\n", dm[i].dish_name);
                fprintf(fp, "%lf\n", dm[i].dish_price);
                fprintf(fp, "%d\n", dm[i].type);
            }
            fclose(fp);
            printf("\n�޸ĳɹ���\n");
        }
        printf("\n�Ƿ�����޸ģ�1.�ǣ�2��\n");
        if (choice_f('y', &choice, 1, 2))
            return 0;
    } while (choice != 2);
}