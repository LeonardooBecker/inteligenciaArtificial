#ifndef _progride_
#define _progride_

#include "estruturas.h"

void retornaVetor(Verificar **mapa, Parametros param, int *vetorCores);

void progride(Verificar **mapa, int row, int column, int **matrizValoracao, Parametros param, int count, int *vetorSolucao, int *vetorAtual, int qntVerificacoes);

#endif