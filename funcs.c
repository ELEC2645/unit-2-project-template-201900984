#include "funcs.h"

/* ============================================================================
 * SECTION 1: GLOBAL STATE & SHARED DATA
 * ============================================================================ */

/* Current value shown in menu and updated after each operation */
static double Ans = 0.0;

/* ============================================================================
 * SECTION 2: UTILITY FUNCTIONS
 * ============================================================================ */

/* Clear the Ans value to zero */
void clear_ans(void) {
    Ans = 0.0;
}

/* Get validated integer input from user within range [1, max_option] */
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

/* Get validated double number from user, supports 'pi' and 'e' constants */
double get_number(char *prompt) {
    char buffer[64], *endptr;
    double b;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof buffer, stdin)) {
            buffer[strcspn(buffer, "\n")] = '\0';
            b = strtod(buffer, &endptr);
            if (endptr != buffer && *endptr == '\0') return b;
            // Check for constants (case-insensitive) - convert to lowercase
            for (int i = 0; buffer[i]; i++) {
                buffer[i] = tolower((unsigned char)buffer[i]);
            }
            if (strcmp(buffer, "pi") == 0) return M_PI;
            if (strcmp(buffer, "e") == 0) return M_E;
        }
        printf("Invalid input. Try again.\n");
    }
}

/* Display current Ans value */
void display_current(void) {
    printf("\nAns: %.15g\n", Ans);
}

/* ============================================================================
 * SECTION 5: CALCULATOR OPERATIONS
 * ============================================================================ */

/* Addition operation */
void menu_item_1(void) {
    printf("\n>> Menu 1: Addition\n");
    display_current();
    double b = get_number("Enter number to add: ");
    printf("Result: %.15g + %.15g = %.15g\n", Ans, b, Ans + b);
    Ans += b;
    calculator_menu();
}

/* Subtraction operation */
void menu_item_2(void) {
    printf("\n>> Menu 2: Subtraction\n");
    display_current();
    double b = get_number("Enter number to subtract: ");
    printf("Result: %.15g - %.15g = %.15g\n", Ans, b, Ans - b);
    Ans -= b;
    calculator_menu();
}

/* Multiplication operation */
void menu_item_3(void) {
    printf("\n>> Menu 3: Multiplication\n");
    display_current();
    double b = get_number("Enter number to multiply: ");
    printf("Result: %.15g * %.15g = %.15g\n", Ans, b, Ans * b);
    Ans *= b;
    calculator_menu();
}

/* Division operation */
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
    printf("Result: %.15g / %.15g = %.15g\n", Ans, b, Ans / b);
    Ans /= b;
    calculator_menu();
}

/* Nth root operation */
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
        Ans = result;
    }
    calculator_menu();
}

/* Power operation */
void menu_item_6(void) {
    printf("\n>> Menu 6: Power\n");
    display_current();
    double base = get_number("Enter base: ");
    double exp = get_number("Enter exponent: ");
    double result = pow(base, exp);
    printf("Result: %.15g ^ %.15g = %.15g\n", base, exp, result);
    Ans = result;
    calculator_menu();
}

/* Logarithm operation */
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
        Ans = result;
    }
    calculator_menu();
}

/* Sine operation (degree mode) */
void menu_item_8(void) {
    printf("\n>> Menu 8: Sin\n");
    display_current();
    double degree = get_number("Enter angle in degrees: ");
    double radian = degree * M_PI / 180.0;
    double result = sin(radian);
    printf("Result: sin(%.15g°) = %.15g\n", degree, result);
    Ans = result;
    calculator_menu();
}

/* Cosine operation (degree mode) */
void menu_item_9(void) {
    printf("\n>> Menu 9: Cos\n");
    display_current();
    double degree = get_number("Enter angle in degrees: ");
    double radian = degree * M_PI / 180.0;
    double result = cos(radian);
    printf("Result: cos(%.15g°) = %.15g\n", degree, result);
    Ans = result;
    calculator_menu();
}

/* Tangent operation (degree mode) */
void menu_item_10(void) {
    printf("\n>> Menu 10: Tan\n");
    display_current();
    double degree = get_number("Enter angle in degrees: ");
    double radian = degree * M_PI / 180.0;
    double result = tan(radian);
    printf("Result: tan(%.15g°) = %.15g\n", degree, result);
    Ans = result;
    calculator_menu();
}

/* ============================================================================
 * SECTION 6: UNIT CONVERSION SYSTEM
 * ============================================================================ */

/* Unit conversion data structure */
typedef struct {
    const char *unit_print_name;   /* e.g. "mV" */
    double factor_to_base;         /* multiply by this to convert to base unit */
} unit_option;

