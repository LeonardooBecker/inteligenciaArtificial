#ifndef _analisaTabuleiro_
#define _analisaTabuleiro_
#include "estruturas.h"

void verificaMapa(Verificar **mapa, int i, int j, Parametros param, int *casas);

void trackingDireita(Verificar **mapa, int i, int j, Parametros param, int *casas);

void trackingBaixo(Verificar **mapa, int i, int j, Parametros param, int *casas);

void trackingEsquerda(Verificar **mapa, int i, int j, Parametros param, int *casas);

void trackingCima(Verificar **mapa, int i, int j, Parametros param, int *casas);

#endif