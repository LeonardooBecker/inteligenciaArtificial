#include <stdio.h>
#include <stdlib.h>
#include "analisaTabuleiro.h"

void trackingDireita(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa)
{
    Verificar *direita;
    Verificar *atual;

    if (j < (param.num_colunas - 1))
        direita = &(mapa[i][j + 1]);
    atual = &(mapa[i][j]);

    /*
    Backtrack direita
    */

    if ((j < (param.num_colunas - 1)) && (direita->verificar == 1) && (direita->valor != atual->valor) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        *valorMapa += matrizValoracao[i][(j + 1)];
        direita->valor = atual->valor;
        atual->camadaExterna = 0;
        verificaMapa(mapa, i, (j + 1), param, casas, matrizValoracao, valorMapa);
    }
    if ((j < (param.num_colunas - 1)) && (direita->verificar == 0) && (direita->valor == atual->valor) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        *valorMapa += matrizValoracao[i][(j + 1)];
        atual->camadaExterna = 0;
        direita->valor = atual->valor;
        direita->verificar = 1;
        direita->camadaExterna = 0;
        verificaMapa(mapa, i, (j + 1), param, casas, matrizValoracao, valorMapa);
    }
    if ((j < (param.num_colunas - 1)) && (direita->verificar == 0))
    {
        if ((atual->camadaExterna == 0) && (atual->valor != direita->valor))
        {
            direita->camadaExterna = 1;
            verificaMapa(mapa, i, (j + 1), param, casas, matrizValoracao, valorMapa);
        }
        else if ((atual->valor == direita->valor) && (direita->camadaExterna == 0))
        {
            direita->camadaExterna = 1;
            verificaMapa(mapa, i, (j + 1), param, casas, matrizValoracao, valorMapa);
        }
    }
}

void trackingBaixo(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa)
{
    Verificar *baixo;
    Verificar *atual;
    if (i < (param.num_linhas - 1))
        baixo = &(mapa[i + 1][j]);
    atual = &(mapa[i][j]);

    /*
        Backtrack baixo
    */

    if ((i < (param.num_linhas - 1) && (baixo->verificar == 1) && (baixo->valor != atual->valor)) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        *valorMapa += matrizValoracao[(i + 1)][j];
        atual->camadaExterna = 0;
        baixo->valor = atual->valor;
        verificaMapa(mapa, (i + 1), j, param, casas, matrizValoracao, valorMapa);
    }
    if ((i < (param.num_linhas - 1) && (baixo->verificar == 0) && (baixo->valor == atual->valor)) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        *valorMapa += matrizValoracao[(i + 1)][j];
        atual->camadaExterna = 0;
        baixo->valor = atual->valor;
        baixo->verificar = 1;
        baixo->camadaExterna = 0;
        verificaMapa(mapa, (i + 1), j, param, casas, matrizValoracao, valorMapa);
    }
    else if (i < (param.num_linhas - 1) && (baixo->verificar == 0))
    {
        if ((atual->camadaExterna == 0) && (atual->valor != baixo->valor))
        {
            baixo->camadaExterna = 1;
            verificaMapa(mapa, (i + 1), j, param, casas, matrizValoracao, valorMapa);
        }
        else if ((atual->valor == baixo->valor) && (baixo->camadaExterna == 0))
        {
            baixo->camadaExterna = 1;
            verificaMapa(mapa, (i + 1), j, param, casas, matrizValoracao, valorMapa);
        }
    }
}

void trackingEsquerda(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa)
{
    Verificar *esquerda;
    Verificar *atual;
    if (j > 0)
        esquerda = &(mapa[i][j - 1]);
    atual = &(mapa[i][j]);

    /*
        Backtrack esquerda
    */

    if ((j > 0) && (esquerda->verificar == 1) && (esquerda->valor != atual->valor) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        *valorMapa += matrizValoracao[i][(j - 1)];
        atual->camadaExterna = 0;
        esquerda->valor = atual->valor;
        verificaMapa(mapa, i, (j - 1), param, casas, matrizValoracao, valorMapa);
    }
    if ((j > 0) && (esquerda->verificar == 0) && (esquerda->valor == atual->valor) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        *valorMapa += matrizValoracao[i][(j - 1)];
        atual->camadaExterna = 0;
        esquerda->valor = atual->valor;
        esquerda->verificar = 1;
        esquerda->camadaExterna = 0;
        verificaMapa(mapa, i, (j - 1), param, casas, matrizValoracao, valorMapa);
    }
    else if ((j > 0) && (esquerda->verificar == 0))
    {
        if ((atual->camadaExterna == 0) && (atual->valor != esquerda->valor) && (esquerda->verificar == 0))
        {
            esquerda->camadaExterna = 1;
            verificaMapa(mapa, i, (j - 1), param, casas, matrizValoracao, valorMapa);
        }
        else if ((atual->valor == esquerda->valor) && (esquerda->camadaExterna == 0))
        {
            esquerda->camadaExterna = 1;
            verificaMapa(mapa, i, (j - 1), param, casas, matrizValoracao, valorMapa);
        }
    }
}

void trackingCima(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa)
{
    Verificar *cima;
    Verificar *atual;
    if (i > 0)
        cima = &(mapa[i - 1][j]);
    atual = &(mapa[i][j]);

    /*
        Backtrack cima
    */

    if ((i > 0) && (cima->verificar == 1) && (cima->valor != atual->valor) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        *valorMapa += matrizValoracao[(i - 1)][j];
        atual->camadaExterna = 0;
        cima->valor = atual->valor;
        verificaMapa(mapa, (i - 1), j, param, casas, matrizValoracao, valorMapa);
    }
    if ((i > 0) && (cima->verificar == 0) && (cima->valor == atual->valor) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        *valorMapa += matrizValoracao[(i - 1)][j];
        atual->camadaExterna = 0;
        cima->valor = atual->valor;
        cima->verificar = 1;
        cima->camadaExterna = 0;
        verificaMapa(mapa, (i - 1), j, param, casas, matrizValoracao, valorMapa);
    }
    else if ((i > 0) && (cima->verificar == 0))
    {
        if ((atual->camadaExterna == 0) && (atual->valor != cima->valor))
        {
            cima->camadaExterna = 1;
            verificaMapa(mapa, (i - 1), j, param, casas, matrizValoracao, valorMapa);
        }
        else if ((atual->valor == cima->valor) && (cima->camadaExterna == 0))
        {
            cima->camadaExterna = 1;
            verificaMapa(mapa, (i - 1), j, param, casas, matrizValoracao, valorMapa);
        }
    }
}

void verificaMapa(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa)
{
    trackingDireita(mapa, i, j, param, casas, matrizValoracao, valorMapa);
    trackingBaixo(mapa, i, j, param, casas, matrizValoracao, valorMapa);
    trackingEsquerda(mapa, i, j, param, casas, matrizValoracao, valorMapa);
    trackingCima(mapa, i, j, param, casas, matrizValoracao, valorMapa);
}