/* Generic unit converter engine - handles all conversion types */
static void run_unit_converter(const char *title,
                               const unit_option *unit_list,
                               int unit_count)
{
    printf("\n%s\n", title);
    display_current();

    printf("\nFrom:\n");
    for (int i = 0; i < unit_count; i++) {
        printf("%d. %s\n", i + 1, unit_list[i].unit_print_name);
    }

    int from = get_user_input(unit_count);

    printf("\nTo:\n");
    for (int i = 0; i < unit_count; i++) {
        printf("%d. %s\n", i + 1, unit_list[i].unit_print_name);
    }

    int to = get_user_input(unit_count);

    double value = get_number("Enter value: ");

    /* Convert: value -> base -> target */
    double base_value = value * unit_list[from - 1].factor_to_base;
    double result = base_value / unit_list[to - 1].factor_to_base;

    printf("\n%.15g %s = %.15g %s\n",
           value, unit_list[from - 1].unit_print_name,
           result, unit_list[to - 1].unit_print_name);
    
    Ans = result;  /* Update Ans with conversion result */
}

/* Voltage conversion: microvolts to megavolts */
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

/* Current conversion: nanoamperes to amperes */
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

/* Resistance conversion: ohms to megaohms */
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

/* Capacitance conversion: picofarads to farads */
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

/* Inductance conversion: nanohenries to henries */
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

/* Frequency conversion: hertz to gigahertz */
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

/* Frequency to rad/s conversion */
void frequency_rads_conversion(void) {
    printf("\nFrequency (Hz <-> rad/s)\n");
    display_current();
    printf("\nFrom:\n1. Hz\n2. rad/s\n");
    int from = get_user_input(2);
    printf("\nTo:\n1. Hz\n2. rad/s\n");
    int to = get_user_input(2);
    
    double value = get_number("Enter value: ");
    double result;
    
    if (from == to) {
        result = value;
    } else if (from == 1 && to == 2) {
        result = value * 2.0 * M_PI;  /* Hz to rad/s */
    } else if (from == 2 && to == 1) {
        result = value / (2.0 * M_PI);  /* rad/s to Hz */
    }
    
    const char *from_unit = "Hz";
    switch (from) {
        case 2:
            from_unit = "rad/s";
            break;
        default:
            break;
    }

    const char *to_unit = "Hz";
    switch (to) {
        case 2:
            to_unit = "rad/s";
            break;
        default:
            break;
    }
    printf("\n%.15g %s = %.15g %s\n", value, from_unit, result, to_unit);
    Ans = result;
    conversion_menu();
}

/* Power conversion: milliwatts to megawatts */
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

/* Power & dBm menu */
void power_dbm_menu(void) {
    printf("\nPower Conversion\n");
    printf("1. Power (mW/W/kW/MW)\n");
    printf("2. dBm <-> W\n");
    int choice = get_user_input(2);
    
    if (choice == 1) {
        power_conversion();
    } else {
        dbm_power_conversion();
    }
}

void temperature_conversion(void) {
    printf("\nTemperature Conversion (C <-> F)\n");
    display_current();
    printf("\nFrom:\n1. Celsius (C)\n2. Fahrenheit (F)\n");
    int from = get_user_input(2);
    printf("\nTo:\n1. Celsius (C)\n2. Fahrenheit (F)\n");
    int to = get_user_input(2);

    double value = get_number("Enter value: ");
    double result;

    if (from == to) {
        result = value;
    } else if (from == 1 && to == 2) {
        result = value * 9.0 / 5.0 + 32.0;  /* C to F */
    } else if (from == 2 && to == 1) {
        result = (value - 32.0) * 5.0 / 9.0;  /* F to C */
    }

    const char *from_unit = "C";
    switch (from) {
        case 2:
            from_unit = "F";
            break;
        default:
            break;
    }

    const char *to_unit = "C";
    switch (to) {
        case 2:
            to_unit = "F";
            break;
        default:
            break;
    }
    printf("\n%.15g %s = %.15g %s\n", value, from_unit, result, to_unit);
    Ans = result;
    conversion_menu();
}

/* Power level conversion: dBm <-> W */
void dbm_power_conversion(void) {
    printf("\nPower Level Conversion (dBm <-> W)\n");
    display_current();
    printf("\nFrom:\n1. dBm\n2. W\n");
    int from = get_user_input(2);
    printf("\nTo:\n1. dBm\n2. W\n");
    int to = get_user_input(2);

    double value, result;

    if (from == to) {
        value = get_number("Enter value: ");
        result = value;
    } else if (from == 1 && to == 2) {
        value = get_number("Enter value in dBm: ");
        result = pow(10.0, (value - 30.0) / 10.0);  /* dBm to W */
        printf("\n%.15g dBm = %.15g W\n", value, result);
    } else if (from == 2 && to == 1) {
        do {
            value = get_number("Enter value in W (>0): ");
            if (value <= 0.0) printf("Invalid input. Must be > 0.\n");
        } while (value <= 0.0);
        result = 10.0 * log10(value) + 30.0;  /* W to dBm */
        printf("\n%.15g W = %.15g dBm\n", value, result);
    } else {
        value = get_number("Enter value: ");
        result = value;
    }

    Ans = result;
    conversion_menu();
}