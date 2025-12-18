#include "funcs.h"

/* ============================================================================
 * MENU SYSTEM - All menu display and navigation logic
 * ============================================================================ */

/* ============================================================================
 * SECTION 1: MENU DISPLAY FUNCTIONS
 * ============================================================================ */

/* Display top menu */
void print_top_menu(void) {
    display_current();
    printf("\n----------- Top menu -----------\n");
    printf("|\t1. Calculator\t\t|\n");
    printf("|\t2. Conversion\t\t|\n");
    printf("|\t3. Exit\t\t\t|\n");
    printf("--------------------------------\n");
}

/* Display calculator menu */
void print_calculator_menu(void) {
    display_current();
    printf("\n----------- Calculator -----------\n");
    printf("|\t1. Addition\t\t|\n");
    printf("|\t2. Subtraction\t\t|\n");
    printf("|\t3. Multiplication\t|\n");
    printf("|\t4. Division\t\t|\n");
    printf("|\t5. Nth Root\t\t|\n");
    printf("|\t6. Power\t\t|\n");
    printf("|\t7. Logarithm\t\t|\n");
    printf("|\t8. Sin\t\t\t|\n");
    printf("|\t9. Cos\t\t\t|\n");
    printf("|\t10. Tan\t\t\t|\n");
    printf("|\t11. Clear Ans\t\t|\n");
    printf("|\t12. Go Back\t\t|\n");
    printf("---------------------------------\n");
}

/* Display conversion menu */
void print_conversion_menu(void) {
    display_current();
    printf("\n----------- Conversion -----------\n");
    printf("|\t1. Voltage\t\t|\n");
    printf("|\t2. Current\t\t|\n");
    printf("|\t3. Resistance\t\t|\n");
    printf("|\t4. Capacitance\t\t|\n");
    printf("|\t5. Inductance\t\t|\n");
    printf("|\t6. Frequency\t\t|\n");
    printf("|\t7. Power\t\t|\n");
    printf("|\t8. Clear Ans\t\t|\n");
    printf("|\t9. Go Back\t\t|\n");
    printf("---------------------------------\n");
}

/* ============================================================================
 * SECTION 2: MENU SELECTION & NAVIGATION
 * ============================================================================ */

/* Top menu handler */
void top_menu(void) {
    print_top_menu();
    int input = get_user_input(3);
    select_top_menu_item(input);
}

/* Top menu selection router */
void select_top_menu_item(int input) {
    switch (input) {
        case 1: calculator_menu(); break;
        case 2: conversion_menu(); break;
        case 3: printf("Exiting program...\n"); exit(0);
        default: printf("Invalid selection.\n"); break;
    }
}

/* Calculator menu handler */
void calculator_menu(void) {
    print_calculator_menu();
    int input = get_user_input(12);
    select_calculator_item(input);
}

/* Calculator menu selection router */
void select_calculator_item(int input) {
    switch (input) {
        case 1: menu_item_1(); break;
        case 2: menu_item_2(); break;
        case 3: menu_item_3(); break;
        case 4: menu_item_4(); break;
        case 5: menu_item_5(); break;
        case 6: menu_item_6(); break;
        case 7: menu_item_7(); break;
        case 8: menu_item_8(); break;
        case 9: menu_item_9(); break;
        case 10: menu_item_10(); break;
        case 11: clear_ans(); printf("\nAns cleared.\n"); calculator_menu(); break;
        case 12: top_menu(); break;
        default: printf("Invalid selection. Exiting...\n"); exit(1);
    }
}

/* Conversion menu handler */
void conversion_menu(void) {
    print_conversion_menu();
    int input = get_user_input(9);
    select_conversion_item(input);
}

/* Conversion menu selection router */
void select_conversion_item(int input) {
    switch (input) {
        case 1: voltage_conversion(); break;
        case 2: current_conversion(); break;
        case 3: resistance_conversion(); break;
        case 4: capacitance_conversion(); break;
        case 5: inductance_conversion(); break;
        case 6: frequency_conversion(); break;
        case 7: power_conversion(); break;
        case 8: clear_ans(); printf("\nAns cleared.\n"); conversion_menu(); break;
        case 9: top_menu(); break;
        default: printf("Invalid selection. Exiting...\n"); exit(1);
    }
}

/* ============================================================================
 * MAIN ENTRY POINT
 * ============================================================================ */

int main(void) {
    
	top_menu();

	return 0;
}