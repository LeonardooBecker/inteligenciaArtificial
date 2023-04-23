#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_LINHA 1024

int main(int argc, char *argv[])
{
    FILE *arq;
    char *ptr;
    char linha[TAM_LINHA];
    char *nome_arquivo = argv[1];
    int parametros[3];
    int i = 0;
    int j = 0;
    int **mapa;

    arq = fopen(nome_arquivo, "r");

    // limpar vetor
    for (i = 0; i < 3; i++)
        parametros[i] = 0;

    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    j = 0;
    while (!feof(arq))
    {
        // Retira a duplicidade da última linha
        if (fgets(linha, TAM_LINHA, arq))
        {
            if ((parametros[0] == 0) || (parametros[1] == 0) || (parametros[2] == 0))
            {
                ptr = strtok(linha, " ");
                i = 0;
                while (ptr != NULL)
                {
                    parametros[i] = atoi(ptr);
                    i++;
                    ptr = strtok(NULL, " ");
                }

                // alocar matriz dinamicamente
                mapa = (int **)malloc(parametros[0] * sizeof(int *));
                for (i = 0; i < parametros[0]; i++)
                    mapa[i] = (int *)malloc(parametros[1] * sizeof(int));
            }
            else
            {
                ptr = strtok(linha, " ");
                i = 0;
                while ((ptr != NULL) && (ptr[0]!='\n'))
                {
                    printf("%d %d\n", j, i);
                    mapa[j][i] = atoi(ptr);
                    i++;
                    ptr = strtok(NULL, " ");
                }
                j++;
            }
        }
    }

    for (i = 0; i < 3; i++)
        printf("%d ", parametros[i]);
    printf("\n");

    // for (i = 0; i < parametros[0]; i++)
    // {
    //     for (j = 0; j < parametros[1]; j++)
    //     {
    //         mapa[i][j] = 0;
    //     }
    // }

    for (i = 0; i < parametros[0]; i++)
    {
        for (j = 0; j < parametros[1]; j++)
        {
            printf("%2d ", mapa[i][j]);
        }
        printf("\n");
    }

    fclose(arq);

    for (i = 0; i < parametros[0]; i++)
        free(mapa[i]);
    free(mapa);

    return 0;
}