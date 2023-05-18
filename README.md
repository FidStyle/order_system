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
main.c模块是程序的入口，它调用了main_form.c模块来显示主界面，并根据用户的选择进入customer_form.c或admin_form.c模块。
步骤如下
- 引入头文件：在文件开头引入了一些必要的头文件，包括stdio.h、stdlib.h、string.h和tools.h等。
- 定义常量：在文件开头定义了一些常量，如MAX_DISH_NAME_LEN、MAX_STR_NAME_LEN和MAX_ORDER_NUM等。
- 函数声明：在文件开头声明了一些函数，如main_form()、customer_form()和manager_form()等。
- 主函数：在main()函数中，使用system("cls")清空屏幕，并打印欢迎信息和身份选择菜单。使用choice_f()函数获取用户输入，并根据用户选择调用相应的函数。
- 管理员界面：manager_form()函数提供了管理员界面的各种选项，包括查看订单信息、修改菜单、添加新员工等。
- 顾客界面：customer_form()函数提供了顾客界面的各种选项，包括查看菜单、点餐、查看订单信息和结账等。
- 订单处理：使用load_order_data()函数从文件中读取订单数据，并将其存储到内存中。使用save_order_data()函数将内存中的订单数据保存到文件中。使用add_order_item()函数向订单中添加新的菜品或饮料，并更新订单总价。使用check_out_order()函数完成支付操作，并将订单状态设置为已支付。

### - main_form.c
  - 在main.c文件中，用户将被要求选择身份（顾客或管理员）。
  - 如果用户选择管理员身份，则将打开admin_form.c文件，其中包含了管理员菜单的各种选项，例如添加、删除和修改菜品等。
  - 如果用户选择顾客身份，则将打开customer_form.c文件，其中包含了顾客点餐的各种选项，例如查看菜单、下订单等。
  - 在tools.h和tools.c文件中定义了一些函数，例如choice_f()函数用于获取用户输入，并确保输入在指定范围内。
  - main_form.c文件包含了主窗体的设计和布局。
  - 整个程序通过这些文件协同工作来实现一个完整的餐厅点餐系统。

- tools.c和tools.h模块是程序的辅助模块，它们定义了一些结构体，常量，变量和函数，用于实现程序的基本逻辑和操作。
   - 自定义choice_f()函数可以获取用户输入，并确保输入在指定范围内。
   
- customer_form.c模块实现了以下功能：
  - 显示欢迎信息和身份选择菜单。
  - 根据用户输入的身份选择，进入不同的界面。
  - 进入顾客界面后，显示菜单并等待用户输入点餐信息。
  - 用户输入完毕后，显示订单信息并等待确认。
  - 确认订单后，生成订单并保存到文件中。
  - 显示支付方式选择菜单，并等待用户输入支付方式。
  - 根据用户选择的支付方式计算总价，并显示给用户确认。
  - 确认支付后，完成订单流程。

- admin_form.c模块实现了以下功能：
  - 显示管理员菜单：在程序启动时，会显示欢迎信息和管理员菜单，让管理员选择需要进行的操作。

  - 添加菜品：当管理员选择添加菜品时，程序会提示输入新菜品的信息，并将其保存到对应的文件中。

  - 修改菜品：当管理员选择修改菜品时，程序会提示输入需要修改的菜品编号，并显示该菜品的详细信息。然后，管理员可以选择修改其中任意一项或全部项，并将修改后的信息保存到对应文件中。

  - 删除菜品：当管理员选择删除菜品时，程序会提示输入需要删除的菜品编号，并显示该菜品的详细信息。然后，程序会询问是否确认删除该菜品。如果确认删除，则将该菜品从对应文件中删除。

  - 查看订单：当管理员选择查看订单时，程序会读取订单文件中保存的所有订单信息，并按照时间顺序显示出来。

  - 退出系统：当管理员选择退出系统时，程序会结束运行并返回主函数。

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


