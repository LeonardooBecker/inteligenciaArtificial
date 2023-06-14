#/bin/bash
gcc -Wall main.c -o main
./geramapa 22 22 6 > aux.txt
./main aux.txt
