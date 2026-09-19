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

struct Pilha
{
    struct Pilha *prox;
    Listagen *info;
    int prof;

};typedef struct Pilha pilha;

void init(pilha **p)
{
    *p = NULL;
}

char vazia(pilha *p)
{
    return p == NULL;
}

void push(pilha **p, Listagen *info, int prof)
{
    pilha *novo = (pilha*)malloc(sizeof(pilha));

    novo->info = info;
    novo->prox = *p;
    novo->prof = prof;

    *p = novo;
}

void pop(pilha **p, Listagen **removido, int *prof)
{
    pilha *aux;

    if(*p == NULL)
    {
        *removido = NULL;
    }
    else
    {
        aux = *p;
        *prof = aux->prof;
        *removido = aux->info;
        *p = aux->prox;

        free(aux);
    }
}

void percorrer_pilha(Listagen *L, listaen **inicio)
{
    int prof=1;
    pilha *p;
    init(&p);
    push(&p, L, prof);
    while(!vazia(p))
    {
        pop(&p, &L, &prof);
        while(!nulo(L))
        {
            if(!nulo(head(L)) && atomo(head(L)))
            {
                insere_no(inicio, L->no.lista.cabeca->no.num, prof);

                L = tail(L);
            }
            else if(!nulo(head(L)) && !atomo(head(L)))
            {
                if(!nulo(tail(L)))
                    push(&p, tail(L), prof);

                push(&p, head(L), prof + 1);

                L = NULL;
            }
        }
    }
}

//Construa um algoritmo de forma nao recursiva que seja capaz de excluir todas as ocorrencias de uma determinada chave

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
};typedef struct listagen ListaGen;


void excluir_elemento(ListaGen *L, char info[])
{
    ListaGen *aux;
    pilha *p;
    init(&p);
    push(&p, L);
    while(!vazia(p))
    {
        pop(&p, &L);
        while(!nulo(L))
        {
            if(!nulo(head(L)) && atomo(head(L)))
            {
                if(strcmp(L->no.lista.cabeca->no.info, info) == 0)
                {
                    aux = head(L);
                    free(aux);
                    L->no.lista.cabeca = cons(NULL, NULL);
                }
                L = tail(L);
            }
            else if(!nulo(head(L)) && !atomo(head(L)))
            {
                //Guarda o tail da lista acima e percorre pra baixo
                if(!nulo(tail(L)))
                    push(&p, tail(L));
                L = head(L);
            }
        }
    }
}

//No algoritmo acima, se percorre a lista gen utilizando a pilha do tail caso encontre uma sublista, pois encontrando, o L eh atualizado para o head dela e guarda-se o tail da lista acima na pilha para percorrer depois, se acha atomo, percorre com tail de L normal, se acha sublista, o L eh atualizado para o head e o tail da lista pai vai para a pilha


int main(void)
{
    return 0;
}
