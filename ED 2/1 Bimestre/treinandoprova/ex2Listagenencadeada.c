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
    int num;
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

Listagen *criat(int num)
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->no.num = num;
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

    if(*f == NULL)
    {
        *removido = NULL;
    }
    else
    {
        aux = *f;
        *removido = aux->info;

        *f = aux->prox;

        free(aux);
    }
    
}

char isEmpty(fila *f)
{
    return f == NULL;
}

void init(fila **f)
{
    *f = NULL;
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

void percorre_e_cria(Listagen *L, listaen **inicio)
{
    fila *f, *qt;
    int qtde, prof=1, num;
    init(&f);
    enqueue(&f, L);
    while(!isEmpty(f))
    {
        qtde = 0;
        qt = f;
        while(qt)
        {
            qtde++;
            qt = qt->prox;
        }
        while(qtde > 0)
        {
            dequeue(&f, &L);
            while(!nulo(L))
            {
                if(!nulo(head(L)) && !atomo(head(L)))
                {
                    enqueue(&f, head(L));
                }
                else if(atomo(head(L)))
                {
                    num = L->no.lista.cabeca->no.num;
                    insere_no(&*inicio, num, prof);
                }
                L = tail(L);
            }
            qtde--;
        }
        prof++;
    }
}


int main(void)
{
    return 0;
}
