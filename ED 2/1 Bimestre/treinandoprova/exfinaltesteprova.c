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
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
        return L->no.lista.cabeca;
}

Listagen *tail(Listagen *L)
{
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
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
    struct pilhap *cabeca;
    Listagen *info;
};typedef struct pilhap pilha;


char vazia(pilha *p)
{
    return p == NULL;
}
void push(pilha **p, Listagen *info)
{
    //Primeiro, cria a caixinha
    pilha *novo = (pilha*)malloc(sizeof(pilha));
    novo->info = info;
    novo->cabeca = NULL;
    if(!*p)
    {
        *p = novo;
    }
    else
    {
        novo->cabeca = *p;
        *p = novo;
    }
}

void pop(pilha **p, Listagen **removido)
{
    pilha *aux;
    aux = *p;
    *removido = (*p)->info;
    *p = (*p)->cabeca;
    free(aux);
}

void init_p(pilha **p)
{
    *p = NULL;
}

struct filap
{
    struct filap *prox;
    Listagen *info;
};typedef struct filap fila;



void enqueue(fila **f, Listagen *dado)
{
    fila *novo = (fila*)malloc(sizeof(fila));

    novo->info = dado;
    novo->prox = NULL;

    if (*f == NULL)
    {
        *f = novo;
    }
    else
    {
        fila *aux = *f;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
}

void dequeue(fila **f, Listagen **removido)
{
    fila *aux;

    if (*f == NULL)
    {
        *removido = NULL;
    }
    else
    {
        aux = *f;

        *removido = (*f)->info;

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


//Exercicio para inserir um determinado elemento ordenado na lista em que eh informado a profundidade da mesma

/*Ideias:
Para esse exercicio eu vou utilizar uma fila por conta do controle de profundidade e toda vez que achar uma sublista, aumenta a prof e verifica se tem aquele atomo naquela linha
antes de tudo vou precisar de uma funcao auxiliar pra verificar se tem aquele atomo naquela linha, que sera chamada dentro da funcao principal, assim como a funcao de inserir ordenado
*/



char verifica_linha(Listagen *L, char at[])
{
    int achou = 0;
    while(L && !achou)
    {
        if(!nulo(head(L)) && atomo(head(L)))
        {
            if(strcmp(L->no.lista.cabeca->no.info, at) == 0)
                achou = 1;
        }
        L = tail(L);
    }
    if(achou)
        return 1;
    return 0;
}


void inserir_ordenado_linha(Listagen **L, char at[], Listagen *info) //Aqui eu posso estar mudando pra onde o ponteiro do lista pai esta apontando, por isso **
{
    Listagen *aux = (*L)->no.lista.cabeca;
    Listagen *ant = NULL;
    int achou = 0;
    if(!nulo(head(aux)) && atomo(head(aux)) && strcmp(aux->no.info, at) > 0) //Primeiro caso de insercao
    {
        info->no.lista.cauda = aux;
        (*L)->no.lista.cabeca = info;
    }
    else //Ai procura pra achar onde inserir
    {
        while(aux && !achou)
        {
            if(!nulo(head(aux)) && atomo(head(aux)))
            {
                if(strcmp(aux->no.info, at) > 0)
                {
                    achou = 1;
                }
            }
            if(!achou)
            {
                ant = aux;
                aux = tail(aux);
            }
        }
        ant->no.lista.cauda = info;
        info->no.lista.cauda = aux;
        info->no.lista.cabeca = criat(at);
    }
}


void insere(Listagen **L, char info[], int prof)
{
    fila *f, *f2, *qt;
    int qtde=0, achou;
    init(&f);
    init(&f2);
    Listagen *aux = *L;
    int prof_atual=1;
    enqueue(&f, aux);
    enqueue(&f2, aux);
    while(prof_atual < prof)
    {
        qt = f;
        while(qt)
        {
            qtde++;
            qt = qt->prox;
        }
        while(qtde > 0)
        {
            dequeue(&f2, &aux);
            dequeue(&f, &aux);
            while(aux)
            {
                if(!nulo(head(aux)) && !atomo(head(aux)))
                {
                    enqueue(&f, head(aux));
                    enqueue(&f2, aux);
                }
                aux = tail(aux);
            }
            qtde--;
        }
        prof_atual++;
    }
    
    while(!isEmpty(f2))
    {
        dequeue(&f2, &aux);
        achou = verifica_linha(head(aux), info);
        if(!achou)
        {
            Listagen *novo = cons(NULL, NULL);
            inserir_ordenado_linha(&aux, info, novo);
        }
    }
}




int main(void)
{


    return 0;
}