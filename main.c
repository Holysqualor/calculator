#include <stdio.h>
#include <string.h>

#include "calculator.h"

int main() {
    char input[256];
    while(1) {
        printf(">> ");
        fgets(input, sizeof(input), stdin);
        *strchr(input, '\n') = 0;
        if(*input == 0) {
            continue;
        }
        if(!strcmp(input, "quit")) {
            break;
        }
        printf("%g\n", calculate(input));
    }
    return 0;
}