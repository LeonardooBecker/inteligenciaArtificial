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

void apresentaResultado(int passosMS, int **melhorSolucao)
{
    int i;
    printf("%d\n", passosMS);

    for (i = 0; i < passosMS; i++)
    {
        switch (melhorSolucao[i][0])
        {
        case 0:
            printf("a %d ", melhorSolucao[i][1]);
            break;
        case 1:
            printf("b %d ", melhorSolucao[i][1]);
            break;
        case 2:
            printf("c %d ", melhorSolucao[i][1]);
            break;
        case 3:
            printf("d %d ", melhorSolucao[i][1]);
            break;
        }
    }
    printf("\n");
}