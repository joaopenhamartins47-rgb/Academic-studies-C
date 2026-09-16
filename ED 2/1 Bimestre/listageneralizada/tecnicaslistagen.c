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

struct pilhap
{
    Listagen *info;
    struct pilhap *prox;
};typedef struct pilhap pilha;

char vazia(pilha *p)
{
    return p == NULL;
}

void push(pilha **p, Listagen *info)
{
    pilha *novo = (pilha*)malloc(sizeof(pilha));
    novo->info = info;
    novo->prox = NULL;
    if(!*p)
        *p = novo;
    else
    {
        novo->prox = *p;
        *p = novo;
    }
}

void pop(pilha **p, Listagen **removido)
{
    *removido = (*p)->info;
    pilha *aux = *p;
    *p = (*p)->prox;
    free(aux);
}


struct filap
{
    Listagen *info;
    struct filap *prox;
};typedef struct filap fila;

void init(fila **f)
{
    *f = NULL;
}

char vazio(fila *f)
{
    return f == NULL;
}

void enqueue(fila **f, Listagen *info)
{
    fila *novo = (fila*)malloc(sizeof(fila));
    novo->info = info;
    novo->prox = NULL;
    if(!*f)
        *f = novo;
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
    *removido = (*f)->info;

    Listagen *aux = *f;
    *f = (*f)->prox;
    free(aux);
}

/*Tem 3 jeitos que podemos percorrer listas generalizadas
1 - Fila
2 - Pilha
3 - Recursividade
*/

//Recursividade

void cont_atomos(Listagen *L, int *cont)
{
    if(!nulo(L))
    {
        if(atomo(L))
            (*cont)++;
        cont_atomos(head(L), cont);
        cont_atomos(tail(L), cont);
    }
}

// Usando fila

void exibir_profundidade(Listagen *L)
{
    fila *f1, *qt;
    Listagen *aux = L;
    int qtde=0, prof=1;
    init(&f1);
    enqueue(&f1, aux);
    while(!vazio(f1))
    {
        //Conta a qtde da fila
        qt = f1;
        while(qt)
        {
            qtde++;
            qt = qt->prox;
        }
        while(qtde > 0)
        {
            dequeue(&f1, &aux);
            while(aux)
            {
                if(!nulo(head(aux)) && !atomo(head(aux)))
                    enqueue(&f1, head(aux));
                aux = tail(aux);
            }
            qtde--;
        }
        if(!vazio(f1)) //Se nao tiver vazio eh pq tem sublista
            prof++;
    }
    printf("A profundidade da lista eh de: %d\n", prof);
}

//Usando pilha

void init_p(pilha **p)
{
    *p = NULL;
}

void exibir_profundidade(Listagen *L)
{
    pilha *p;
    Listagen *aux;
    init_p(&p);
    push(&p, L);
    while(!vazia(p))
    {
        if(!nulo(p))
        {
            pop(&p, &aux);
            while(!nulo(aux) && !atomo(aux))
            {
                push(&p, aux);
                aux = head(aux);
            }
            if(atomo(aux))
                printf("Atomo: %s\n", aux->no.info);
            //Cheguei na ultima lista antes do atomo, agora eu preciso desempilhar e verificar o tail para andar
            pop(&p, &aux);
            aux = tail(aux);
            if(!nulo(aux))
                push(&p, aux);
        }
    }
}


int main(void)
{

}