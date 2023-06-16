#/bin/bash
make
./geramapa 26 73 5 > mapaTeste.txt
./main mapaTeste.txt > mapaTesteResultado.txt
cat mapaTeste.txt mapaTesteResultado.txt | ./verifica
echo $?
