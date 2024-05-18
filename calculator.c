#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "calculator.h"

double calculate(char *expression) {
    double N[STACK_SIZE] = {};
    char *ptr, O[STACK_SIZE] = {};
    int n = 0, i, j;
    for(ptr = expression; *ptr; ++ptr) {
        if(isdigit(*ptr)) {
            N[n++] = strtod(ptr, &ptr);
            ptr--;
        } else if(*ptr == '(') {
            i = 0;
            expression = ++ptr;
            while(*ptr != ')' || i) {
                if(*ptr == '(') {
                    i++;
                } else if(*ptr == ')') {
                    i--;
                }
                ptr++;
            }
            *ptr = 0;
            N[n++] = calculate(expression);
            *ptr = ')';
        } else if(*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/' || *ptr == '^') {
            O[n] = *ptr;
        } else if(*ptr != ' ') {
            return NAN;
        }
    }
    while(n > 1) {
        for(i = 1; i < n; i++) {
            if(O[i] == '^') {
                N[i - 1] = pow(N[i - 1], N[i]);
                O[i] = 0;
            } else if(O[i + 1] != '^') {
                if(O[i] == '*' || O[i] == '/') {
                    N[i - 1] = (O[i] == '*') ? N[i - 1] * N[i] : N[i - 1] / N[i];
                    O[i] = 0;
                } else if(O[i + 1] != '*' && O[i + 1] != '/') {
                    N[i - 1] = (O[i] == '+') ? N[i - 1] + N[i] : N[i - 1] - N[i];
                    O[i] = 0;
                }
            }
            if(O[i] == 0) {
                n--;
                for(j = i; j < n; ++j) {
                    N[j] = N[j + 1];
                    O[j] = O[j + 1];
                }
                i--;
            }
        }
    }
    return *N;
}