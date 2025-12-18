#include "funcs.h"

/* current value shown in menu and updated after each operation */
static double current = 0.0;

/* Flush leftover input */
static void flush_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

void calculator_menu(void) {
    print_calculator_menu();
    int input = get_user_input(8);
    select_calculator_item(input);
}

int get_user_input(int max_option) {
    char buffer[64];
    char *endptr;
    long val;

    while (1) {
        printf("\nSelect item: ");
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;

        buffer[strcspn(buffer, "\n")] = '\0';      // Remove newline
        val = strtol(buffer, &endptr, 10);         // Convert to long

        if (*endptr == '\0' && val >= 1 && val <= max_option)
            return (int)val;

        printf("Invalid input. \n");
    }
}


/* int get_user_input(void) {
    int input;
    printf("\nSelect item: ");
    scanf("%d", &input);  // assume valid input for this activity
    return input;
} */ 


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
    printf("|\t8. Go Back\t\t|\n");
    printf("---------------------------------\n");
}

void select_calculator_item(int input) {
    switch (input) {
        case 1: menu_item_1(); break;
        case 2: menu_item_2(); break;
        case 3: menu_item_3(); break;
        case 4: menu_item_4(); break;
        case 5: menu_item_5(); break;
        case 6: menu_item_6(); break;
        case 7: menu_item_7(); break;
        case 8: top_menu();
        default: printf("Invalid selection. Exiting...\n"); exit(1);
    }
}

/* void go_back_to_main(void) {
    /* char input;
    // this do loop ensures user inputs 'b' or 'B' to go back
    // if user inputs other characters, it keeps prompting
    do {
        printf("\nEnter 'b' or 'B' to go back to main menu: ");
        scanf(" %c", &input);
        flush_input_buffer(); //mannuelly remove \n 
    } while (input != 'b' && input != 'B'); 
    main_menu();
} */

// --------------- Menu Item Functions ---------------

/*void get_two_numbers(double *a, double *b) {
    printf("Enter first number: ");
    scanf("%lf", a);

    printf("Enter second number: ");
    scanf("%lf", b);
} */
void get_two_numbers(double *a, double *b) {
    char buffer[64], *endptr;

    while (1) {
        printf("Enter first number: ");
        if (fgets(buffer, sizeof buffer, stdin)) {
            buffer[strcspn(buffer, "\n")] = '\0';
            *a = strtod(buffer, &endptr);
            if (endptr != buffer && *endptr == '\0') break;
        }
        printf("Invalid input. Try again.\n");
    }

    while (1) {
        printf("Enter second number: ");
        if (fgets(buffer, sizeof buffer, stdin)) {
            buffer[strcspn(buffer, "\n")] = '\0';
            *b = strtod(buffer, &endptr);
            if (endptr != buffer && *endptr == '\0') break;
        }
        printf("Invalid input. Try again.\n");
    }
}

double get_number(char *prompt) {
    char buffer[64], *endptr;
    double b;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof buffer, stdin)) {
            buffer[strcspn(buffer, "\n")] = '\0';
            b = strtod(buffer, &endptr);
            if (endptr != buffer && *endptr == '\0') return b;
            // Check for constants (case-insensitive)
            if (strcasecmp(buffer, "pi") == 0) return M_PI;
            if (strcasecmp(buffer, "e") == 0) return M_E;
        }
        printf("Invalid input. Try again.\n");
    }
}

void display_current(void) {
    printf("\nCurrent: %.15g\n", current);
}

void menu_item_1(void) {
    printf("\n>> Menu 1: Addition\n");
    display_current();
    double b = get_number("Enter number to add: ");
    printf("Result: %.15g + %.15g = %.15g\n", current, b, current + b);
    current += b;
    calculator_menu();
}


