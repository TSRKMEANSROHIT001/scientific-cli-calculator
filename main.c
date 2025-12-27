#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>

/* ---------- Safe double parsing ---------- */
int parse_double(const char *str, double *out) {
    char *endptr;
    errno = 0;
    double val = strtod(str, &endptr);

    if (errno != 0 || endptr == str || *endptr != '\0') {
        return 0;
    }
    *out = val;
    return 1;
}

/* ---------- Help / Usage ---------- */
void print_usage(const char *prog) {
    printf("\n=========================================\n");
    printf(" Scientific CLI Calculator (ECE Oriented)\n");
    printf("=========================================\n\n");

    printf("Basic Arithmetic:\n");
    printf("  %s add   <a> <b>        Addition\n", prog);
    printf("  %s sub   <a> <b>        Subtraction\n", prog);
    printf("  %s mul   <a> <b>        Multiplication\n", prog);
    printf("  %s div   <a> <b>        Division\n", prog);

    printf("\nScientific Operations:\n");
    printf("  %s pow   <a> <b>        Power (a^b)\n", prog);
    printf("  %s sqrt  <a>            Square root\n", prog);
    printf("  %s log   <a>            Log base 10\n", prog);

    printf("\nECE / DSP Helpers:\n");
    printf("  %s rms   <v_peak>       RMS value (sinusoidal)\n", prog);
    printf("  %s nyq   <f_max>        Nyquist sampling frequency\n", prog);
    printf("  %s db    <ratio>        Ratio to dB\n", prog);
    printf("  %s dbm   <power_mW>     mW to dBm\n", prog);

    printf("\nOhm's Law:\n");
    printf("  %s ohm v <i> <r>        Voltage = I * R\n", prog);
    printf("  %s ohm i <v> <r>        Current = V / R\n", prog);
    printf("  %s ohm r <v> <i>        Resistance = V / I\n", prog);

    printf("\nExamples:\n");
    printf("  %s add 10 20\n", prog);
    printf("  %s pow 2 10\n", prog);
    printf("  %s rms 5\n", prog);
    printf("  %s nyq 1000\n", prog);
    printf("  %s ohm v 2 6\n", prog);

    printf("\nUse --help to display this menu.\n\n");
}

/* ---------- Main ---------- */
int main(int argc, char *argv[]) {

    if (argc < 2 || !strcmp(argv[1], "--help")) {
        print_usage(argv[0]);
        return 0;
    }

    const char *cmd = argv[1];
    double a, b;

    /* ---------- BASIC / SCIENTIFIC ---------- */
    if (!strcmp(cmd, "add") || !strcmp(cmd, "sub") ||
        !strcmp(cmd, "mul") || !strcmp(cmd, "div") ||
        !strcmp(cmd, "pow")) {

        if (argc != 4 || !parse_double(argv[2], &a) || !parse_double(argv[3], &b)) {
            printf("Error: Invalid numeric input\n");
            return 1;
        }

        if (!strcmp(cmd, "add")) printf("Result: %.6f\n", a + b);
        else if (!strcmp(cmd, "sub")) printf("Result: %.6f\n", a - b);
        else if (!strcmp(cmd, "mul")) printf("Result: %.6f\n", a * b);
        else if (!strcmp(cmd, "div")) {
            if (b == 0) {
                printf("Error: Division by zero\n");
                return 1;
            }
            printf("Result: %.6f\n", a / b);
        }
        else if (!strcmp(cmd, "pow")) {
            printf("Result: %.6f\n", pow(a, b));
        }
    }

    /* ---------- SQRT ---------- */
    else if (!strcmp(cmd, "sqrt")) {
        if (argc != 3 || !parse_double(argv[2], &a) || a < 0) {
            printf("Error: Invalid input for sqrt\n");
            return 1;
        }
        printf("Result: %.6f\n", sqrt(a));
    }

    /* ---------- LOG ---------- */
    else if (!strcmp(cmd, "log")) {
        if (argc != 3 || !parse_double(argv[2], &a) || a <= 0) {
            printf("Error: log requires positive input\n");
            return 1;
        }
        printf("Result: %.6f\n", log10(a));
    }

    /* ---------- DSP HELPERS ---------- */
    else if (!strcmp(cmd, "rms")) {
        if (argc != 3 || !parse_double(argv[2], &a)) {
            printf("Error: Invalid RMS input\n");
            return 1;
        }
        printf("RMS Value: %.6f\n", a / sqrt(2));
    }

    else if (!strcmp(cmd, "nyq")) {
        if (argc != 3 || !parse_double(argv[2], &a) || a <= 0) {
            printf("Error: Invalid frequency\n");
            return 1;
        }
        printf("Minimum Sampling Frequency: %.6f Hz\n", 2 * a);
    }

    else if (!strcmp(cmd, "db")) {
        if (argc != 3 || !parse_double(argv[2], &a) || a <= 0) {
            printf("Error: Ratio must be positive\n");
            return 1;
        }
        printf("Value: %.6f dB\n", 20 * log10(a));
    }

    else if (!strcmp(cmd, "dbm")) {
        if (argc != 3 || !parse_double(argv[2], &a) || a <= 0) {
            printf("Error: Power must be positive\n");
            return 1;
        }
        printf("Value: %.6f dBm\n", 10 * log10(a));
    }

    /* ---------- OHM’S LAW ---------- */
    else if (!strcmp(cmd, "ohm")) {
        if (argc != 5 || !parse_double(argv[3], &a) || !parse_double(argv[4], &b)) {
            printf("Error: Invalid Ohm's law arguments\n");
            return 1;
        }

        if (!strcmp(argv[2], "v")) {
            printf("Voltage: %.6f V\n", a * b);
        }
        else if (!strcmp(argv[2], "i")) {
            if (b == 0) {
                printf("Error: Resistance cannot be zero\n");
                return 1;
            }
            printf("Current: %.6f A\n", a / b);
        }
        else if (!strcmp(argv[2], "r")) {
            if (b == 0) {
                printf("Error: Current cannot be zero\n");
                return 1;
            }
            printf("Resistance: %.6f Ohm\n", a / b);
        }
        else {
            printf("Error: Unknown Ohm option (use v, i, r)\n");
            return 1;
        }
    }

    else {
        printf("Error: Unknown command '%s'\n", cmd);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
