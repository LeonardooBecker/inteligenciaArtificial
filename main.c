#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

#define TAM_LINHA 1024

typedef struct
{
    int verificar;
    int valor;
    int camadaExterna;

} Verificar;

typedef struct
{
    int num_cores;
    int num_linhas;
    int num_colunas;
} Parametros;

void setaValoracao(int **matrizValoracao, Parametros param)
{
    int i, j;
    for (i = 0; i < (param.num_linhas / 2) + 1; i++)
    {
        for (j = 0; j < (param.num_colunas / 2) + 1; j++)
        {
            int valor = (param.num_colunas*param.num_linhas)/(abs(i-j)+1)+1;
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

int retornaNumero(Verificar **mapa, Parametros param, int **matValoracao)
{
    int *vet_cores = malloc(param.num_cores * sizeof(int));
    for (int i = 0; i < (param.num_cores); i++)
        vet_cores[i] = 0;
    for (int a = 0; a < param.num_linhas; a++)
    {
        for (int b = 0; b < param.num_colunas; b++)
        {
            if ((mapa[a][b].camadaExterna) == 1)
            {
                vet_cores[(mapa[a][b].valor - 1)] += matValoracao[a][b];
            }
        }
    }
    int index_maior = 1;
    for (int i = 0; i < (param.num_cores); i++)
    {
        if ((vet_cores[i]) > (vet_cores[index_maior]))
        {
            index_maior = i;
        }
    }
    free(vet_cores);
    return (index_maior + 1);
}

void verificaDireita(Verificar **mapa, int i, int j, Parametros param, int *casas, int **matValoracao)
{
    Verificar *direita;
    Verificar *baixo;
    Verificar *cima;
    Verificar *esquerda;
    Verificar *atual;
    if (i < (param.num_colunas - 1))
        baixo = &(mapa[i + 1][j]);
    if (i > 0)
        cima = &(mapa[i - 1][j]);
    if (j > 0)
        esquerda = &(mapa[i][j - 1]);
    if (j < (param.num_linhas - 1))
        direita = &(mapa[i][j + 1]);
    atual = &(mapa[i][j]);

    /*
        Backtrack direita
    */
    if ((j < (param.num_linhas - 1)) && (direita->verificar == 1) && (direita->valor != atual->valor) && (atual->camadaExterna == 0))
    {
        direita->valor = atual->valor;
        atual->camadaExterna = 0;
        verificaDireita(mapa, i, (j + 1), param, casas, matValoracao);
    }
    if ((j < (param.num_linhas - 1)) && (direita->verificar == 0) && (direita->valor == atual->valor) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        atual->camadaExterna = 0;
        direita->valor = atual->valor;
        direita->verificar = 1;
        direita->camadaExterna = 0;
        verificaDireita(mapa, i, (j + 1), param, casas, matValoracao);
    }
    if ((j < (param.num_linhas - 1)) && (direita->verificar == 0))
    {
        if ((atual->camadaExterna == 0) && (atual->valor != direita->valor))
        {
            direita->camadaExterna = 1;
            verificaDireita(mapa, i, (j + 1), param, casas, matValoracao);
        }
        else if ((atual->valor == direita->valor) && (direita->camadaExterna == 0))
        {
            direita->camadaExterna = 1;
            if(matValoracao[i][j]>matValoracao[i][j-1])
                matValoracao[i][j]=matValoracao[i][j]*3;
            else
                matValoracao[i][j] = matValoracao[i][j-1]*3;
            verificaDireita(mapa, i, (j + 1), param, casas, matValoracao);
        }
    }

    /*
        Backtrack baixo
    */
    if ((i < (param.num_colunas - 1) && (baixo->verificar == 1) && (baixo->valor != atual->valor)) && (atual->camadaExterna == 0))
    {
        atual->camadaExterna = 0;
        baixo->valor = atual->valor;
        verificaDireita(mapa, (i + 1), j, param, casas, matValoracao);
    }
    if ((i < (param.num_colunas - 1) && (baixo->verificar == 0) && (baixo->valor == atual->valor)) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        atual->camadaExterna = 0;
        baixo->valor = atual->valor;
        baixo->verificar = 1;
        baixo->camadaExterna = 0;
        verificaDireita(mapa, (i + 1), j, param, casas, matValoracao);
    }
    else if (i < (param.num_colunas - 1) && (baixo->verificar == 0))
    {
        if ((atual->camadaExterna == 0) && (atual->valor != baixo->valor))
        {
            baixo->camadaExterna = 1;
            verificaDireita(mapa, (i + 1), j, param, casas, matValoracao);
        }
        else if ((atual->valor == baixo->valor) && (baixo->camadaExterna == 0))
        {
            baixo->camadaExterna = 1;
            if(matValoracao[i][j]>matValoracao[i+1][j])
                matValoracao[i][j]=matValoracao[i][j]*3;
            else
                matValoracao[i][j] = matValoracao[i+1][j]*3;
            verificaDireita(mapa, (i + 1), j, param, casas, matValoracao);
        }
    }

    /*
        Backtrack esquerda
    */
    if ((j > 0) && (esquerda->verificar == 1) && (esquerda->valor != atual->valor) && (atual->camadaExterna == 0))
    {
        atual->camadaExterna = 0;
        esquerda->valor = atual->valor;
        verificaDireita(mapa, i, (j - 1), param, casas, matValoracao);
    }
    if ((j > 0) && (esquerda->verificar == 0) && (esquerda->valor == atual->valor) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        atual->camadaExterna = 0;
        esquerda->valor = atual->valor;
        esquerda->verificar = 1;
        esquerda->camadaExterna = 0;
        verificaDireita(mapa, i, (j - 1), param, casas, matValoracao);
    }
    else if ((j > 0) && (esquerda->verificar == 0))
    {
        if ((atual->camadaExterna == 0) && (atual->valor != esquerda->valor) && (esquerda->verificar == 0))
        {
            esquerda->camadaExterna = 1;
            verificaDireita(mapa, i, (j - 1), param, casas, matValoracao);
        }
        else if ((atual->valor == esquerda->valor) && (esquerda->camadaExterna == 0))
        {
            esquerda->camadaExterna = 1;
            if(matValoracao[i][j]>matValoracao[i][j+1])
                matValoracao[i][j] = matValoracao[i][j]*3;
            else
                matValoracao[i][j] = matValoracao[i][j+1]*3;
            verificaDireita(mapa, i, (j - 1), param, casas, matValoracao);
        }
    }

    /*
        Backtrack cima
    */
    if ((i > 0) && (cima->verificar == 1) && (cima->valor != atual->valor) && (atual->camadaExterna == 0))
    {
        atual->camadaExterna = 0;
        cima->valor = atual->valor;
        verificaDireita(mapa, (i - 1), j, param, casas, matValoracao);
    }
    if ((i > 0) && (cima->verificar == 0) && (cima->valor == atual->valor) && (atual->camadaExterna == 0))
    {
        *casas += 1;
        atual->camadaExterna = 0;
        cima->valor = atual->valor;
        cima->verificar = 1;
        cima->camadaExterna = 0;
        verificaDireita(mapa, (i - 1), j, param, casas, matValoracao);
    }
    else if ((i > 0) && (cima->verificar == 0))
    {
        if ((atual->camadaExterna == 0) && (atual->valor != cima->valor))
        {
            cima->camadaExterna = 1;
            verificaDireita(mapa, (i - 1), j, param, casas, matValoracao);
        }
        else if ((atual->valor == cima->valor) && (cima->camadaExterna == 0))
        {
            cima->camadaExterna = 1;
            if(matValoracao[i][j]>matValoracao[i-1][j])
                matValoracao[i][j] = matValoracao[i][j]*3;
            else
                matValoracao[i][j] = matValoracao[i-1][j]*3;
            verificaDireita(mapa, (i - 1), j, param, casas, matValoracao);
        }
    }
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
    int **matrizValoracao;

    Verificar **mapa;
    int **guardaMapa;

    srand(time(NULL));

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
                guardaMapa = (int **)malloc(parametros[0] * sizeof(int *));
                for (i = 0; i < parametros[0]; i++)
                    guardaMapa[i] = (int *)malloc(parametros[1] * sizeof(int));
            }
            else
            {
                ptr = strtok(linha, " ");
                i = 0;
                while ((ptr != NULL) && (ptr[0] != '\n'))
                {
                    mapa[j][i].valor = atoi(ptr);
                    guardaMapa[i][j] = atoi(ptr);
                    mapa[i][j].verificar = 0;
                    mapa[i][j].camadaExterna = 0;
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

    int *frequencias = (int *)calloc(param.num_cores, sizeof(int));
    for (i = 0; i < param.num_linhas; i++)
        for (j = 0; j < param.num_colunas; j++)
            frequencias[(mapa[i][j].valor - 1)] += 1;
    for (i = 0; i < param.num_cores; i++)
        printf("%d ", frequencias[i]);
    printf("\n");

    setaValoracao(matrizValoracao, param);

    for (i = 0; i < param.num_linhas; i++)
    {
        for (j = 0; j < param.num_colunas; j++)
        {
            printf("%4d ", matrizValoracao[i][j]);
        }
        printf("\n");
    }
    char ao;
    scanf("%c", &ao);

    int **melhorSolucao;
    melhorSolucao = (int **)calloc(param.num_linhas * param.num_colunas, sizeof(int *));
    for (i = 0; i < (param.num_linhas * param.num_colunas); i++)
        melhorSolucao[i] = (int *)calloc(2, sizeof(int));

    int **solucaoAtual;
    solucaoAtual = (int **)calloc(param.num_linhas * param.num_colunas, sizeof(int *));
    for (i = 0; i < (param.num_linhas * param.num_colunas); i++)
        solucaoAtual[i] = (int *)calloc(2, sizeof(int));

    mapa[0][0].verificar = 1;
    int num;
    int casas = 1;
    int count = -1;
    int passosMS = 0;
    char none;
    while (casas != (param.num_linhas * param.num_colunas))
    {
        system("clear");
        num = retornaNumero(mapa, param, matrizValoracao);
        mapa[0][0].valor = num;
        verificaDireita(mapa, 0, 0, param, &casas, matrizValoracao);
        imprimeMapa(mapa, param);
        usleep(50000);
        count++;
        solucaoAtual[count][0] = 0;
        solucaoAtual[count][1] = num;
    }
    if ((count < passosMS) || (passosMS == 0))
    {
        passosMS = count;
        for (i = 0; i <= count; i++)
        {
            melhorSolucao[i][0] = 0;
            melhorSolucao[i][1] = solucaoAtual[i][1];
        }
    }
    // inf esq
    setaValoracao(matrizValoracao, param);
    for (i = 0; i < param.num_linhas; i++)
    {
        for (j = 0; j < param.num_colunas; j++)
        {
            mapa[i][j].valor = guardaMapa[i][j];
            mapa[i][j].camadaExterna = 0;
            mapa[i][j].verificar = 0;
        }
    }
    mapa[(param.num_linhas - 1)][0].verificar = 1;
    casas = 1;
    count = -1;
    while (casas != (param.num_linhas * param.num_colunas))
    {
        system("clear");
        num = retornaNumero(mapa, param, matrizValoracao);
        mapa[(param.num_linhas - 1)][0].valor = num;
        verificaDireita(mapa, (param.num_linhas - 1), 0, param, &casas, matrizValoracao);
        imprimeMapa(mapa, param);
        usleep(50000);
        count++;
        solucaoAtual[count][0] = 0;
        solucaoAtual[count][1] = num;
    }
    if ((count < passosMS) || (passosMS == 0))
    {
        passosMS = count;
        for (i = 0; i <= count; i++)
        {
            melhorSolucao[i][0] = 1;
            melhorSolucao[i][1] = solucaoAtual[i][1];
        }
    }

    // inf dir
    setaValoracao(matrizValoracao, param);
    for (i = 0; i < param.num_linhas; i++)
    {
        for (j = 0; j < param.num_colunas; j++)
        {
            mapa[i][j].valor = guardaMapa[i][j];
            mapa[i][j].camadaExterna = 0;
            mapa[i][j].verificar = 0;
        }
    }
    mapa[(param.num_linhas - 1)][(param.num_colunas - 1)].verificar = 1;
    casas = 1;
    count = -1;
    while (casas != (param.num_linhas * param.num_colunas))
    {
        system("clear");
        num = retornaNumero(mapa, param, matrizValoracao);
        mapa[(param.num_linhas - 1)][(param.num_colunas - 1)].valor = num;
        verificaDireita(mapa, (param.num_linhas - 1), (param.num_colunas - 1), param, &casas, matrizValoracao);
        imprimeMapa(mapa, param);
        usleep(50000);
        count++;
        solucaoAtual[count][0] = 0;
        solucaoAtual[count][1] = num;
    }
    if ((count < passosMS) || (passosMS == 0))
    {
        passosMS = count;
        for (i = 0; i <= count; i++)
        {
            melhorSolucao[i][0] = 2;
            melhorSolucao[i][1] = solucaoAtual[i][1];
        }
    }
    // sup dir
    setaValoracao(matrizValoracao, param);
    for (i = 0; i < param.num_linhas; i++)
    {
        for (j = 0; j < param.num_colunas; j++)
        {
            mapa[i][j].valor = guardaMapa[i][j];
            mapa[i][j].camadaExterna = 0;
            mapa[i][j].verificar = 0;
        }
    }
    mapa[0][(param.num_colunas - 1)].verificar = 1;
    casas = 1;
    count = -1;
    while (casas != (param.num_linhas * param.num_colunas))
    {
        system("clear");
        num = retornaNumero(mapa, param, matrizValoracao);
        mapa[0][(param.num_colunas - 1)].valor = num;
        verificaDireita(mapa, 0, (param.num_colunas - 1), param, &casas, matrizValoracao);
        imprimeMapa(mapa, param);
        usleep(50000);
        count++;
        solucaoAtual[count][0] = 0;
        solucaoAtual[count][1] = num;
    }
    if ((count < passosMS) || (passosMS == 0))
    {
        passosMS = count;
        for (i = 0; i <= count; i++)
        {
            melhorSolucao[i][0] = 3;
            melhorSolucao[i][1] = solucaoAtual[i][1];
        }
    }

    for (i = 0; i <= passosMS; i++)
    {
        switch (melhorSolucao[i][0])
        {
        case 0:
            fprintf(solu, "a %d ", melhorSolucao[i][1]);
            break;
        case 1:
            fprintf(solu, "b %d ", melhorSolucao[i][1]);
            break;
        case 2:
            fprintf(solu, "c %d ", melhorSolucao[i][1]);
            break;
        case 3:
            fprintf(solu, "d %d ", melhorSolucao[i][1]);
            break;
        }
    }

    fseek(solu, 0, SEEK_SET);
    fprintf(solu, "%d\n", passosMS);
    printf("\nTotal de passos %d\n", passosMS);

    imprimeMapa(mapa, param);

    fclose(arq);
    fclose(solu);

    for (i = 0; i < parametros[0]; i++)
        free(mapa[i]);
    free(mapa);

    return 0;
}