#include <stdio.h>
#include <stdlib.h>

#include "../lib/interface.h"

void raise(char *err) {
    clear();
    printf("[ERROR] %s\n", err);
    await();
    
    exit(0);
}