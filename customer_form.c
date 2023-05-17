#include "tools.h"
// ��������
int table_no; // ��̨��
extern char hot_dish_filename[max_str_name_len];
extern char cold_dish_filename[max_str_name_len];
extern char staple_food_filename[max_str_name_len];
extern char drink_filename[max_str_name_len];
// ��������
int customer_menu();                     // �˵�����
void all_dishmenu(char *fnm);            // �򿪲˵�
void over_view();                        // ����
int check_bill();                        // ֧������
void order_status();                     // ����״̬
void page_controller(dish_menu *, int);  // �˵���ҳ
int display_menu(dish_menu *, int, int); // ��ʾ�˵���Ϣ
int create_order(dish_menu *, int, int); // ���ɶ���

int customer_form()
{
    system("cls");
    printf("----------------------\n���˿�ϵͳ�򿪳ɹ�!\n�������ϼ��˵��밴Esc\n----------------------\n\n���������Ĳ�̨�ţ�");
    int choice; // �����̨��
    if (choice_f('y', &table_no, 1, 999))
        return 0;
start: // �򿪲˵�����
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
        default:
            break;
        }
    } while (choice > 8 || choice < 1);
    if (choice != 8)
        goto start;
}

int customer_menu()
{
    system("cls");
    int choice;
    printf("--------------------------\n����̨��%d ��ѡ�����Ĳ���\n�������ϼ��˵��밴Esc\n--------------------------\n\n1.�Ȳ�\n2.����\n3.��ʳ\n4.��Ʒ\n5.����\n6.����\n7.����״̬\n\n����������:", table_no);
    // printf("8.�˳�\n");
    if (choice_f('y', &choice, 1, 7))
        return 8;
    return choice;
}

void all_dishmenu(char *fnm)
{
    dish_menu all_dishmenu[MAX_LENGTH]; // ���ýṹ�����鱣���ȡ���Ĳ˵�Ʒ��Ϣ
    int cnt = 0;                        // ����һ�������������Ʒʵ������
    // �� cold_dish.txt ����ȡ���ݽ�����ʾ
    FILE *fp;
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
    page_controller(all_dishmenu, cnt); // ���÷�ҳ������ʾ�˵���ִ�е�˲���
}

void over_view()
{
    system("cls");
    int cnt = 0;
    dish_order my_order[MAX_LENGTH]; // �����������ɶ����ļ���
    char fstr[50] = {'\0'};
    sprintf(fstr, "order//%d.txt", table_no);
    // �ж��Ƿ���ڸ��ļ����������ڣ���ö���������
    FILE *fp;
    fp = fopen(fstr, "r");
    if (fp == NULL)
    {
        printf("����û���µ���\n");
        my_pause();
        return 0;
    }
    else
    {               // ���ļ��л�ȡ��������
        int flag_0; // ��ȡ��־λ����ֹ���
        fscanf(fp, "%d", &flag_0);
        // �����ļ���Ϣ
        while (fscanf(fp, "%d %s %lf %d %d", &my_order[cnt].no,
                      my_order[cnt].dish_name, &my_order[cnt].dish_price,
                      &my_order[cnt].type, &my_order[cnt].nums) == 5)
        {
            cnt++;
        }
    }
    fclose(fp);
    // ������Ϣ��ȡ��������ʾ
    printf("��� ��Ʒ���     ��Ʒ����       ����   ����     С��\n");
    for (int i = 0; i < cnt; i++)
        printf("%d\t %d\t  %s\t %.2lf\t %d\t %.2lf\n", i + 1, my_order[i].no, my_order[i].dish_name, my_order[i].dish_price, my_order[i].nums, my_order[i].dish_price * my_order[i].nums);
    my_pause();
}

int check_bill()
{
    system("cls");
    double account = 0;
    int cnt = 0;
    dish_order my_order[MAX_LENGTH]; // �����������ɶ����ļ���
    char fstr[50] = {'\0'};
    sprintf(fstr, "order//%d.txt", table_no);
    // �ж��Ƿ���ڸ��ļ����������ڣ���ö���������
    FILE *fp;
    fp = fopen(fstr, "r");
    if (fp == NULL)
    {
        printf("����û���µ���\n");
        my_pause();
        return 0;
    }
    else
    {
        int flag_0; // ���ļ��л�ȡ��������, ��ȡ��־λ����ֹ���
        fscanf(fp, "%d", &flag_0);
        if (flag_0 != 1)
        {
            printf("�������֧�������Ժ�Ϊ���ϲ�\n");
            my_pause();
            return 0;
        }
        // �����ļ���Ϣ
        while (fscanf(fp, "%d %s %lf %d %d", &my_order[cnt].no,
                      my_order[cnt].dish_name, &my_order[cnt].dish_price,
                      &my_order[cnt].type, &my_order[cnt].nums) == 5)
        {
            account += my_order[cnt].dish_price * my_order[cnt].nums;
            cnt++;
        }
    }
    fclose(fp);
    printf("---------------------\n�������ϼ��˵��밴Esc\n������Ҫ֧����%.2lfԪ\n---------------------\n����֧��:", account);
    double pay;
    if (my_num_input('y', MAX_STR_LEN, &pay, NULL))
        return 0;
    printf("\n");
    while (pay < account)
    {
        printf("�͹٣�Ǯ��������\n�͹��ٸ��㣺");
        if (my_num_input('y', MAX_STR_LEN, &pay, NULL))
            return 0;
    }
    if (pay > account)
        printf("\n�͹ٴ���������%.2lfԪ\n", pay - account);
    printf("�͹����Եȣ�С�����֪ͨ�ϰ�����ϲ�\n");
    fp = fopen(fstr, "w");
    fprintf(fp, "%d\n", 2); // ���ñ�־λΪ2��Ϊ֧����ɣ�����¼���ļ�
    for (int i = 0; i < cnt; i++)
        fprintf(fp, "%d %s %lf %d %d\n", my_order[i].no, my_order[i].dish_name, my_order[i].dish_price, my_order[i].type, my_order[i].nums);
    fclose(fp);
    my_pause();
}

