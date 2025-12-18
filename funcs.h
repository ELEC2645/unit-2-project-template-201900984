#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h> // for printf(), scanf()
#include <stdlib.h> // for exit()
#include <string.h> 
#include <math.h> 

int get_user_input(int max_option);
void select_calculator_item(int input);
void print_calculator_menu(void);
void get_two_numbers(double *a, double *b);
double get_number(char *prompt);
void display_current(void);
/* void go_back_to_main(void);  */
void calculator_menu(void);

void menu_item_1(void);
void menu_item_2(void);
void menu_item_3(void);
void menu_item_4(void);
void menu_item_5(void);
void menu_item_6(void);
void menu_item_7(void);
void menu_item_8(void);
void menu_item_9(void);
void menu_item_10(void);

void top_menu(void);
void print_top_menu(void);
void select_top_menu_item(int input);

void conversion_menu(void);
void print_conversion_menu(void);
void select_conversion_item(int input);

void voltage_conversion(void);
void current_conversion(void);
void resistance_conversion(void);
void capacitance_conversion(void);
void inductance_conversion(void);
void frequency_conversion(void);
void power_conversion(void);

#endif