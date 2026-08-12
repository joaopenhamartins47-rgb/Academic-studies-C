#include <stdio.h>
#include <stdlib.h>

struct Caixa
{
    int info;
    struct Caixa *prox;
};typedef struct Caixa caixa;

void init(caixa **inicio)
{
    *inicio = NULL;
}

void insere_final(caixa **inicio, int info) //Insercao no final
{
    //Criar uma caixa nova
    caixa *novo = (caixa*)malloc(sizeof(caixa));
    //Criar um andador
    caixa *aux;
    novo->prox = NULL;
    novo->info = info;
    if(*inicio == NULL)
        *inicio = novo;
    else
    {
        aux = *inicio;
        while(aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
    
}

void exibir(caixa *inicio)
{
    caixa *aux = inicio;
    while(aux != NULL)
    {
        printf("info: %d", aux->info);
        aux = aux->prox;
    }
        
}


int main(void)
{
    caixa *inicio;
    init(&inicio);
    insere_final(&inicio, 10);
    exibir(inicio);
    return 0;
}