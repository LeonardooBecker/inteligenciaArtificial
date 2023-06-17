#include <stdio.h>
#include <stdlib.h>
#include "operadores.h"

int defineLimite(Parametros param)
{
    int qntVerificacoes;
    qntVerificacoes = 30 / param.num_cores;

    if (param.num_cores <= 5)
    {
        qntVerificacoes*=3/2;
    }
    return qntVerificacoes;
}

int continua(int casas, Parametros param)
{
    if (casas < (param.num_linhas * param.num_colunas))
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

void verificaSolucao(int cantoAtual, int counter, int *passosMS, int **melhorSolucao, int **solucaoAtual)
{
    int i;
    if ((counter < *passosMS) || (*passosMS == 0))
    {
        *passosMS = counter;
        for (i = 0; i < counter; i++)
        {
            melhorSolucao[i][0] = cantoAtual;
            melhorSolucao[i][1] = solucaoAtual[i][1];
        }
    }
}