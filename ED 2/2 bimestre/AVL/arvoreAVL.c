#include <stdio.h>
#include <stdlib.h>

struct tree
{
    struct tree *esq, *dir;
    int info;
};typedef struct tree Tree;


Tree *criaNo(int info)
{
    Tree *novo = (Tree*)malloc(sizeof(Tree));
    novo->esq = novo->dir = NULL;
    novo->info = info;

    return novo;
}

void rotacao_esq(Tree **P)
{
    //Se rotaciona pra esquerda, olha pra direita

    Tree *Q, *temp;
    Q = (*P)->dir;
    temp = Q->esq;

    //Faz a rotacao
    Q->esq = *P;
    (*P)->dir = temp;
    *P = Q;
}

void rotacao_direita(Tree **P)
{
    //Se rotaciona pra direita, olha pro da esquerda
    Tree *Q, *temp;
    Q = (*P)->esq;
    temp = Q->dir;

    //Faz a rotacao
    Q->dir = *P;
    (*P)->esq = temp;
    *P = Q;
}

int main(void)
{
    return 0;
}