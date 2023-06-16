#include <stdio.h>
#include <stdlib.h>
#include "operadores.h"

int continua(Verificar **mapa, Parametros param)
{
    int i, j;
    int totalCasas = 0;
    for (i = 0; i < param.num_linhas; i++)
    {
        for (j = 0; j < param.num_colunas; j++)
        {
            if (mapa[i][j].verificar == 1)
                totalCasas += 1;
        }
    }

    if (totalCasas < (param.num_linhas * param.num_colunas))
        return 0;
    else
        return 1;
}

int defineLado(int iLinha, int jColuna)
{
    if (iLinha == jColuna)
        return 0;
    else if (jColuna > iLinha)
        return 1;
    else if (iLinha > jColuna)
        return 3;
    else
        return 2;
}

void preencheArquivo(int passosMS, int **melhorSolucao)
{
    FILE *solu;
    int i;

    solu = fopen("solu.txt", "w");
    if (solu == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    fprintf(solu, "%d\n", passosMS);

    for (i = 0; i < passosMS; i++)
    {
        switch (melhorSolucao[i][0])
        {
        case 0:
            fprintf(solu, "a %d ", melhorSolucao[i][1]);
            break;
        case 1:
            fprintf(solu, "b %d ", melhorSolucao[i][1]);
            break;
        case 2:
            fprintf(solu, "c %d ", melhorSolucao[i][1]);
            break;
        case 3:
            fprintf(solu, "d %d ", melhorSolucao[i][1]);
            break;
        }
    }
    fprintf(solu, "\n");
    fclose(solu);
}