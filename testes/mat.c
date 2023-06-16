#include <stdio.h>
#include <stdlib.h>

int main()
{
    int row = 72;
    int cln = 26;

    int matrizLinha[4];
    matrizLinha[0] = 0;
    matrizLinha[1] = 0;
    matrizLinha[2] = row - 1;
    matrizLinha[3] = row - 1;

    int matrizColuna[4];
    matrizColuna[0] = 0;
    matrizColuna[1] = cln - 1;
    matrizColuna[2] = 0;
    matrizColuna[3] = cln - 1;



    int lAtual;
    int cAtual;
    int i, j;
    for (i = 0; i < 4; i++)
    {
            lAtual = matrizLinha[i];
            cAtual = matrizColuna[i];
            printf("(%d %d)\n", lAtual, cAtual);
    }
}