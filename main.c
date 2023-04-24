#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define TAM_LINHA 1024

typedef struct
{
    int verificar;
    int valor;

} Verificar;

typedef struct
{
    int num_cores;
    int num_linhas;
    int num_colunas;
} Parametros;

void verificaDireita(Verificar **mapa, int i, int j, Parametros param, int *casas)
{
    Verificar *direita;
    Verificar *baixo;
    Verificar *cima;
    Verificar *esquerda;
    Verificar *atual;
    baixo = &(mapa[i + 1][j]);
    cima = &(mapa[i - 1][j]);
    esquerda = &(mapa[i][j - 1]);
    direita = &(mapa[i][j + 1]);
    atual = &(mapa[i][j]);
    // system("clear");
    // for (int a = 0; a < param.num_linhas; a++)
    // {
    //     for (int b = 0; b < param.num_colunas; b++)
    //     {
    //         // printf("%2d ", mapa[i][j].valor);
    //         if (mapa[a][b].verificar == 1)
    //             printf("%3d ", mapa[a][b].valor);
    //         else
    //             printf("%3d ", mapa[a][b].verificar);
    //     }
    //     printf("\n");
    // }
    // sleep(10);
    if ((direita->verificar == 1) && (direita->valor != atual->valor) && (j < (param.num_linhas - 1)))
    {
        direita->valor = atual->valor;
        verificaDireita(mapa, i, (j + 1), param, casas);
    }
    if ((direita->verificar == 0) && (direita->valor == atual->valor) && (j < (param.num_linhas - 1)))
    {
        *casas += 1;
        direita->valor = atual->valor;
        direita->verificar = 1;
        verificaDireita(mapa, i, (j + 1), param, casas);
    }

    if ((i < (param.num_colunas - 1) && (baixo->verificar == 1) && (baixo->valor != atual->valor)))
    {
        baixo->valor = atual->valor;
        verificaDireita(mapa, (i + 1), j, param, casas);
    }
    if ((i < (param.num_colunas - 1) && (baixo->verificar == 0) && (baixo->valor == atual->valor)))
    {
        *casas += 1;
        baixo->valor = atual->valor;
        baixo->verificar = 1;
        verificaDireita(mapa, (i + 1), j, param, casas);
    }

    if ((j > 0) && (esquerda->verificar == 1) && (esquerda->valor != atual->valor))
    {
        esquerda->valor = atual->valor;
        verificaDireita(mapa, i, (j - 1), param, casas);
    }
    if ((j > 0) && (esquerda->verificar == 0) && (esquerda->valor == atual->valor))
    {
        *casas += 1;
        esquerda->valor = atual->valor;
        esquerda->verificar = 1;
        verificaDireita(mapa, i, (j - 1), param, casas);
    }

    if ((i > 0) && (cima->verificar == 1) && (cima->valor != atual->valor))
    {
        cima->valor = atual->valor;
        verificaDireita(mapa, (i - 1), j, param, casas);
    }
    if ((i > 0) && (cima->verificar == 0) && (cima->valor == atual->valor))
    {
        *casas += 1;
        cima->valor = atual->valor;
        cima->verificar = 1;
        verificaDireita(mapa, (i - 1), j, param, casas);
    }

    // printf("((%d %d))\n",i,j);
}

int main(int argc, char *argv[])
{
    FILE *arq;
    FILE *solu;
    char *ptr;
    char linha[TAM_LINHA];
    char *nome_arquivo = argv[1];
    int parametros[3];
    int i = 0;
    int j = 0;
    // int **mapa;
    int **matrizValoracao;

    srand(time(NULL));

    Verificar **mapa;

    arq = fopen(nome_arquivo, "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    solu = fopen("solu.txt", "w");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    // limpar vetor
    for (i = 0; i < 3; i++)
        parametros[i] = 0;

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
                mapa = (Verificar **)malloc(parametros[0] * sizeof(Verificar *));
                for (i = 0; i < parametros[0]; i++)
                    mapa[i] = (Verificar *)malloc(parametros[1] * sizeof(Verificar));

                matrizValoracao = (int **)malloc(parametros[0] * sizeof(int *));
                for (i = 0; i < parametros[0]; i++)
                    matrizValoracao[i] = (int *)malloc(parametros[1] * sizeof(int));
            }
            else
            {
                ptr = strtok(linha, " ");
                i = 0;
                while ((ptr != NULL) && (ptr[0] != '\n'))
                {
                    mapa[j][i].valor = atoi(ptr);
                    mapa[i][j].verificar = 0;
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

    Parametros param;
    param.num_linhas = parametros[0];
    param.num_colunas = parametros[1];
    param.num_cores = parametros[2];

    int num_linhas = parametros[0];
    int num_colunas = parametros[1];
    // for (i = 0; i < (num_linhas/2); i++)
    // {
    //     for (j = 0; j < (num_colunas/2); j++)
    //     {
    //         matrizValoracao[i][(num_colunas-j)]=i*j+1;
    //         matrizValoracao[i][j]=i*j+1;
    //     }
    // }

    mapa[0][0].verificar = 1;
    int num;
    int casas = 1;
    int count = 0;
    while (casas != 900)
    {
        num = rand() % (parametros[2] + 1);
        fprintf(solu,"a %d ",num);
        mapa[0][0].valor = num;
        verificaDireita(mapa, 0, 0, param, &casas);
        count++;
    }
    fseek(solu,0,SEEK_SET);
    fprintf(solu,"%d\n",count);
    printf("\nTotal de passos %d\n", count);
    for (i = 0; i < parametros[0]; i++)
    {
        for (j = 0; j < parametros[1]; j++)
        {
            // printf("%2d ", mapa[i][j].valor);
            if (mapa[i][j].verificar == 1)
                printf("%3d ", mapa[i][j].valor);
            else
                printf("%3d ", mapa[i][j].verificar);
        }
        printf("\n");
    }
    printf("\n\n%d\n\n", casas);
    if (i == 0 && j == 0)
    {
    }

    // int atual=mapa[i][j].valor;
    // int direita=mapa[i+1][j].valor;
    // int baixo=mapa[i][j+1].valor;
    // int esquerda=mapa[i-1][j].valor;
    // int cima=mapa[i][j-1].valor;

    fclose(arq);
    fclose(solu);

    for (i = 0; i < parametros[0]; i++)
        free(mapa[i]);
    free(mapa);

    return 0;
}