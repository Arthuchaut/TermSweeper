#include <stdio.h>
#include <stdlib.h>

#include "../lib/interface.h"

/**
 * Print an error message and exit the programm
 * 
 * @param {char *} err The message to print
 * 
 * @returns {void}
 */
void raise(char *msg) {
    clear();
    printf("[ERROR] %s\n", msg);
    await();
    
    exit(0);
}