void order_status()
{
    system("cls");
    char fstr[50] = {'\0'};
    sprintf(fstr, "order//%d.txt", table_no); // �����������ɶ����ļ���
    // �ж��Ƿ���ڸ��ļ����������ڣ���ö���������
    FILE *fp;
    fp = fopen(fstr, "r");
    if (fp == NULL)
    {
        printf("����û���µ���\n");
        my_pause();
        return 0;
    }
    int flag_0;
    fscanf(fp, "%d", &flag_0);
    fclose(fp);
    switch (flag_0)
    {
    case 1:
        printf("���ѵ�ˣ������Ʋ�ȥ֧��Ӵ��\n");
        break;
    case 2:
        printf("����֧����ɣ��ϰ�������ȷ���У�\n");
        break;
    case 3:
        printf("����Ϊ�����ͣ��Եȣ�\n");
        break;
    case 4:
        printf("ף���ò���죬��ӭ�´ι��٣�\n");
        break;
    default:
        break;
    }
    my_pause();
}

int create_order(dish_menu *dm, int mode, int count)
{
    int cnt = 0;
    dish_order new_order[MAX_LENGTH];
    // ����mode���ļ�
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
    FILE *fp;
    fp = fopen(filename, "r");
    int choice;
    int temp_no;
    int temp_num;
    do
    {
        printf("\n�������Ʒ��ţ�");
        if (my_num_input('y', MAX_STR_LEN, NULL, &temp_no))
            return 0;
        // ����Ʒ����Ƿ����
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
                printf("\n����Ĳ�Ʒ��Ų����ڣ���������ȷ�Ĳ�Ʒ��ţ�");
                if (my_num_input('y', MAX_STR_LEN, NULL, &temp_no))
                    return 0;
            }
        } while (flag == 0);
        // ��Ʒ��Ŵ���ʱ����������
        printf("\n��������������");
        if (choice_f('y', &temp_num, 1, 999))
            return 0;
        new_order[cnt].nums = temp_num;
        cnt++;
        // �ж��Ƿ�������
        printf("\n�Ƿ������ˣ� 1.�� 2.�� ��\n");
        if (choice_f('y', &choice, 1, 2))
            return 0;
    } while (choice != 2);
    fclose(fp);
    // �����������ɶ����ļ���
    char fstr[50] = {'\0'};
    sprintf(fstr, "order//%d.txt", table_no);
    // �����жϸ��ļ��Ƿ���ڣ��粻�����򴴽�һ���������ñ�־λΪ1
    fp = fopen(fstr, "r");
    if (fp == NULL)
    {
        fp = fopen(fstr, "w");
        fprintf(fp, "%d\n", 1);
    }
    fclose(fp);
    // ������׷��ģʽ���´��ļ�����������Ϣ��ӽ�ȥ
    fp = fopen(fstr, "a");
    int i = 0;
    for (i = 0; i < cnt; i++)
        fprintf(fp, "%d %s %lf %d %d\n", new_order[i].no, new_order[i].dish_name, new_order[i].dish_price, new_order[i].type, new_order[i].nums);
    fclose(fp);
}

int display_menu(dish_menu *dm, int start, int end)
{
    int i;
    int choice;
    system("cls");
    printf("----------------------------------------------------------\n�����ҳ��򿪳ɹ�����ѡ��ѡ��\n�������ϼ��˵��밴Esc\n----------------------------------------------------------\n���  ��Ʒ���    ��Ʒ����      �۸�\n");
    for (i = start; i < end; i++)
        printf(" %d\t %d\t  %s\t%.2lf\n", i + 1, dm[i].no, dm[i].dish_name, dm[i].dish_price);
    printf("----------------------------------------------------------\n");
    // ��ӿ����߼�����ֹ����
    if (start == 0 && end - start < RECORD_NUM)
    {
        printf("3.���\n");
        printf("4.�˳�\n");
        if (choice_f('y', &choice, 3, 4))
            return 4;
    }
    else if (start == 0)
    {
        // ����һҳѡ��
        printf("2.��һҳ\n");
        printf("3.���\n");
        printf("4.�˳�\n");
        if (choice_f('y', &choice, 2, 4))
            return 4;
    }
    else if (end - start != RECORD_NUM)
    {
        // ����һҳѡ��
        printf("1.��һҳ\n");
        printf("3.���\n");
        printf("4.�˳�\n");
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
                printf("\n����������������� : ");
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
    { // ������ʾ
        printf("1.��һҳ\n");
        printf("2.��һҳ\n");
        printf("3.���\n");
        printf("4.�˳�\n");
        if (choice_f('y', &choice, 1, 4))
            return 4;
    }
    return choice;
}

void page_controller(dish_menu *dm, int cnt)
{
    int record_num = RECORD_NUM;
    // �趨������ʾ��ر���
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