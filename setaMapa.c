#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "setaMapa.h"

#define ANSI_RESET "\033[0m"
#define C_BRIGHT_CYAN "\x1b[96m"
#define C_RED "\033[31m"
#define C_GREEN "\033[32m"
#define C_YELLOW "\033[33m"
#define C_BLUE "\033[34m"
#define C_MAGENTA "\033[35m"
#define C_CYAN "\033[36m"
#define C_GRAY "\033[37m"
#define C_LIGHT_YELLOW "\x1b[93m"
#define C_LIGHT_BLUE "\x1b[94m"

void clonaMapa(Verificar **mapa, Verificar **mapaClone, Parametros param)
{
    int i, j;
    for (i = 0; i < param.num_linhas; i++)
    {
        for (j = 0; j < param.num_colunas; j++)
        {
            mapaClone[i][j].valor = mapa[i][j].valor;
            mapaClone[i][j].camadaExterna = mapa[i][j].camadaExterna;
            mapaClone[i][j].verificar = mapa[i][j].verificar;
        }
    }
}

void resetaMapa(int **mapa, Verificar **mapaClone, Parametros param)
{
    int i, j;
    for (i = 0; i < param.num_linhas; i++)
    {
        for (j = 0; j < param.num_colunas; j++)
        {
            mapaClone[i][j].valor = mapa[i][j];
            mapaClone[i][j].camadaExterna = 0;
            mapaClone[i][j].verificar = 0;
        }
    }
}

void setaValoracao(int **matrizValoracao, Parametros param)
{
    int i, j;
    for (i = 0; i < (param.num_linhas / 2) + 1; i++)
    {
        for (j = 0; j < (param.num_colunas / 2) + 1; j++)
        {

            int a = param.num_linhas - 1;
            int b = 1 - param.num_colunas;
            int c = param.num_colunas * 1 - 1 * param.num_linhas;
            double x0 = j; 
            double y0 = i; 
            double distancia = fabs(a * x0 + b * y0 + c) / sqrt(a * a + b * b); 

            int valor = (param.num_colunas * param.num_linhas * param.num_cores) / (distancia*distancia*distancia + 1);
            if(distancia==0)
                valor*=2;
            matrizValoracao[i][j] = valor;
            matrizValoracao[(param.num_linhas - i - 1)][(param.num_colunas - j - 1)] = valor;
            matrizValoracao[(param.num_linhas - i - 1)][j] = valor;
            matrizValoracao[i][(param.num_colunas - j - 1)] = valor;
        }
    }
}

void imprimeMapa(Verificar **mapa, Parametros param)
{
    for (int a = 0; a < param.num_linhas; a++)
    {
        for (int b = 0; b < param.num_colunas; b++)
        {
            if (mapa[a][b].camadaExterna == 1)
                printf("%s%2d %s", C_RED, mapa[a][b].valor, ANSI_RESET);
            else
                printf("%s%2d %s", C_BLUE, mapa[a][b].valor, ANSI_RESET);

            // switch (mapa[a][b].valor)
            // {
            // case 1:
            //     printf("%s%2c %s", C_BRIGHT_CYAN, '1', ANSI_RESET);
            //     break;
            // case 2:
            //     printf("%s%2c %s", C_RED, '2', ANSI_RESET);
            //     break;
            // case 3:
            //     printf("%s%2c %s", C_GREEN, '3', ANSI_RESET);
            //     break;
            // case 4:
            //     printf("%s%2c %s", C_YELLOW, '4', ANSI_RESET);
            //     break;
            // case 5:
            //     printf("%s%2c %s", C_BLUE, '5', ANSI_RESET);
            //     break;
            // case 6:
            //     printf("%s%2c %s", C_MAGENTA, '6', ANSI_RESET);
            //     break;
            // case 7:
            //     printf("%s%2c %s", C_CYAN, '7', ANSI_RESET);
            //     break;
            // case 8:
            //     printf("%s%2c %s", C_GRAY, '8', ANSI_RESET);
            //     break;
            // case 9:
            //     printf("%s%2c %s", C_LIGHT_BLUE, '9', ANSI_RESET);
            //     break;
            // case 10:
            //     printf("%s%d %s", C_LIGHT_YELLOW, 10, ANSI_RESET);
            //     break;
            // default:
            //     printf("%2d ", mapa[a][b].valor);
            //     break;
            // }
        }
        printf("\n");
    }
}