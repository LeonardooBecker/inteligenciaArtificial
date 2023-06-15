#/bin/bash
gcc -Wall main.c -o main
./geramapa 30 30 3 > aux.txt
./main aux.txt
