#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reg_lista
{
    struct listagen *cabeca;
    struct listagen *cauda;
};

union info_lista
{
    char info[8];
    struct reg_lista lista;
};

struct listagen
{
    char terminal;
    union info_lista no;
};typedef struct listagen Listagen;

char nulo(Listagen *L)
{
    return L == NULL;
}

char atomo(Listagen *L)
{
    return !nulo(L) && L->terminal;
}

Listagen *head(Listagen *L)
{
    if(nulo(L) || atomo(L))
    {
        printf("O argumento nao pode ser um atomo\n");
        return NULL;
    }
    else
        return L->no.lista.cabeca;
}

Listagen *tail(Listagen *L)
{
    if(nulo(L) || atomo(L))
    {
        printf("O argumento nao pode ser um atomo e nao pode ser nulo\n");
        return NULL;
    }
    return L->no.lista.cauda;
}

Listagen *criat(char info[])
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    strcpy(novo->no.info, info);
    novo->terminal = 1;
    return novo;
}

Listagen *cons(Listagen *H, Listagen *T)
{
    if(atomo(T))
    {
        printf("O segundo argumento nao pode ser atomo!\n");
        return NULL;
    }
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->terminal = 0;
    novo->no.lista.cabeca = H;
    novo->no.lista.cauda = T;
    return novo;
}

struct filap
{
    struct filap *prox;
    Listagen *info;
};typedef struct filap fila;

struct lista_encadeada
{
    struct lista_encadeada *prox, *ant;
    int num, prof;
};typedef struct lista_encadeada listaen;

void enqueue(fila **f, Listagen *info)
{
    fila *novo = (fila*)malloc(sizeof(fila));
    novo->info = info;
    novo->prox = NULL;
    if(!*f)
    {
        *f = novo;
    }
    else
    {
        fila *aux = *f;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

void dequeue(fila **f, Listagen **removido)
{
    fila *aux;
    Listagen *info;

    if(*f == NULL)
        return NULL;

    aux = *f;
    *removido = aux->info;

    *f = aux->prox;

    free(aux);
}

listaen* criaNo(int num, int prof)
{
    listaen *novo = (listaen*)malloc(sizeof(listaen));
    novo->ant = NULL;
    novo->prox = NULL;
    novo->num = num; novo->prof = prof;
    return novo;
}

void insere_no(listaen **inicio, int num, int prof)
{
    listaen *aux;
    listaen *novo = criaNo(num, prof);
    if(*inicio == NULL)
    {
        *inicio = novo;
    }
    else
    {
        aux = *inicio;
        while(aux->prox != NULL)
            aux = aux->prox;
        novo->ant = aux;
        aux->prox = novo;
    }
}
//Criar uma lista encadeada de acordo com a listagen com a profundidade e o valor nela

void criar

int main(void)
{
    return 0;
}
