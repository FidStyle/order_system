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



# order_system

This is a simple restaurant ordering system consisting of the following files:

- `main.c`: Program entry point, containing the main function.
- `main_form.c`: Implementation file for the main interface.
- `admin_form.c`: Implementation file for the administrator interface.
- `customer_form.c`: Implementation file for the customer interface.
- `tools.c`: Implementation file for utility functions.
- `tools.h`: Header file for utility functions.

## Features

The program provides the following features:

1. Administrators can add, delete, and modify menu items, view order information, and sales data.
2. Customers can browse the menu, place orders, and pay for their meals.

## File Organization

The customer's order txt file is stored in the order folder when ordering.

cold_dish.txt corresponds to the cold dish menu

hot_dish.txt corresponds to the hot dish menu

staple_food.txt corresponds to the main dish menu

drink.txt corresponds to the beverage menu

## Usage

1. Download the source code and compile and run it.
2. After entering the program, select your identity (administrator or customer) based on the prompts and enter the corresponding number to enter the corresponding interface for operation.

## Development Environment

This program was developed and tested in the following environment:

- Operating System: Windows 11
- Compiler: gcc (MinGW.org GCC Build-20200227-1) 9.2.0
- IDE: Visual Studio

## Author

This program was written by FidStyle. If you have any questions, please contact [FidStyle/order_system (github.com)](https://github.com/FidStyle/order_system)