void menu_item_2(void) {
    printf("\n>> Menu 2: Subtraction\n");
    display_current();
    double b = get_number("Enter number to subtract: ");
    printf("Result: %.15g - %.15g = %.15g\n", current, b, current - b);
    current -= b;
    calculator_menu();
}


void menu_item_3(void) {
    printf("\n>> Menu 3: Multiplication\n");
    display_current();
    double b = get_number("Enter number to multiply: ");
    printf("Result: %.15g * %.15g = %.15g\n", current, b, current * b);
    current *= b;
    calculator_menu();
}


void menu_item_4(void) {
    printf("\n>> Menu 4: Division\n");
    display_current();
    double b;
    do {
        b = get_number("Enter number to divide by: ");
        if (b == 0.0) {
            printf("Invalid input. Try again.\n");
        }
    } while (b == 0.0);
    printf("Result: %.15g / %.15g = %.15g\n", current, b, current / b);
    current /= b;
    calculator_menu();
}

void menu_item_5(void) {
    printf("\n>> Menu 5: Nth Root\n");
    display_current();
    double base = get_number("Enter base: ");
    double n = get_number("Enter root degree (n for nth root): ");
    if (n == 0.0) {
        printf("Invalid root degree: cannot be zero\n");
    } else if (base < 0 && fmod(n, 2) != 1) {
        printf("Invalid: negative base with even root degree\n");
    } else {
        double result = pow(base, 1.0 / n);
        printf("Result: %.15g^(1/%.15g) = %.15g\n", base, n, result);
        current = result;
    }
    calculator_menu();
}

void menu_item_6(void) {
    printf("\n>> Menu 6: Power\n");
    display_current();
    double base = get_number("Enter base: ");
    double exp = get_number("Enter exponent: ");
    double result = pow(base, exp);
    printf("Result: %.15g ^ %.15g = %.15g\n", base, exp, result);
    current = result;
    calculator_menu();
}

void menu_item_7(void) {
    printf("\n>> Menu 7: Logarithm\n");
    display_current();
    double base = get_number("Enter base: ");
    double value = get_number("Enter value: ");
    if (base <= 0 || base == 1 || value <= 0) {
        printf("Invalid base or value for logarithm\n");
    } else {
        double result = log(value) / log(base);
        printf("Result: log_%.15g(%.15g) = %.15g\n", base, value, result);
        current = result;
    }
    calculator_menu();
}

void top_menu(void) {
    print_top_menu();
    int input = get_user_input(3);
    select_top_menu_item(input);
}

void print_top_menu(void) {
    display_current();
    printf("\n----------- Top menu -----------\n");
    printf("|\t1. Calculator\t\t|\n");
    printf("|\t2. Conversion\t\t|\n");
    printf("|\t3. Exit\t\t\t|\n");
    printf("--------------------------------\n");
}

void select_top_menu_item(int input) {
    switch (input) {
        case 1: calculator_menu(); break;
        case 2: conversion_menu(); break;
        case 3: printf("Exiting program...\n"); exit(0);
        default: printf("Invalid selection.\n"); break;
    }
}

// --------------- Conversion Menu ---------------

typedef struct {
    const char *unit_print_name;   /* e.g. "mV" */
    double factor_to_base;         /* multiply by this to convert to base unit */
} unit_option;

static void run_unit_converter(const char *title,
                               const unit_option *unit_list,
                               int unit_count)
{
    while (1) {
        printf("\n%s\n", title);
        display_current();

        printf("\nFrom:\n");
        for (int i = 0; i < unit_count; i++) {
            printf("%d. %s\n", i + 1, unit_list[i].unit_print_name);
        }
        printf("%d. Go Back\n", unit_count + 1);

        int from = get_user_input(unit_count + 1);
        if (from == unit_count + 1) return;

        printf("\nTo:\n");
        for (int i = 0; i < unit_count; i++) {
            printf("%d. %s\n", i + 1, unit_list[i].unit_print_name);
        }
        printf("%d. Go Back\n", unit_count + 1);

        int to = get_user_input(unit_count + 1);
        if (to == unit_count + 1) return;

        double value = get_number("Enter value: ");

        /* Convert: value -> base -> target */
        double base_value = value * unit_list[from - 1].factor_to_base;
        double result = base_value / unit_list[to - 1].factor_to_base;

        printf("\n%.15g %s = %.15g %s\n",
               value, unit_list[from - 1].unit_print_name,
               result, unit_list[to - 1].unit_print_name);
    }
}

