#include <stdio.h>
#include <stdlib.h>


struct Arvore
{
    int info;
    struct Arvore *esq, *dir;
};typedef struct Arvore arvore;

arvore* criaNo(int info)
{
    arvore *novo = (arvore*)malloc(sizeof(arvore));
    novo->info = info;
    novo->dir = novo->esq = NULL;
    return novo;
}

void localizaNo(arvore *raiz, int info, arvore **aux)
{
    if(raiz)
    {
        if(raiz->info == info)
            *aux = raiz;
        else
        {
            localizaNo(raiz->esq, info, &*aux);
            if(!*aux)
                localizaNo(raiz->dir, info, &*aux);
        }
    }
}

void insere(arvore **raiz, int info, int info_pai, arvore *pai, char direcao)
{
    arvore *aux = NULL;
    if(*raiz == NULL)
        *raiz = criaNo(info);
    else
    {
        localizaNo(*raiz, info_pai, &aux);
        if(aux)
        {
            if(direcao == 'e' && aux->esq == NULL)
                aux->esq = criaNo(info);
            else if(direcao == 'd' && aux->dir == NULL)
                aux->dir = criaNo(info);
        }
    }
}

//Como percorrer arvores binarias?

//Basicamente ha 3 jeitos de se percorrer arvores binarias, o jeito pre-ordem, em-ordem e pos-ordem

//Os 3 jeitos de forma recursiva
void pre_ordem(arvore *raiz) //Imprime de cima ate embaixo, indo primeiro pela esquerda e depois um passo a direita
{
    if(raiz)
    {
        printf("%d", raiz->info);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }
}

void em_ordem(arvore *raiz) //Imprime os elementos em ordem seguindo os padros ABB de arvore binaria
{
    if(raiz)
    {
        em_ordem(raiz->esq);
        printf("%d", raiz->info);
        em_ordem(raiz->dir);
    }
}

void pos_ordem(arvore *raiz) //Imprime os elementos de baixo pra cima, bom para exclusoes
{
    if(raiz)
    {
        pos_ordem(raiz->esq);
        pos_ordem(raiz->dir);
        printf("%d", raiz->info);
    }
}


//Agora de forma iterativa, temos 2 jeitos padroes de codigo, seguindo a logica do pre-ordem, em-ordem e pos-ordem

//Utilizamos pilha pra percorrer
struct Pilha
{
    arvore *info;
    struct Pilha *prox;
};
typedef struct Pilha pilha;

void init(pilha **p)
{
    *p = NULL; 
}

void push(pilha **topo, arvore *info)
{
    pilha *novo = (pilha*) malloc(sizeof(pilha));

    if(novo != NULL)
    {
        novo->info = info;
        novo->prox = *topo;
        *topo = novo;
    }
}

void pop(pilha **topo, arvore **removido)
{
    pilha *aux;

    if(*topo == NULL)
        return 0;

    aux = *topo;
    *removido = aux;
    *topo = aux->prox;
    free(aux);
}

char isEmpty(pilha *topo)
{
    return topo == NULL;
}

void pre_ordemI(arvore *raiz) //Nesse codigo tem 2 partes, uma que avanca todas da esquerda e outra que coloca na pilha o elemento da direita, pra depois ser percorrido
{
    pilha *p;
    init(&p);
    push(&p, raiz);
    while(!isEmpty(p))
    {
        if(raiz)
        {
            pop(&p, &raiz);
            while(raiz)
            {
                printf("%d", raiz->info);
                push(&p, raiz);
                raiz = raiz->esq;
            }
        }
        pop(&p, &raiz);
        raiz = raiz->dir;
        if(raiz)
            push(&p, raiz);
    }
}

//Outro jeito guardando na pilha sempre o elemento da direita
void pre_ordem_pilha(arvore *raiz)
{
    pilha *p;
    init(&p);
    push(&p, raiz);
    while(!isEmpty(p))
    {
        pop(&p, &raiz);
        printf("%d", raiz->info);
        if(raiz->dir)
            push(&p, raiz->dir);
        if(raiz->esq)
            push(&p, raiz->esq);
    }
}

void em_ordemI(arvore *raiz) 
{
    pilha *p;
    init(&p);
    push(&p, raiz);
    while(!isEmpty(p))
    {
        if(raiz)
        {
            pop(&p, &raiz);
            while(raiz)
            {
                push(&p, raiz);
                raiz = raiz->esq;
            }
        }
        pop(&p, &raiz);
        printf("%d", raiz->info);
        raiz = raiz->dir;
        if(raiz)
            push(&p, raiz);
    }
}

void pos_ordemI(arvore *raiz) 
{
    pilha *p, *p2;
    init(&p);
    init(&p2);
    push(&p, raiz);
    while(!isEmpty(p))
    {
        if(raiz)
        {
            pop(&p, &raiz);
            while(raiz)
            {
                push(&p2, raiz);
                push(&p, raiz);
                raiz = raiz->dir;
            }
        }
        pop(&p, &raiz);
        raiz = raiz->esq;
        if(raiz)
            push(&p, raiz);
    }
    while(!isEmpty(p2))
    {
        pop(&p2, &raiz);
        printf("%d", raiz->info);
    }
}


//Exercicio de arvore binaria ABB

/*
Exercício 1 — Implementar a inserção de uma ABB
Crie uma função com esta assinatura:
void insereABB(arvore **raiz, int info);


Requisitos:
1. A árvore começa vazia.
2. O primeiro valor inserido se torna a raiz.
3. Cada valor seguinte percorre a árvore comparando valores até encontrar uma posição livre.
4. Valores duplicados não devem ser inseridos.
5. Você não pode informar manualmente o pai nem a direção de inserção.
*/


void insereABB(arvore **raiz, int info)
{
    arvore *aux = *raiz, *pai = NULL;
    int igual = 0;
    arvore *novo = (arvore*)malloc(sizeof(arvore));
    novo->info = info;
    novo->esq = novo->dir = NULL;
    if(!*raiz)
        *raiz = novo;
    else
    {
        //Procura pelo pai para inserir
        while(aux && !igual)
        {
            if(aux->info > info)
            {
                pai = aux;
                aux = aux->esq;
            }
            else if(aux->info < info)
            {
                pai = aux;
                aux = aux->dir;
            }
            else
                igual = 1;
        }
        if(igual)
        {
            printf("Elemento ja existente!\n");
            free(novo);
        }
        else
        {
            if(pai)
            {
                if(pai->info > info && pai->esq == NULL)
                    pai->esq = novo;
                else if(pai->info < info && pai->dir == NULL)
                    pai->dir = novo;
            }
        }
    }
}


int main(void)
{
    return 0;
}