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
    int posicaoAtual = 0;
    int valorMapa;
    int i = 0;
    int j = 0;
    int **matrizValoracao;
    int casas = 1;
    int passosMS = 0;
    int row;
    int column;
    int cantoAtual;
    int counter;
    int qntVerificacoes = 0;
    Verificar **mapa;
    int **guardaMapa;
    int **melhorSolucao;
    int **solucaoAtual;
    
    Parametros param;
    // Leitura dos parâmetros de linha, coluna e cor.
    scanf("%d", &param.num_linhas);
    scanf("%d", &param.num_colunas);
    scanf("%d", &param.num_cores);

    mapa = (Verificar **)malloc(param.num_linhas * sizeof(Verificar *));
    for (i = 0; i < param.num_linhas; i++)
        mapa[i] = (Verificar *)malloc(param.num_colunas * sizeof(Verificar));

    matrizValoracao=alocarMatriz(param.num_linhas,param.num_colunas);
    guardaMapa=alocarMatriz(param.num_linhas,param.num_colunas);
    melhorSolucao=alocarMatriz((param.num_linhas*param.num_colunas),2);
    solucaoAtual=alocarMatriz((param.num_linhas*param.num_colunas),2);

    // Preenche o tabuleiro
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

    qntVerificacoes = defineLimite(param);

    int *vetorSolucao;
    vetorSolucao = (int *)calloc((qntVerificacoes + 2), sizeof(int));

    int *vetorAtual;
    vetorAtual = (int *)calloc((qntVerificacoes + 2), sizeof(int));

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

        row = matrizCantos[cantoAtual][0];
        column = matrizCantos[cantoAtual][1];

        counter = 0;
        casas = 0;
        setaValoracao(matrizValoracao, param);

        resetaMapa(guardaMapa, mapa, param);

        mapa[row][column].verificar = 1;

        while (1)
        {
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

            if (continua(casas, param))
                break;
        }

        verificaSolucao(cantoAtual, counter, &passosMS, melhorSolucao, solucaoAtual);
    }

    apresentaResultado(passosMS, melhorSolucao);

    for (i = 0; i < param.num_linhas; i++)
        free(mapa[i]);
    free(mapa);
    for (i = 0; i < param.num_linhas; i++)
        free(matrizValoracao[i]);
    free(matrizValoracao);
    for (i = 0; i < param.num_linhas; i++)
        free(guardaMapa[i]);
    free(guardaMapa);
    for (i = 0; i < param.num_linhas * param.num_colunas; i++)
        free(melhorSolucao[i]);
    free(melhorSolucao);
    for (i = 0; i < param.num_linhas * param.num_colunas; i++)
        free(solucaoAtual[i]);
    free(solucaoAtual);

    free(vetorSolucao);
    free(vetorAtual);

    return 0;
}