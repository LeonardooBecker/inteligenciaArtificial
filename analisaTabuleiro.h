#ifndef _analisaTabuleiro_
#define _analisaTabuleiro_
#include "estruturas.h"

// Realiza o backtrackig valorando a estrutura de dados assim como contando o número de casas verificadas e o respectivo valor do mapa 
void verificaMapa(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa);

// Backtracking conferindo as posições a direita
void trackingDireita(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa);

// Backtracking conferindo as posições abaixo
void trackingBaixo(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa);

// Backtracking conferindo as posições a esquerda
void trackingEsquerda(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa);

// Backtracking conferindo as posições acima
void trackingCima(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matrizValoracao, int *valorMapa);

#endif