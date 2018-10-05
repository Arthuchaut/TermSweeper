# TermSweeper

A simple minesweeper written for console.
**Note :** I had not yet tested on a UNIX system.

## Building using GCC

First **compile** the files

```bash
gcc -c -Wall src/grid.c -o build/grid.o
gcc -c -Wall src/exception.c -o build/exception.o
gcc -c -Wall src/interface.c -o build/interface.o
gcc -c -Wall src/main.c -o build/main.o
```
Then create the **executable** and **link** the files

```bash
gcc -o build/termsweeper.exe \
build/main.o \
build/grid.o \
build/exception.o \
build/interface.o
```
