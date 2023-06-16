#ifndef _setaMapa_
#define _setaMapa_

#include "estruturas.h"

void clonaMapa(Verificar **mapa, Verificar **mapaClone, Parametros param);

void resetaMapa(int **mapa, Verificar **mapaClone, Parametros param);

void setaValoracao(int **matrizValoracao, Parametros param);

void imprimeMapa(Verificar **mapa, Parametros param);

#endif