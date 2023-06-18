#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "setaMapa.h"
#include "analisaTabuleiro.h"
#include "progride.h"
#include "operadores.h"

int main(int argc, char *argv[])
{
    FILE *arq;
    int parametros[3];
    int i = 0;
    int j = 0;
    int **matrizValoracao;
    int casas = 1;
    int valorMapa = 0;
    int posicaoAtual = 0;
    int passosMS = 0;
    int row;
    int column;
    int cantoAtual;
    int counter;
    int qntVerificacoes = 0;
    Verificar **mapa;
    int **guardaMapa;

    // limpar vetor
    for (i = 0; i < 3; i++)
        parametros[i] = 0;

    Parametros param;
    // param.num_linhas = parametros[0];
    // param.num_colunas = parametros[1];
    // param.num_cores = parametros[2];

    scanf("%d", &param.num_linhas);
    scanf("%d", &param.num_colunas);
    scanf("%d", &param.num_cores);

    mapa = (Verificar **)malloc(param.num_linhas * sizeof(Verificar *));
    for (i = 0; i < param.num_linhas; i++)
        mapa[i] = (Verificar *)malloc(param.num_colunas * sizeof(Verificar));

    matrizValoracao = (int **)malloc(param.num_linhas * sizeof(int *));
    for (i = 0; i < param.num_linhas; i++)
        matrizValoracao[i] = (int *)malloc(param.num_colunas * sizeof(int));
    guardaMapa = (int **)malloc(param.num_linhas * sizeof(int *));
    for (i = 0; i < param.num_linhas; i++)
        guardaMapa[i] = (int *)malloc(param.num_colunas * sizeof(int));

    for (i = 0; i < param.num_linhas; i++)
    {
        for (j = 0; j < param.num_colunas; j++)
        {
            scanf("%d", &(mapa[i][j].valor));
            guardaMapa[i][j] = mapa[i][j].valor;
            mapa[i][j].verificar = 0;
            mapa[i][j].camadaExterna = 0;
        }
    }

    int **melhorSolucao;
    melhorSolucao = (int **)calloc(param.num_linhas * param.num_colunas, sizeof(int *));
    for (i = 0; i < (param.num_linhas * param.num_colunas); i++)
        melhorSolucao[i] = (int *)calloc(2, sizeof(int));

    int **solucaoAtual;
    solucaoAtual = (int **)calloc(param.num_linhas * param.num_colunas, sizeof(int *));
    for (i = 0; i < (param.num_linhas * param.num_colunas); i++)
        solucaoAtual[i] = (int *)calloc(2, sizeof(int));

    int *vetorSolucao;
    vetorSolucao = (int *)calloc((qntVerificacoes + 2), sizeof(int));

    int *vetorAtual;
    vetorAtual = (int *)calloc((qntVerificacoes + 2), sizeof(int));

    qntVerificacoes = defineLimite(param);

    int matrizCantos[4][2];
    matrizCantos[0][0] = 0;
    matrizCantos[1][0] = 0;
    matrizCantos[2][0] = param.num_linhas - 1;
    matrizCantos[3][0] = param.num_linhas - 1;
    matrizCantos[0][1] = 0;
    matrizCantos[1][1] = param.num_colunas - 1;
    matrizCantos[2][1] = param.num_colunas - 1;
    matrizCantos[3][1] = 0;

    passosMS = 0;

    for (cantoAtual = 0; cantoAtual < 4; cantoAtual++)
    {

        printf("processando....\n");

        row = matrizCantos[cantoAtual][0];
        column = matrizCantos[cantoAtual][1];

        counter = 0;
        casas = 0;
        setaValoracao(matrizValoracao, param);

        resetaMapa(guardaMapa, mapa, param);

        mapa[row][column].verificar = 1;

        while (1)
        {
            // Limpa vetores
            for (i = 0; i < qntVerificacoes + 2; i++)
            {
                vetorSolucao[i] = 0;
                vetorAtual[i] = 0;
            }

            progride(mapa, row, column, matrizValoracao, param, posicaoAtual, vetorSolucao, vetorAtual, qntVerificacoes);

            for (i = 1; i < qntVerificacoes + 2; i++)
            {
                if (vetorSolucao[i] == 0)
                    break;

                mapa[row][column].valor = vetorSolucao[i];
                casas = 1;
                verificaMapa(mapa, row, column, param, &casas, matrizValoracao, &valorMapa);
                solucaoAtual[counter][0] = 0;
                solucaoAtual[counter][1] = vetorSolucao[i];
                counter++;
            }
            // // Comentario para debug
            // char ao;
            // system("clear");
            // printf("\n%d\n", casas);
            // imprimeMapa(mapa, param);
            // scanf("%c", &ao);

            if (continua(casas, param))
                break;
        }

        verificaSolucao(cantoAtual, counter, &passosMS, melhorSolucao, solucaoAtual);
    }

    apresentaResultado(passosMS, melhorSolucao);

    for (i = 0; i < param.num_linhas; i++)
        free(mapa[i]);
    // free(mapa);
    // for (i = 0; i < param.num_linhas; i++)
    //     free(matrizValoracao[i]);
    // free(matrizValoracao);
    // for (i = 0; i < param.num_linhas; i++)
    //     free(guardaMapa[i]);
    // free(guardaMapa);
    // for (i = 0; i < param.num_linhas * param.num_colunas; i++)
    //     free(melhorSolucao[i]);
    // free(melhorSolucao);
    // for (i = 0; i < param.num_linhas * param.num_colunas; i++)
    //     free(solucaoAtual[i]);
    // free(solucaoAtual);

    // free(vetorSolucao);
    // free(vetorAtual);

    return 0;
}
