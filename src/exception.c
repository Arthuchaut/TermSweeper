#include <stdio.h>
#include <stdlib.h>

void raise(char *err) {
    system("cls");
    printf("[ERROR] %s\n", err);
    system("pause");
    
    exit(0);
}