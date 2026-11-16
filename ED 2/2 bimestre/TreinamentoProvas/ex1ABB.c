#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADarvore.h"


//Funcao pra exibir a arvore em nivel
typedef arvore Tree;


//Funcao contando o nivel

void percorrer_em_nivel(Tree *raiz)
{
    //Posso usar a msm logica da altura ou fazer do jeito que fiz no 1b, vou usar a logica da altura

    fila *f;
    initF(&f);
    int nivel = 1;
    enqueue(&f, raiz);
    enqueue(&f, NULL);

    while(!isEmptyF(f))
    {
        dequeue(&f, &raiz);
        if(raiz)
        {
            if(raiz->esq)
                enqueue(&f, raiz->esq);
            if(raiz->dir)
                enqueue(&f, raiz->dir);
            printf("%d n: %d, ", raiz->info, nivel);
        }
        else
        {
            nivel++;
            if(!isEmptyF(f))
                enqueue(&f, NULL);
        }
    }
}

//Transformar uma arvore em lista encadeada no percurso em nivel so alterando os nos

void Tree_to_listlevel(Tree *inicio)
{
    int primeiro=0;
    fila *f;
    initF(&f);
    Tree *aux = inicio;
    Tree *ant = NULL;
    enqueue(&f, aux);
    while(!isEmptyF(f))
    {
        dequeue(&f, &aux);
        if(aux->esq)
            enqueue(&f, aux->esq);
        if(aux->dir)
            enqueue(&f, aux->dir);

        if(ant)
            ant->dir = aux;

        aux->esq = ant;
        aux->dir = NULL;

        ant = aux;
        
    }
}

//Algoritmo de arvore perfeitamente balanceada nao recursivo








//Arvore AVL em disco, verificar se eh AVL ou nao em todos os nos e fazer a exclusao em disco




int main(void)
{
    return 0;
}