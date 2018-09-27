#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/exception.h"

void read(char *str) {
    int len = 10;
    char *enter = NULL;

    if (fgets(str, len, stdin) == NULL) return -1;

    enter = strchr(str, '\n');

    if (enter != NULL) *enter = '\0';
}

void menu() {
    printf("+-----------------------------------------------+\n");
    printf("|           MINESWEEPER by Arthuchaut           |\n");
    printf("+-----------------------------------------------+\n\n");

    printf("[1] - 5  x  5 grid\n");
    printf("[2] - 10 x 10 grid\n");
    printf("[3] - 15 x 15 grid\n");
    printf("[4] - 20 x 20 grid\n");
    printf("[*] - Quit\n\n");
}