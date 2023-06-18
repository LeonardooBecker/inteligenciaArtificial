#/bin/bash
make
./geramapa  22 22 6 > mpaTeste.txt
./main < mapaTeste.txt > mapaTesteResultado.txt
cat mapaTeste.txt mapaTesteResultado.txt | ./verifica
echo $?
