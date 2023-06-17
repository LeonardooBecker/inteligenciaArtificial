#include <stdio.h>
#include <stdlib.h>
#include "progride.h"
#include "analisaTabuleiro.h"
#include "setaMapa.h"

void retornaVetor(Verificar **mapa, Parametros param, int *vetorCores)
{
    for (int a = 0; a < param.num_linhas; a++)
    {
        for (int b = 0; b < param.num_colunas; b++)
        {
            if ((mapa[a][b].camadaExterna) == 1)
            {
                if (vetorCores[(mapa[a][b].valor - 1)] == 0)
                    vetorCores[(mapa[a][b].valor - 1)] += 1;
            }
        }
    }
}

void progride(Verificar **mapa, int row, int column, int **matrizValoracao, Parametros param, int posicaoAtual, int *vetorSolucao, int *vetorAtual, int qntVerificacoes)
{
    int casas = 0;
    int valorMapa = 0;
    int i;
    int continua;
    int numero;

    Verificar **mapaAqui;

    mapaAqui = (Verificar **)malloc(param.num_linhas * sizeof(Verificar *));
    for (i = 0; i < param.num_linhas; i++)
        mapaAqui[i] = (Verificar *)malloc(param.num_colunas * sizeof(Verificar));

    int opcoes[param.num_cores];

    for (i = 0; i < param.num_cores; i++)
        opcoes[i] = 0;

    verificaMapa(mapa, row, column, param, &casas, matrizValoracao, &valorMapa);

    // Vetor contendo as cores que se encontram na camada externa considerando o preenchimento atual do tabuleiro
    retornaVetor(mapa, param, opcoes);

    while (1)
    {

        continua = 0;
        // Percorre pelo vetor verificando se ainda existem cores a ser utilizadas
        for (i = 0; i < param.num_cores; i++)
        {
            if (opcoes[i] > 0)
            {
                numero = (i + 1);
                opcoes[i]--;
                continua = 1;
                break;
            }
        }
        if (continua == 0)
        {
            vetorAtual[(posicaoAtual + 1)] = 0;
            for (i = 0; i < param.num_linhas; i++)
                free(mapaAqui[i]);
            free(mapaAqui);
            return;
        }

        // Copia o mapa para que possa fazer alterações
        clonaMapa(mapa, mapaAqui, param);

        mapaAqui[row][column].valor = numero;

        casas = 1;

        valorMapa = matrizValoracao[row][column];

        verificaMapa(mapaAqui, row, column, param, &casas, matrizValoracao, &valorMapa);

        setaValoracao(matrizValoracao, param);

        vetorAtual[(posicaoAtual + 1)] = numero;

        // Se o mapa não tiver sido preenchido por completo
        if (casas < (param.num_linhas * param.num_colunas))
        {
            if ((vetorSolucao[0] == 0) || ((valorMapa > vetorSolucao[0]) && (vetorSolucao[0] > matrizValoracao[row][column])))
            {
                vetorSolucao[0] = valorMapa;
                for (i = 1; i <= (qntVerificacoes + 1); i++)
                    vetorSolucao[i] = vetorAtual[i];
            }
        }
        // Mapa preenchido por completo - possívelmente todas posições reservadas ao vetor não serão usadas
        else
        {
            int qntZeros = 1;
            if (vetorSolucao[0] > matrizValoracao[row][column])
                vetorSolucao[0] = 0;

            for (i = 1; i <= (qntVerificacoes + 1); i++)
            {
                if (vetorAtual[i] == 0)
                    qntZeros++;
            }

            if (qntZeros >= vetorSolucao[0])
            {
                vetorSolucao[0] = qntZeros;
                for (i = 1; i <= (qntVerificacoes + 1); i++)
                    vetorSolucao[i] = vetorAtual[i];
            }
        }

        // Sequência comentada - utilizada para análise do código.
        // char a;
        // printf("(%d - %d - %d)\n", valorMapa, valorMapa, casas);
        // for (i = 0; i < qntVerificacoes + 2; i++)
        // {
        //     printf("%d ", vetorAtual[i]);
        // }
        // printf("\n");
        // for (i = 0; i < qntVerificacoes + 2; i++)
        // {
        //     printf("%d ", vetorSolucao[i]);
        // }
        // printf("\n");

        // imprimeMapa(mapaAqui, param);
        // scanf("%c", &a);

        if ((posicaoAtual != qntVerificacoes) && (casas < param.num_colunas * param.num_linhas))
        {
            progride(mapaAqui, row, column, matrizValoracao, param, (posicaoAtual + 1), vetorSolucao, vetorAtual, qntVerificacoes);
        }
        else
        {
            continua = 0;
            // Verifica se ainda restam elementos no vetor de cores possíveis
            for (i = 0; i < param.num_cores; i++)
            {
                if (opcoes[i] > 0)
                    continua = 1;
            }
            if (continua == 0)
            {
                for (i = 0; i < param.num_linhas; i++)
                    free(mapaAqui[i]);
                free(mapaAqui);
                vetorAtual[(posicaoAtual + 1)] = 0;
                return;
            }
        }
    }
}