#include "funcs.h"

/* current value shown in menu and updated after each operation */
static double current = 0.0;

/* Flush leftover input */
void flush_input_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

void calculator_menu(void) {
    print_calculator_menu();
    int input = get_user_input(5);
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
    printf("\nCurrent: %.15g\n", current);
    printf("\n----------- Calculator -----------\n");
    printf("|\t1. Addition\t\t|\n");
    printf("|\t2. Subtraction\t\t|\n");
    printf("|\t3. Multiplication\t|\n");
    printf("|\t4. Division\t\t|\n");
    printf("|\t5. Go Back\t\t|\n");
    printf("---------------------------------\n");
}

void select_calculator_item(int input) {
    switch (input) {
        case 1: menu_item_1(); break;
        case 2: menu_item_2(); break;
        case 3: menu_item_3(); break;
        case 4: menu_item_4(); break;
        case 5: top_menu();
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

void menu_item_1(void) {
    printf("\n>> Menu 1: Addition\n");
    double a, b;
    get_two_numbers(&a, &b);
    printf("Result: %.15g + %.15g = %.15g\n", a, b, a + b);
    current = a + b;
    calculator_menu();
}


void menu_item_2(void) {
    printf("\n>> Menu 2: Subtraction\n");
    double a, b;
    get_two_numbers(&a, &b);
    printf("Result: %.15g - %.15g = %.15g\n", a, b, a - b);
    current = a - b;
    calculator_menu();
}


void menu_item_3(void) {
    printf("\n>> Menu 3: Multiplication\n");
    double a, b;
    get_two_numbers(&a, &b);
    printf("Result: %.15g * %.15g = %.15g\n", a, b, a * b);
    current = a * b;
    calculator_menu();
}


void menu_item_4(void) {
    printf("\n>> Menu 4: Division\n");
    double a, b;
    get_two_numbers(&a, &b);
    if (b == 0.0) {
    printf("Error: division by zero\n");
    } else {
    printf("Result: %.15g / %.15g = %.15g\n", a, b, a / b);
}
    current = a / b;
    calculator_menu();
}

void top_menu(void) {
    print_top_menu();
    int input = get_user_input(3);
    select_top_menu_item(input);
}

void print_top_menu(void) {
    printf("\n----------- Top menu -----------\n");
    printf("|\t1. Calculator\t\t|\n");
    printf("|\t2. Conversion\t\t|\n");
    printf("|\t3. Exit\t\t\t|\n");
    printf("--------------------------------\n");
}

void select_top_menu_item(int input) {
    switch (input) {
        case 1: calculator_menu(); break;
        case 2: printf("Conversion\n"); break;
        case 3: printf("Exiting program...\n"); exit(0);
        default: printf("Invalid selection.\n"); break;
    }
}