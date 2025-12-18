#ifndef FUNCS_H
#define FUNCS_H

#define PI 3.14159f

#include <stdio.h> // for printf(), scanf()
#include <stdlib.h> // for exit()
#include <string.h> 

int get_user_input(void);
void select_menu_item(int input);
void print_main_menu(void);
void get_two_numbers(double *a, double *b);
void go_back_to_main(void);
void main_menu(void);

void menu_item_1(void);
void menu_item_2(void);
void menu_item_3(void);
void menu_item_4(void);

#endif