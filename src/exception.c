#include <stdio.h>
#include <stdlib.h>

#include "../lib/interface.h"

void raise(char *err) {
    system("cls");
    printf("[ERROR] %s\n", err);
    await();
    
    exit(0);
}