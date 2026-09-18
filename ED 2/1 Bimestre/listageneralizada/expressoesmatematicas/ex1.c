#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
1:) Faça um algoritmo para resolver uma expressão matemática utilizando uma lista generalizada
(diferente do modelo de aula!). A partir de uma string (char [ ]) passada por parâmetro, o
algoritmo deverá:
a) Construir uma lista generalizada segundo as prioridades.
b) Após a lista ter sido construída, o algoritmo deverá resolver a expressão “podando” os nodos da
lista generalizada até sobrar um único nodo com o resultado, cujo valor deverá ser retornado. À
medida que cada operação vai sendo resolvida, os nodos da lista generalizada devem ser
removidos e deverá sobrar apenas um nodo com o resultado. O nodo da lista deverá ser construído
com o uso de union, uma vez que poderá ter um valor (float), um operador (char) ou uma função
(pow, sqrt, sin e cos).
Obs: Você pode usar Pilha e Fila conforme foi aprendido em aula sem a necessidade de
implementação, apenas use as funções de forma correta, com seus devidos nomes e parâmetros!
*/

//Construir a listagen de acordo com as prioridades

union valores
{
    float valorF;
    char operador;
    char funcao[8];
};

struct ListaGen
{
    struct ListaGen *cabeca;
    struct ListaGen *cauda;
    union valores no;
    char terminal;
};typedef struct ListaGen Listagen;

struct pilhap
{
    Listagen *info;
    struct pilhap *cabeca;
};typedef struct pilhap pilha;


void init_pilha(pilha **p)
{
    *p = NULL;
}

char isEmpty(pilha *p)
{
    return p == NULL;
}

void push(pilha **p, Listagen *x)
{
    pilha *novo;

    novo = (pilha *) malloc(sizeof(pilha));

    novo->info = x;
    novo->cabeca = *p;

    *p = novo;
}

void pop(pilha **p, Listagen **x)
{
    pilha *aux;

    if(*p != NULL)
    {
        aux = *p;

        *x = aux->info;

        *p = aux->cabeca;
        free(aux);
    }
}

Listagen* criaNoF(float valor)
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->no.valorF = valor;
    novo->cabeca = NULL;
    novo->cauda = NULL;
    novo->terminal = 'V';
    return novo;
}

Listagen* criaNoO(char op)
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->no.operador = op;
    novo->cabeca = NULL;
    novo->cauda = NULL;
    novo->terminal = 'O';
    return novo;
}

Listagen* criaNoFuncao(char funcao[])
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    strcpy(novo->no.funcao, funcao);
    novo->cabeca = NULL;
    novo->cauda = NULL;
    novo->terminal = 'F';
    return novo;
}



void resolve(Listagen *L)
{

}

void construir_listagen(char exp[])
{

}

int main(void)
{
    return 0;
}