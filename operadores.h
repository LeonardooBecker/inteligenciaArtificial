#ifndef _operadores_
#define _operadores_
#include "estruturas.h"

int **alocarMatriz(int qntLinha,int qntColuna);

int defineLimite(Parametros param);

int continua(int casas, Parametros param);

void apresentaResultado(int passosMS, int **melhorSolucao);

void verificaSolucao(int cantoAtual, int counter, int *passosMS, int **melhorSolucao, int **solucaoAtual);

#endif