void conversion_menu(void) {
    print_conversion_menu();
    int input = get_user_input(8);
    select_conversion_item(input);
}

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
    printf("|\t8. Go Back\t\t|\n");
    printf("---------------------------------\n");
}

void select_conversion_item(int input) {
    switch (input) {
        case 1: voltage_conversion(); break;
        case 2: current_conversion(); break;
        case 3: resistance_conversion(); break;
        case 4: capacitance_conversion(); break;
        case 5: inductance_conversion(); break;
        case 6: frequency_conversion(); break;
        case 7: power_conversion(); break;
        case 8: top_menu();
        default: printf("Invalid selection. Exiting...\n"); exit(1);
    }
}

// --------------- Conversion Functions ---------------

void voltage_conversion(void) {
    static const unit_option unit_list[] = {
        {"uV", 0.000001},
        {"mV", 0.001},
        {"V",  1.0},
        {"kV", 1000.0},
        {"MV", 1000000.0}
    };
    run_unit_converter("Voltage Conversion", unit_list,
                       (int)(sizeof(unit_list) / sizeof(unit_list[0])));
    conversion_menu();
}

void current_conversion(void) {
    static const unit_option unit_list[] = {
        {"nA", 0.000000001},
        {"uA", 0.000001},
        {"mA", 0.001},
        {"A",  1.0}
    };
    run_unit_converter("Current Conversion", unit_list,
                       (int)(sizeof(unit_list) / sizeof(unit_list[0])));
    conversion_menu();
}

void resistance_conversion(void) {
    static const unit_option unit_list[] = {
        {"Ohm", 1.0},
        {"kOhm", 1000.0},
        {"MOhm", 1000000.0}
    };
    run_unit_converter("Resistance Conversion", unit_list,
                       (int)(sizeof(unit_list) / sizeof(unit_list[0])));
    conversion_menu();
}

void capacitance_conversion(void) {
    static const unit_option unit_list[] = {
        {"pF", 0.000000000001},
        {"nF", 0.000000001},
        {"uF", 0.000001},
        {"mF", 0.001},
        {"F",  1.0}
    };
    run_unit_converter("Capacitance Conversion", unit_list,
                       (int)(sizeof(unit_list) / sizeof(unit_list[0])));
    conversion_menu();
}

void inductance_conversion(void) {
    static const unit_option unit_list[] = {
        {"nH", 0.000000001},
        {"uH", 0.000001},
        {"mH", 0.001},
        {"H",  1.0}
    };
    run_unit_converter("Inductance Conversion", unit_list,
                       (int)(sizeof(unit_list) / sizeof(unit_list[0])));
    conversion_menu();
}

void frequency_conversion(void) {
    static const unit_option unit_list[] = {
        {"Hz",  1.0},
        {"kHz", 1000.0},
        {"MHz", 1000000.0},
        {"GHz", 1000000000.0}
    };
    run_unit_converter("Frequency Conversion", unit_list,
                       (int)(sizeof(unit_list) / sizeof(unit_list[0])));
    conversion_menu();
}

void power_conversion(void) {
    static const unit_option unit_list[] = {
        {"mW", 0.001},
        {"W",  1.0},
        {"kW", 1000.0},
        {"MW", 1000000.0}
    };
    run_unit_converter("Power Conversion", unit_list,
                       (int)(sizeof(unit_list) / sizeof(unit_list[0])));
    conversion_menu();
}