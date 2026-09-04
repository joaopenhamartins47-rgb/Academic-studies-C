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

Listagen *criat(char info[])
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->terminal = 1;
    strcpy(novo->no.info, info);
    return novo;
}

Listagen *cons(Listagen *H, Listagen *T)
{
    if(atomo(T))
    {
        printf("O segundo argumento nao pode ser um atomo!\n");
        return NULL;
    }
    else{
        Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
        novo->terminal = 0;
        novo->no.lista.cabeca = H;
        novo->no.lista.cauda = T;
        return novo;
    }
}

// 1 - Fazer um algoritmo pra destruir uma lista gen

//Temos 2 formas inicialmente de percorrer uma lista gen, uma delas é percorrer recursivamente pelo head e depois pelo tail, a outra é percorrer em linhas, utilizando fila.

void destruir(Listagen **L)
{
    if(!nulo(*L))
    {
        if(atomo(*L))
            free(*L);
        else
        {
            destruir(&(*L)->no.lista.cabeca);
            destruir(&(*L)->no.lista.cauda);
            free(*L);
            *L = NULL;
        }
    }
}

// 2 - Fazer um algoritmo para duplicar uma lista generalizada fornecida por parâmetro.

// A ideia eh criar um cons com a cabeca e cauda da lista atual, percorrendo recursivamente

Listagen *head(Listagen *L)
{
    if(atomo(L))
        printf("O argumento deve ser uma lista\n");
        return NULL;
    return L->no.lista.cabeca;
}

Listagen *tail(Listagen *L)
{
    if(atomo(L))
        printf("O argumento deve ser uma lista\n");
        return NULL;
    return L->no.lista.cauda;
}

Listagen *dup(Listagen *L)
{
    if(nulo(L))
        return NULL;
    if(atomo(L))
        return criat(L->no.info);
    return cons(dup(head(L)), dup(tail(L)));
}

// 3 - Fazer um algoritmo (função boolean) para comparar duas listas generalizadas passadas por parâmetro.

char comp(Listagen *L, Listagen *L2)
{
    if(nulo(L) && nulo(L2))
        return 1;
    if(nulo(L) || nulo(L2))
        return 0;
    if(atomo(L) && atomo(L2))
        return 1;
    if(atomo(L) || atomo (L2))
        return 0;

    return comp(head(L), head(L2)) && comp(tail(L), tail(L2));
}


int main(void)
{
    return 0;
}