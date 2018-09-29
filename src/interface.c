#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/interface.h"
#include "../lib/exception.h"
#include "../lib/grid.h"

/**
 * Read the user command
 * 
 * @param {char *} args The user command
 * 
 * @returns {int} A Boolean indicating that the reading went well
 */
int read(char *args) {
    int len = STDIN_LEN;
    char *enter = NULL;

    printf("Command : ");

    if (fgets(args, len, stdin) != NULL) {
        enter = strchr(args, '\n');

        if (enter != NULL) *enter = '\0';
        else freeBuffer();

        return 1;
    }

    freeBuffer();

    return 0;
}

/**
 * Free the buffer
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void freeBuffer(void) {
    char c = NULL;

    while (c != '\n' && c != EOF) c = getchar();
}

/**
 * Clear the console
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void clear(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * Patient before continuing the program
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void await(void) {
    #ifdef _WIN32
        system("pause");
    #else
        system("read");
    #endif
}

/**
 * Print space to formatting a box in console
 * 
 * @param {char *} str The string to add spaces
 * 
 * @returns {void}
 */
void space(char *str) {
    char sp[100];
    int len = strlen(str);
    int i;

    for (i = 0; i < (NBSP - len); ++i) {
        str[len + i] = 32;
    }

    str[len + i] = '\0';
}

/**
 * Print a line for formating a box in console
 * 
 * @param {char *} str The string to add line
 * 
 * @returns {void}
 */
void printLine(char *str) {
    int i;

    str[0] = '+';

    for (i = 1; i < NBSP + 2; ++i) {
        str[i] = '-';
    }

    str[i] = '+';
    str[i + 1] = '\0';
}

/**
 * Print statistics of the current game
 * 
 * @param {const Grid *} grid The Grid pointer
 * 
 * @returns {void}
 */
void printStats(const Grid *grid) {
    char line[100];
    char flags[100];
    char mines[100];
    char revealed[100];

    sprintf(flags, "Flags: %d", grid->totalFlags);
    sprintf(mines, "Mines: %d", grid->totalMines);
    sprintf(revealed, "Revealed: %d%%", percentage(grid));

    printLine(line);
    space(flags);
    space(mines);
    space(revealed);

    printf("%s\n", line);
    printf("| %s|\n", flags);
    printf("| %s|\n", mines);
    printf("| %s|\n", revealed);
    printf("%s\n\n", line);    
}

/**
 * Print help on commands to play
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void printHelp(void) {
    printf("Commands:\n");
    printf("    F<coords>     Flag a cell           (ex: FCJ), (ex2: fcj)\n");
    printf("    U<coords>     Unflag a cell         (ex: UCJ), (ex2: ucj)\n");
    printf("    <coords>      Reveal a cell         (ex: CJ), (ex2: cj)\n");
    printf("    menu          Return to the menu\n\n");
}

/**
 * Print the rules of the game
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void printRules(void) {
    printf("Rules:\n");
    printf("    To win, you must <reveal> all <safe> cells.\n");
    printf("    Be careful, if you reveal a <mine>, you lose !\n");
    printf("    You can <flag> a cell if you think it's a mine to find your way around.\n\n");
    printf("    Good luck and have fun !\n\n");
}

/**
 * Print the menu
 * 
 * @param {void}
 * 
 * @returns {void}
 */
void menu(void) {
    printf("+-----------------------------------------------+\n");
    printf("|           TermSweeper by Arthuchaut           |\n");
    printf("+-----------------------------------------------+\n\n");

    printf("[1] - 5 x 5 grid\n");
    printf("[2] - 10 x 10 grid\n");
    printf("[3] - 15 x 15 grid\n");
    printf("[4] - 20 x 20 grid\n");
    printf("[0] - Quit\n\n");
}