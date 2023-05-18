# Restaurant Ordering System

This is a simple restaurant ordering system consisting of the following files:

- `main.c`: Program entry point, containing the main function.
- `main_form.c`: Implementation file for the main interface.
- `admin_form.c`: Implementation file for the administrator interface.
- `customer_form.c`: Implementation file for the customer interface.
- `tools.c`: Implementation file for utility functions.
- `tools.h`: Header file for utility functions.

## Program Features

- The `main.c` module is the entry point of the program, which calls the `main_form.c` module to display the main interface, and enters the `customer_form.c` or `admin_form.c` module based on the user's selection.

- The `tools.c` and `tools.h` modules are auxiliary modules of the program, which define some structures, constants, variables, and functions for implementing the basic logic and operations of the program.

- The `customer_form.c` module implements the following features:
  - Customers can enter the table number to place an order.
  - Customers can search by dish type, browse the menu, and view prices.
  - Customers can select the desired dishes and quantities and place an order.
  - Customers can check the order status, pay the fee, and wait for the food to be served.

- The `admin_form.c` module implements the following features:
  - The administrator needs to enter a preset password to enter the backend system.
  - The administrator can confirm customer orders, complete orders, and view revenue.
  - The administrator can add dishes, delete dishes, and modify prices.

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
