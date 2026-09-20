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

void init(pilha **p)
{
    *p = NULL;
}

struct filap
{
    struct filap *prox; 
    Listagen *info;
};
typedef struct filap fila;

char vazia_f(fila *f)
{
    return f == NULL;
}

void init_f(fila **f)
{
    *f = NULL;
}

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
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}

void dequeue(fila **f, Listagen **removido)
{
    fila *aux;
    aux = *f;
    *removido = (*f)->info;
    *f = (*f)->prox;
    free(aux);
}

struct NoNivel
{
    int prof;
    struct NoNivel *prox;
};typedef struct NoNivel nonivel;

struct Listaen
{
    char sobrenome[20];
    int qtde;
    struct NoNivel *lista_niveis; // Ponteiro para a cabeça da lista de níveis
    struct Listaen *prox; 
};
typedef struct Listaen listaen;

void inserir_listaencadeada(listaen **inicio, char sobrenome[], int qtde, int nivel)
{
    listaen *novo = (listaen*)malloc(sizeof(listaen));
    novo->prox = NULL;
    novo->qtde = qtde;
    strcpy(novo->sobrenome, sobrenome);
    novo->lista_niveis = NULL;

    nonivel *novo_ni = (nonivel*)malloc(sizeof(nonivel));
    novo_ni->prox = NULL; //Precisa inicializar, igual foi no lista niveis em cima
    novo_ni->prof = nivel;

    nonivel *aux_ni;

    aux_ni = novo->lista_niveis;

    if(!aux_ni)
        novo->lista_niveis = novo_ni;
    
        
    
    if(!*inicio)
    {
        *inicio = novo;
    }
    else
    {
        listaen *aux = *inicio,  *ant = NULL;
        while(aux != NULL && strcmp(sobrenome, aux->sobrenome) > 0)
        {
            ant = aux;
            aux = aux->prox;
        }

        if(aux == *inicio)
        {
            novo->prox = *inicio;
            *inicio = novo;
        }
        else
        {
            ant->prox = novo;
            novo->prox = aux;
        }
        
        
    }
}

listaen *busca_sobrenome(listaen *inicio, char sobrenome[])
{
    while(inicio != NULL && strcmp(sobrenome, inicio->sobrenome) != 0)
        inicio = inicio->prox;

    return inicio;

}

void atualizar_sobrenome(listaen *end, int qtde, int nivel)
{
    nonivel *novo = (nonivel*)malloc(sizeof(nonivel));
    novo->prox = NULL;
    novo->prof = nivel;
    end->qtde = qtde+1;
    nonivel *aux = end->lista_niveis;
    while(aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;

}

//1 - Percorrer uma lista gen e armazenar numa estrutura auxiliar a quantidade de vezes que aquele sobrenome aparece junto com a profundidade com que aparece

//Pra esse algoritmo eu vou utilizar a estrutura do tipo fila pra percorrer e uma lista encadeada para armazenar os sobrenomes, assim consigo ter um controle maior sobre a profundidade



int main(void)
{
    return 0;
}