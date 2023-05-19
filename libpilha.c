#include <stdio.h>
#include <stdlib.h>
#include "libpilha.h"
pilha_t *pilha_cria(int nelem)
{
    pilha_t *pilha;
    if ((pilha = malloc(sizeof(pilha_t))))
    {
        if ((pilha->elems = malloc(sizeof(int) * nelem)))
        {
            pilha->topo = -1;
            pilha->nelem = nelem;
            return pilha;
        }
        return NULL;
    }
    return NULL;
}

int push(pilha_t *pilha, int elem)
{
    if (pilha->topo == ((pilha->nelem) - 1))
        return -1;

    /* Insere elemento fornecido no topo da pilha */
    else
    {
        (pilha->topo)++;
        pilha->elems[pilha->topo] = elem;
    }
    return (pilha->topo);
}

int pop(pilha_t *pilha)
{
    /* Se a pilha estiver vazia, retorna 0 */
    if (pilha_vazia(pilha))
        return 0;
    /* Caso contrario, retorna o topo da pilha, ou seja, o ultimo elemento a ser inserido, segundo politica LIFO */
    else
    {
        (pilha->topo)--;
        return (pilha->elems[(pilha->topo) + 1]);
    }
}

int pertence_pilha(pilha_t *pilha, int elem)
{
    int i;
    /* Se a pilha estiver vazia, retorna 0 */
    if (pilha_vazia(pilha))
        return 0;
    /* Caso contrario, retorna o topo da pilha, ou seja, o ultimo elemento a ser inserido, segundo politica LIFO */
    else
    {
        if (!(pilha_vazia(pilha)))
        {
            for (i = 0; i <=(pilha->topo); i++)
                if(pilha->elems[i]==elem)
                    return 1;
        }
        return 0;
    }
}

int pilha_topo(pilha_t *pilha)
{
    /* Se a pilha estiver vazia retorna 0 */
    if (pilha_vazia(pilha))
        return 0;
    else
        return (pilha->elems[(pilha->topo)]);
}

int pilha_tamanho(pilha_t *pilha)
{
    return (pilha->topo) + 1;
}

int pilha_vazia(pilha_t *pilha)
{
    if (pilha->topo == -1)
        return 1;
    else
        return 0;
}

pilha_t *pilha_destroi(pilha_t *pilha)
{
    /* Libera primeiramente o vetor que contem todos os elementos da pilha */
    free(pilha->elems);
    /* Para entao liberar a struct pilha */
    free(pilha);
    return NULL;
}

void pilha_imprime(pilha_t *pilha)
{
    int i;
    if (!(pilha_vazia(pilha)))
    {
        for (i = 0; i < (pilha->topo); i++)
            printf("%d ", pilha->elems[i]);
        printf("%d", pilha->elems[pilha->topo]);
    }
}
