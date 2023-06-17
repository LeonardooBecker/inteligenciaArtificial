#/bin/bash
make
./geramapa 100 100 3 > mapaTeste.txt
./main mapaTeste.txt > mapaTesteResultado.txt
cat mapaTeste.txt mapaTesteResultado.txt | ./verifica
echo $?
