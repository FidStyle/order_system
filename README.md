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

## 程序功能介绍
- main.c模块是程序的入口，它调用了main_form.c模块来显示主界面，并根据用户的选择进入customer_form.c或admin_form.c模块。

- tools.c和tools.h模块是程序的辅助模块，它们定义了一些结构体，常量，变量和函数，用于实现程序的基本逻辑和操作。

- customer_form.c模块实现了以下功能：
  - 顾客可以输入餐台号进行点餐。
  - 顾客可以根据菜品类型进行搜索，浏览菜单和价格。
  - 顾客可以选择想要的菜品和数量并下单。
  - 顾客可以查看订单状态，支付费用，等待出餐。

- admin_form.c模块实现了以下功能：
  - 管理员需要输入预设的密码才能进入后台系统。
  - 管理员可以确认顾客的订单，完成订单，查看营业额。
  - 管理员可以添加菜品，删除菜品，修改价格。
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


