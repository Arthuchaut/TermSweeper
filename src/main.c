#include <stdio.h>
#include <stdlib.h>

#include "../lib/grid.h"
#include "../lib/interface.h"

int main(int argc, char *argv[]) {
    char in[STDIN_LEN];

    // While not exit command
    while (in[0] != '0') {
        clear(); // clear the console
        menu(); // Print the menu
        printRules(); // Print the rules

        read(in); // Read the user command to load game

        // Load the game with the user choice
        switch (in[0]) {
            case '0': exit(0);       break;
            case '1': start(5, 5);   break;
            case '2': start(10, 10); break;
            case '3': start(15, 15); break;
            case '4': start(20, 20); break;
            default: printf("Wrong command.\n");
        }
        
        await(); // Mark a pause
    }

    return 0;
}

