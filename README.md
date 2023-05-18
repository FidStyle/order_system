### Eng_ver
[order_system/Eng.md](https://github.com/FidStyle/order_system/blob/main/Eng.md)
# 餐厅点餐系统

这是一个简单的餐厅点餐系统，由以下几个文件构成：

- `main.c`：程序入口，包含主函数。
- `main_form.c`：主界面的实现文件。

- `admin_form.c`：管理员界面的实现文件。
- `customer_form.c`：顾客界面的实现文件。
- `tools.c`：工具函数的实现文件。
- `tools.h`：工具函数的头文件。

## 功能

该程序提供了以下功能：

1. 管理员可以添加、删除、修改菜品信息，并查看订单信息和销售情况。
2. 顾客可以浏览菜单、下单、结账等操作。

## 文件规划

点菜时将顾客订单的txt文件存入order文件夹。

cold_dish.txt 对应于凉菜菜单

hot_dish.txt 对应于热菜菜单

staple_food.txt 对应于主食菜单

drink.txt 对应于饮品菜单

## 使用方法

1. 下载源代码并编译运行。
2. 进入程序后，根据提示选择身份（管理员或顾客）并输入相应数字即可进入对应界面进行操作。

## 开发环境

该程序在以下环境下开发和测试通过：

- 操作系统：Windows 11
- 编译器：gcc (MinGW.org GCC Build-20200227-1) 9.2.0
- IDE: Visual Studio

## 作者

本程序由FidStyle编写，如有问题请联系[FidStyle/order_system (github.com)](https://github.com/FidStyle/order_system)


