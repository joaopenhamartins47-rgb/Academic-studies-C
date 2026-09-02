#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reg_lista
{
    struct listagen *cabeça;
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
};typedef struct listagen ListaGen;


char nulo(ListaGen *L)
{
    return L == NULL;
}

char atomo(ListaGen *L)
{
    return !nulo(L) && L->terminal;
}

ListaGen *head(ListaGen *L)
{
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
        return L->no.lista.cabeça;
}

ListaGen *tail(ListaGen *L)
{
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
        return L->no.lista.cauda;
}

// A ideia aqui é percorrer de forma recursiva os head e de forma iterativa as caudas

void exibemisto(ListaGen *L)
{
    if(!nulo(L))
    {
        if(atomo(L))
            printf("%s\n", L->no.info);
        else
        {
            printf("[");
            while(!nulo(L))
            {
                exibemisto(head(L)); //Percorre os head
                L = tail(L); //Avança pela cauda
                if(!nulo(L))
                    printf(",");

            }
            printf("]");
        }
    }
}

// Agora a ideia é percorrer recursivamente pelo head e pela cauda quando desempilhar 

void exibe_recursivo(ListaGen *L)
{
    if(!nulo(L))
    {
        if(atomo(L))
            printf("%s\n", L->no.info);
        else
        {
            exibe_recursivo(head(L));
            exibe_recursivo(tail(L));
        }
    }
}

void destruir_lista(ListaGen **L)
{
    if(!nulo(*L))
    {
        if(atomo(*L))
            free(*L);
        else
        {
            destruir_lista(&(*L)->no.lista.cabeça);
            destruir_lista(&(*L)->no.lista.cauda);
            free(*L);
            *L = NULL;
        }
    }
}

struct fila
{
    ListaGen *info;
    struct fila *prox;
};typedef struct fila Fila;

void init(Fila **f)
{
    *f = NULL;
}

void enqueue(Fila **f, ListaGen *L)
{
    Fila *novo = (Fila*)malloc(sizeof(Fila));
    novo->info = L;
    novo->prox = NULL;
    if(*f == NULL)
        *f = novo;
    else
    {
        Fila *aux = *f;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

void dequeue(Fila **f, ListaGen **info)
{
    if(*f)
    {
        Fila *aux = *f;
        *info = (*f)->info;
        *f = (*f)->prox;
        free(aux);
    }
    else
        *info = NULL;
}

char isEmpty(Fila *f)
{
    return f == NULL; 
}
int contaLista(ListaGen *L)
{
    int cont =0;
    Fila *f;
    init(&f);
    enqueue(&f, L);
    while(!isEmpty(f))
    {
        dequeue(&f, &L);
        cont++;
        while(!nulo(L))
        {
            if(!nulo(head(L)) && !atomo(head(L)))
                enqueue(&f, head(L));

            L = tail(L);
        }
    }
    return cont;
}



int main(void)
{


    return 0;
}